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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/ByteBuffer.h"

static void
Arcadia_ByteBuffer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_ByteBuffer_destruct
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_ByteBuffer_constructImpl,
  .destruct = &Arcadia_ByteBuffer_destruct,
  .visit = NULL,
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

Rex_defineObjectType(u8"Arcadia.ByteBuffer", Arcadia_ByteBuffer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_ByteBuffer_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_ByteBuffer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_ByteBuffer_getType(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  Arcadia_Process_allocateUnmanaged(process, &_self->p, 0);
  Arcadia_Object_setType(process, _self, _type);
}

static void
Arcadia_ByteBuffer_destruct
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self
  )
{
  if (self->p) {
    Arcadia_Process_deallocateUnmanaged(process, self->p);
    self->p = NULL;
  }
}

Arcadia_ByteBuffer*
Arcadia_ByteBuffer_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Arcadia_ByteBuffer* self = R_allocateObject(process, _Arcadia_ByteBuffer_getType(process), 0, &argumentValues[0]);
  return self;
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_endsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_SizeValue d = self->sz - numberOfBytes;
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->p + d, bytes, numberOfBytes);
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_startsWith_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (self->sz < numberOfBytes) {
    return Arcadia_BooleanValue_False;
  }
  return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->p, bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_append_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_ByteBuffer_insert_pn(process, self, self->sz, bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_prepend_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_ByteBuffer_insert_pn(process, self, Arcadia_SizeValue_Literal(0), bytes, numberOfBytes);
}

void
Arcadia_ByteBuffer_insert_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self,
    Arcadia_SizeValue index,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes || index > self->sz) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!numberOfBytes) {
    return;
  }
  Arcadia_SizeValue freeCapacity = self->cp - self->sz;
  if (freeCapacity < numberOfBytes) {
    Arcadia_SizeValue additionalCapacity = numberOfBytes - freeCapacity;
    Arcadia_SizeValue oldCapacity = self->cp;
    if (SIZE_MAX - oldCapacity < additionalCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
      Arcadia_Process_jump(process);
    }
    Arcadia_SizeValue newCapacity = oldCapacity + additionalCapacity;
    Arcadia_Process_reallocateUnmanaged(process, &self->p, newCapacity);
    self->cp = newCapacity;
  }
  if (index < self->sz) {
    Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->p + index, self->p + index + numberOfBytes, self->sz - index);
  }
  Arcadia_Process1_copyMemory(Arcadia_Process_getProcess1(process), self->p + index, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    Arcadia_ByteBuffer const* other
  )
{
  if (self == other) {
    return Arcadia_BooleanValue_True;
  }
  if (self->sz == other->sz) {
    return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->p, other->p, self->sz);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

Arcadia_BooleanValue
Arcadia_ByteBuffer_isEqualTo_pn
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  if (!self || !bytes) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (self->sz == numberOfBytes) {
    return !Arcadia_Process1_compareMemory(Arcadia_Process_getProcess1(process), self->p, bytes, numberOfBytes);
  } else {
    return Arcadia_BooleanValue_False;
  }
}

void
Arcadia_ByteBuffer_clear
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* self
  )
{
  self->sz = 0;
}

Arcadia_SizeValue
Arcadia_ByteBuffer_getSize
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self
  )
{
  return self->sz;
}

Arcadia_SizeValue
Arcadia_ByteBuffer_getNumberOfBytes
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self
  )
{ return self->sz; }

Arcadia_Natural8Value const*
Arcadia_ByteBuffer_getBytes
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self
  )
{ return self->p; }

Arcadia_Natural8Value
Arcadia_ByteBuffer_getAt
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer const* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->sz) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return *(self->p + index);
}
