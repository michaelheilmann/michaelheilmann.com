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

// Last modified: 2024-09-28

#include "Arcadia/Ring1/Implementation/countLeadingZeroes.h"

#include "Arcadia/Ring1/Include.h"
#include "R/Value.h"

#if R_Configuration_CompilerC == R_Configuration_CompilerC_Msvc
#include <intrin.h>
#endif

Arcadia_SizeValue
Arcadia_countLeadingZeroesInteger8Value
  (
    Arcadia_Process* process,
    Arcadia_Integer8Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countLeadingZeroesNatural8Value(process, (Arcadia_Natural8Value)x);
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesInteger16Value
  (
    Arcadia_Process* process,
    Arcadia_Integer16Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countLeadingZeroesNatural16Value(process, (Arcadia_Natural16Value)x);
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesInteger32Value
  (
    Arcadia_Process* process,
    Arcadia_Integer32Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countLeadingZeroesNatural32Value(process, (Arcadia_Natural32Value)x);
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesInteger64Value
  (
    Arcadia_Process* process,
    Arcadia_Integer64Value x
  )
{
  // Cast is defined behavior: Two's complete cast signed to unsigned is Bit reinterpretation when 2-complement.
  return Arcadia_countLeadingZeroesNatural64Value(process, (Arcadia_Natural64Value)x);
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesNatural8Value
  (
    Arcadia_Process* process,
    Arcadia_Natural8Value x
  )
{
  // Maps a value from 0000 (0x0) to 1111 (0xf) the value's number of leading zero bits.
  static const short lookup[16] = {
    4, //  0: 0000
    3, //  1: 0001
    2, //  2: 0010
    2, //  3: 0011
    1, //  4: 0100
    1, //  5: 0101
    1, //  6: 0110
    1, //  7: 0111
    0, //  8: 1000
    0, //  9: 1001
    0, // 10: 1010
    0, // 11: 1011
    0, // 12: 1100
    0, // 13: 1101
    0, // 14: 1110
    0, // 15: 1111
  };
  Arcadia_Natural8Value upper = (x & 0xf0) >> 4;
  Arcadia_Natural8Value lower = (x & 0x0f) >> 0;
  return upper ? lookup[upper] : 4 + lookup[lower];
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesNatural16Value
  (
    Arcadia_Process* process,
    Arcadia_Natural16Value x
  )
{
  Arcadia_Natural16Value t;
  t = (x & 0xff00) >> 8;
  if (t) return Arcadia_countLeadingZeroesNatural8Value(process, (Arcadia_Natural8Value)t);
  t = (x & 0x00ff) >> 0;
  return 8 + Arcadia_countLeadingZeroesNatural8Value(process, (Arcadia_Natural8Value)t);
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesNatural32Value
  (
    Arcadia_Process* process,
    Arcadia_Natural32Value x
  )
{
#if R_Configuration_CompilerC == R_Configuration_CompilerC_Msvc
  unsigned long n;
  if (_BitScanReverse(&n, x)) {
    // x was not zero.
    return (short)32 - ((short)n + 1);
  } else {
    // x was zero.
    return (short)32;
  }
#else
  Arcadia_Natural32Value t;
  t = (x & 0xffff0000) >> 16;
  if (t) return Arcadia_countLeadingZeroesNatural16Value(process, (Arcadia_Natural16Value)t);
  t = (x & 0x0000ffff) >> 0;
  return 16 + Arcadia_countLeadingZeroesNatural16Value(process, (Arcadia_Natural16Value)t);
#endif
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesNatural64Value
  (
    Arcadia_Process* process,
    Arcadia_Natural64Value x
  )
{
  Arcadia_Natural32Value hi = (x & 0xffffffff00000000) >> 32;
  Arcadia_Natural32Value lo = (x & 0x00000000ffffffff) >> 0;
  if (hi) {
    return Arcadia_countLeadingZeroesNatural32Value(process, hi);
  } else {
    return 32 + Arcadia_countLeadingZeroesNatural32Value(process, lo);
  }
}

Arcadia_SizeValue
Arcadia_countLeadingZeroesSizeValue
  (
    Arcadia_Process* process,
    Arcadia_SizeValue x
  )
{
#if R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X64
  return Arcadia_countLeadingZeroesNatural64Value(process, x);
#elif R_Configuration_InstructionSetArchitecture == R_Configuration_InstructionSetArchitecture_X86
  return Arcadia_countLeadingZeroesNatural32Value(process, x);
#else
  #error("environment not (yet) supported")
#endif
}