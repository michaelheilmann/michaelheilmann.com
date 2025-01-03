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

// Last modified: 2024-10-07

#include "R/List.h"

#include "R/ArmsIntegration.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

static R_BooleanValue g_initialized = R_BooleanValue_False;

static R_SizeValue g_minimumCapacity = -1;
static R_SizeValue g_maximumCapacity = -1;

static void
R_List_ensureFreeCapacity
  (
    R_List* self,
    R_SizeValue requiredFreeCapacity
  );

static void
R_List_ensureInitialized
  (
  );

static void
R_List_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_List_destruct
  (
    R_List* self
  );

static void
R_List_visit
  (
    R_List* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_List_constructImpl,
  .destruct = &R_List_destruct,
  .visit = &R_List_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.List", R_List, "R.Object", R_Object, &_typeOperations);

static void
R_List_ensureFreeCapacity
  (
    R_List* self,
    R_SizeValue requiredFreeCapacity
  )
{
  R_SizeValue newAvailableFreeCapacity = self->capacity - self->size;
  R_SizeValue oldCapacity = self->capacity;
  R_SizeValue newCapacity = oldCapacity;
  while (requiredFreeCapacity > newAvailableFreeCapacity) {
    oldCapacity = self->capacity;
    newCapacity = oldCapacity;
    if (oldCapacity > g_maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_maximumCapacity) {
        R_setStatus(R_Status_AllocationFailed);
        R_jump();
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  if (!R_reallocateUnmanaged_nojump(&self->elements, sizeof(R_Value) * newCapacity)) {
    R_jump();
  }
  self->capacity = newCapacity;
}

static void
R_List_ensureInitialized
  (
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(R_Value);
    if (g_maximumCapacity > R_Integer32Value_Maximum) {
      g_maximumCapacity = R_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    }
    g_initialized = R_BooleanValue_True;
  }
}

static void
R_List_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_List* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_List_getType();
  R_List_ensureInitialized();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  if (!R_allocateUnmanaged_nojump(&_self->elements, sizeof(R_Value) * _self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    R_Value_setVoidValue(_self->elements + i, R_VoidValue_Void);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_List_destruct
  (
    R_List* self
  )
{
  if (self->elements) {
    R_deallocateUnmanaged_nojump(self->elements);
    self->elements = NULL;
  }
}

static void
R_List_visit
  (
    R_List* self
  )
{
  if (self->elements) {
    for (R_SizeValue i = 0, n = self->size; i < n; ++i) {
      R_Value_visit(self->elements + i);
    }
  }
}

R_List*
R_List_create
  (
  )
{
  R_List_ensureInitialized();
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_List* self = R_allocateObject(_R_List_getType(), 0, &argumentValues[0]);
  R_Value selfValue = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)self };
  R_List_constructImpl(&selfValue, 0, &argumentValues[0]);
  return self;
}

void
R_List_clear
  (
    R_List* self
  )
{ self->size = 0; }

R_SizeValue
R_List_getSize
  (
    R_List* self
  )
{ return self->size; }

void
R_List_append
  (
    R_List* self,
    R_Value value
  )
{
  R_List_insertAt(self, self->size, value);
}

void
R_List_prepend
  (
    R_List* self,
    R_Value value
  )
{
  R_List_insertAt(self, R_SizeValue_Literal(0), value);
}

void
R_List_insertAt
  (
    R_List* self,
    R_SizeValue index,
    R_Value value
  )
{
  if (index > self->size) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (self->capacity == self->size) {
    R_List_ensureFreeCapacity(self, R_SizeValue_Literal(1));
  }
  if (index < self->size) {
    c_memmove(self->elements + index + 1,
              self->elements + index + 0,
              sizeof(R_Value) * (self->size - index));
  }
  self->elements[index] = value;
  self->size++;
}

R_Value
R_List_getAt
  (
    R_List* self,
    R_SizeValue index
  )
{
  if (index >= self->size) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  return self->elements[index];
}

void
R_List_remove
  (
    R_List* self,
    R_SizeValue index,
    R_SizeValue count
  )
{
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if ((R_SizeValue_Maximum - count) < index) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if ((index + count) > self->size) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_SizeValue tailLength = (self->size - index) - count;
  if (tailLength) {
    R_SizeValue tailStart = index + count;
    c_memmove(self->elements + index, self->elements + tailStart, tailLength * sizeof(R_Value));
  }
  self->size -= count;
}

#define Define(Suffix, Prefix) \
  void \
  R_List_append##Suffix##Value \
    ( \
      R_List* self, \
      R_##Suffix##Value prefix##Value \
    ) \
  { \
    R_Value value; \
    R_Value_set##Suffix##Value(&value, prefix##Value); \
    R_List_append(self, value); \
  } \
\
  void \
  R_List_prepend##Suffix##Value \
    ( \
      R_List* self, \
      R_##Suffix##Value prefix##Value \
    ) \
  { \
    R_Value value; \
    R_Value_set##Suffix##Value(&value, prefix##Value); \
    R_List_prepend(self, value); \
  } \
\
  R_BooleanValue \
  R_List_is##Suffix##ValueAt \
    ( \
      R_List* self, \
      R_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    return R_Value_is##Suffix##Value(self->elements + index); \
  } \
\
  R_##Suffix##Value \
  R_List_get##Suffix##ValueAt \
    ( \
      R_List* self, \
      R_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    R_Value* element = self->elements + index; \
    if (!R_Value_is##Suffix##Value(element)) { \
      R_setStatus(R_Status_ArgumentValueInvalid); \
      R_jump(); \
    } \
    return R_Value_get##Suffix##Value(element); \
  }

Define(Boolean, boolean)
Define(ForeignProcedure, foreignProcedure)
Define(Integer8, integer8)
Define(Integer16, integer16)
Define(Integer32, integer32)
Define(Integer64, integer64)
Define(Natural8, natural8)
Define(Natural16, natural16)
Define(Natural32, natural32)
Define(Natural64, natural64)
Define(ObjectReference, objectReference)
Define(Size, size)
Define(Void, void)

#undef Define