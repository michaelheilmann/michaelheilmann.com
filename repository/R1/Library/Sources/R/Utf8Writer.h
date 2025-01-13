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

// Last modified: 2024-09-22

#if !defined(R_UTF8WRITER_H_INCLUDED)
#define R_UTF8WRITER_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
typedef struct R_ByteBuffer R_ByteBuffer;

Rex_declareObjectType(u8"R.Utf8Writer", R_Utf8Writer, u8"Arcadia.Object");

struct R_Utf8Writer {
  Arcadia_Object _parent;
  void (*writeBytes)(Arcadia_Process*, R_Utf8Writer* self, const void* bytes, Arcadia_SizeValue numberOfBytes);
  void (*writeCodePoints)(Arcadia_Process*, R_Utf8Writer* self, Arcadia_Natural32Value const* codePoints, Arcadia_SizeValue numberOfCodePoints);
};

void
R_Utf8Writer_writeBytes
  (
    Arcadia_Process* process,
    R_Utf8Writer* self,
    const void* bytes,
    Arcadia_SizeValue numberOfBytes
  );

void
R_Utf8Writer_writeCodePoints
  (
    Arcadia_Process* process,
    R_Utf8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  );

#endif // R_UTF8WRITER_H_INCLUDED
