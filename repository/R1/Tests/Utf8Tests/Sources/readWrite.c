// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-08-27

#include "readWrite.h"

#include "R.h"

void
R1_Tests_Utf8_readWrite
  (
    char const* p,
    size_t n
  )
{
  R_ByteBuffer* sourceByteBuffer = R_ByteBuffer_create();
  R_ByteBuffer_append_pn(sourceByteBuffer, p, n);
  R_ByteBuffer* targetByteBuffer = R_ByteBuffer_create();
  R_Utf8Reader* reader = (R_Utf8Reader*)R_Utf8ByteBufferReader_create(sourceByteBuffer);
  R_Utf8Writer* writer = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(targetByteBuffer);
  while (R_Utf8Reader_hasCodePoint(reader)) {
    R_Natural32Value codePoint = R_Utf8Reader_getCodePoint(reader);
    R_Utf8Writer_writeCodePoints(writer, &codePoint, 1);
    R_Utf8Reader_next(reader);
  }
  if (!R_ByteBuffer_isEqualTo(sourceByteBuffer, targetByteBuffer)) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
}
