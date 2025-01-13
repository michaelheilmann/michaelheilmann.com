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

// Last modified: 2024-10-07

#include "R/Utf8ByteBufferReader.h"

#include "R/Utf8.h"

#define CodePoint_Start (R_Utf8CodePoint_Last + 1)
#define CodePoint_End (R_Utf8CodePoint_Last + 2)
#define CodePoint_Error (R_Utf8CodePoint_Last + 3)

/// @code
/// construct(source:ByteBuffer)
/// @endcode
static void
R_Utf8ByteBufferReader_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Utf8ByteBufferReader_visit
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  );

static void
R_Utf8ByteBufferReader_nextImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  );

static Arcadia_Natural32Value
R_Utf8ByteBufferReader_getCodePointImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  );

static Arcadia_BooleanValue
R_Utf8ByteBufferReader_hasCodePointImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  );

static void
R_Utf8ByteBufferReader_visit
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  )
{
  Arcadia_Object_visit(process, self->source);
}

static void
R_Utf8ByteBufferReader_nextImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_End || self->codePoint == CodePoint_Error) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue n = R_ByteBuffer_getSize(self->source);
  if (self->byteIndex == n) {
    self->codePoint = CodePoint_End;
    return;
  }
  Arcadia_Natural32Value codePoint;
  Arcadia_Natural8Value x = R_ByteBuffer_getAt(process, self->source, self->byteIndex);
  if (x <= 0b01111111) {
    codePoint = x;
    self->byteIndex += 1;
    self->codePoint = codePoint;
  } else if (x <= 0b11011111) {
    codePoint = x & 0b00011111;
    if (n - self->byteIndex < 2) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    for (size_t i = 1; i < 2; ++i) {
      x = R_ByteBuffer_getAt(process, self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->byteIndex += 2;
    self->codePoint = codePoint;
  } else if (x <= 0b11101111) {
    codePoint = x & 0b00001111;
    if (n - self->byteIndex < 3) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    for (size_t i = 1; i < 3; ++i) {
      x = R_ByteBuffer_getAt(process, self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      codePoint <<= 6;
      codePoint |= x & 0b00111111;
    }
    self->byteIndex += 3;
    self->codePoint = codePoint;
  } else if (x <= 0b11110111) {
    codePoint = x & 0b00000111;
    if (n - self->byteIndex < 4) {
      Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
      Arcadia_Process_jump(process);
    }
    for (size_t i = 1; i < 4; ++i) {
      x = R_ByteBuffer_getAt(process, self->source, self->byteIndex + i);
      if (0x80 != x & 0xc0) {
        Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
        Arcadia_Process_jump(process);
      }
      codePoint <<= 6;
      codePoint |= x;
    }
    self->byteIndex += 4;
    self->codePoint = codePoint;
  } else {
    Arcadia_Process_setStatus(process, Arcadia_Status_EncodingInvalid);
    Arcadia_Process_jump(process);
  }
}

static Arcadia_Natural32Value
R_Utf8ByteBufferReader_getCodePointImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_Start || self->codePoint == CodePoint_End) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  return self->codePoint;
}

static Arcadia_BooleanValue
R_Utf8ByteBufferReader_hasCodePointImpl
  (
    Arcadia_Process* process,
    R_Utf8ByteBufferReader* self
  )
{
  if (self->codePoint == CodePoint_Start) {
    R_Utf8ByteBufferReader_nextImpl(process, self);
  }
  return CodePoint_End != self->codePoint;
}

static Arcadia_SizeValue
R_Utf8ByteBufferReader_getByteIndexImpl
  (
    R_Utf8ByteBufferReader* self
  )
{ return self->byteIndex; }

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Utf8ByteBufferReader_constructImpl,
  .destruct = NULL,
  .visit = &R_Utf8ByteBufferReader_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"R.Utf8ByteBufferReader", R_Utf8ByteBufferReader, u8"R.Utf8Reader", R_Utf8Reader, &_typeOperations);

void
R_Utf8ByteBufferReader_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Utf8ByteBufferReader* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Utf8ByteBufferReader_getType(process);
  {
    Arcadia_Value argumentValues[] =  { { .tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
    Rex_superTypeConstructor(process, _type, self, 0, & argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(Arcadia_Value_getType(process, &argumentValues[0]), _R_ByteBuffer_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  _self->source = Arcadia_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->byteIndex = 0;
  _self->codePoint = CodePoint_Start;
  ((R_Utf8Reader*)_self)->getByteIndex = (Arcadia_SizeValue(*)(R_Utf8Reader*)) & R_Utf8ByteBufferReader_getByteIndexImpl;
  ((R_Utf8Reader*)_self)->getCodePoint = (Arcadia_Natural32Value (*)(Arcadia_Process*,R_Utf8Reader*)) & R_Utf8ByteBufferReader_getCodePointImpl;
  ((R_Utf8Reader*)_self)->hasCodePoint = (Arcadia_BooleanValue (*)(Arcadia_Process*,R_Utf8Reader*)) &R_Utf8ByteBufferReader_hasCodePointImpl;
  ((R_Utf8Reader*)_self)->next = (void (*)(Arcadia_Process*, R_Utf8Reader*)) &R_Utf8ByteBufferReader_nextImpl;
  Arcadia_Object_setType(process, _self, _type);
}

R_Utf8ByteBufferReader*
R_Utf8ByteBufferReader_create
  (
    Arcadia_Process* process,
    R_ByteBuffer* source
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = source }, };
  R_Utf8ByteBufferReader* self = R_allocateObject(process, _R_Utf8ByteBufferReader_getType(process), 1, &argumentValues[0]);
  return self;
}
