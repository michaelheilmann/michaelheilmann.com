// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
//
// Permission to use, copy, modify, and distribute this software for any
// purpose without fee is hereby granted, provided that this entire notice
// is included in all copies of any software which is or includes a copy
// or modification of this software and in all copies of the supporting
// documentation for such software.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
// WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
// REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
// OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

// Last modified: 2025-02-16

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Utf8.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_BooleanValue
Arcadia_isUtf8
  (
    Arcadia_Process* process,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes,
    Arcadia_SizeValue* numberOfSymbols
  )
{
  Arcadia_SizeValue numberOfSymbols1 = 0;
  uint8_t const* start = (uint8_t const*)bytes;
  uint8_t const* end = start + numberOfBytes;
  uint8_t const* current = start;

  while (current != end) {
    uint8_t x = (*current);
    if (x <= 0x7f) {
      current += 1;
      numberOfSymbols1++;
    } else if (x <= 0x7ff) {
      if (end - current < 2) {
        if (numberOfSymbols) {
          *numberOfSymbols = numberOfSymbols1;
        }
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 2; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
          return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0xffff) {
      if (end - current < 3) {
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 3; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
         return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else if (x <= 0x10ffff) {
      if (end - current < 4) {
        if (numberOfSymbols) {
          *numberOfSymbols = numberOfSymbols1;
        }
        return Arcadia_BooleanValue_False;
      }
      for (Arcadia_SizeValue i = 1; i < 4; ++i) {
        current++;
        x = *current;
        if (0x80 != (x & 0xc0)) {
          if (numberOfSymbols) {
            *numberOfSymbols = numberOfSymbols1;
          }
          return Arcadia_BooleanValue_False;
        }
      }
      current++;
      numberOfSymbols1++;
    } else {
      return Arcadia_BooleanValue_False;
    }
  }
  if (numberOfSymbols) {
    *numberOfSymbols = numberOfSymbols1;
  }
  return Arcadia_BooleanValue_True;
}

void
Arcadia_Utf8_encodeCodePoints
  ( 
    Arcadia_Process* process,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints,
    void* callbackContext,
    void (*callbackFunction)(Arcadia_Process* process, void* callbackContext, Arcadia_Natural8Value const* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
  if (!numberOfCodePoints) {
    return;
  }
  for (Arcadia_SizeValue i = 0, n = numberOfCodePoints; i < n; ++i) {
    Arcadia_Natural32Value codePoint = codePoints[i];
    if (codePoint <= 0x7f) {
      Arcadia_Natural8Value x[1];
      x[0] = (codePoint & 0b1111111);
      (*callbackFunction)(process, callbackContext, &x[0], Arcadia_SizeValue_Literal(1));
    } else if (/*0x80 <=*/ codePoint <= 0x7ff) {
      // This CP uses the lower 11 bit of the 32 Bit number.
      // The first 5 of these bits are stored in the first Byte.
      // The last 6 of these bits are stored in the second Byte.
      Arcadia_Natural8Value x[2];
      x[0] = (codePoint & 0b11111000000) >> 6;
      x[1] = (codePoint & 0b00000111111) >> 0;
      // OR in 1100.0000.
      x[0] |= 0b11000000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      (*callbackFunction)(process, callbackContext, &x[0], Arcadia_SizeValue_Literal(2));
    } else if (/*0x800 <=*/ codePoint <= 0xffff) {
      // This CP uses the lower 16 bit of the 32 Bit number.
      // The first 4 of these bits are stored in the first Byte.
      // The next 6 of these bits are stored in the second Byte.
      // The last 6 of these bits are stored in teh third Byte.
      Arcadia_Natural8Value x[3];
      x[0] = (codePoint & 0b1111000000000000) >> 12;
      x[1] = (codePoint & 0b0000111111000000) >> 6;
      x[2] = (codePoint & 0b0000000000111111) >> 0;
      // OR in 1110.0000.
      x[0] |= 0b11100000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      x[2] |= 0b10000000;
      (*callbackFunction)(process, callbackContext, &x[0], Arcadia_SizeValue_Literal(3));
    } else if (/*0x10000 <=*/ codePoint <= 0x10FFFF) {
      // This CP uses the lower 21 Bit of the code point.
      // The first 3 are stored in the first Byte.
      // The next 6 are stored in the second Byte.
      // The next 6 are stored in the third Byte.
      // The last 6 are stored in the fourth Byte.
      Arcadia_Natural8Value x[4];
      x[0] = (codePoint & 0b111000000000000000000) >> 18;
      x[1] = (codePoint & 0b000111111000000000000) >> 12;
      x[2] = (codePoint & 0b000000000111111000000) >> 6;
      x[3] = (codePoint & 0b000000000000000111111) >> 0;
      // OR in 1111.0000.
      x[0] |= 0b1110000;
      // OR in 1000.0000.
      x[1] |= 0b10000000;
      x[2] |= 0b10000000;
      x[3] |= 0b10000000;
      (*callbackFunction)(process, callbackContext, &x[0], Arcadia_SizeValue_Literal(4));
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(Arcadia_Process_getThread(process));
    }
  }
}

void
Arcadia_Utf8_encodeBytes
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value const* bytes,
    Arcadia_SizeValue numberOfBytes,
    void* callbackContext,
    void (*callbackFunction)(Arcadia_Process*, void* callbackContext, Arcadia_Natural8Value const* bytes, Arcadia_SizeValue numberOfBytes)
  )
{
  if (!numberOfBytes) {
    return;
  }
  for (Arcadia_Natural8Value const* current = (Arcadia_Natural8Value const*)bytes, *end = (Arcadia_Natural8Value const*)bytes + numberOfBytes; current != end; ) {
    Arcadia_Natural8Value x = *current;
    if (x <= 0x7f) {
      (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
      current++;
    } else if (x <= 0x7ff) {
      (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
      if (end - current < 2) {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      current++;
      for (size_t i = 1; i < 2; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
        }
        (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
        current++;
      }
    } else if (x <= 0xffff) {
      (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
      if (end - current < 3) {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      current++;
      for (size_t i = 1; i < 3; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
        }
        (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
        current++;
      }
    } else if (x <= 0x10ffff) {
      (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
      if (end - current < 4) {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
        Arcadia_Thread_jump(Arcadia_Process_getThread(process));
      }
      current++;
      for (size_t i = 1; i < 4; ++i) {
        if (0x80 != (*current) & 0xc0) {
          Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
          Arcadia_Thread_jump(Arcadia_Process_getThread(process));
        }
        (*callbackFunction)(process, callbackContext, current, Arcadia_SizeValue_Literal(1));
        current++;
      }
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_EncodingInvalid);
      Arcadia_Thread_jump(Arcadia_Process_getThread(process));
    }
  }
}
