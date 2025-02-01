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

#include "R/List.h"

#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

static void
R_List_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
R_List_ensureInitialized
  (
    Arcadia_Process* process
  );

static void
R_List_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_List_destruct
  (
    Arcadia_Process* process,
    R_List* self
  );

static void
R_List_visit
  (
    Arcadia_Process* process,
    R_List* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_List_constructImpl,
  .destruct = &R_List_destruct,
  .visit = &R_List_visit,
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

Rex_defineObjectType(u8"Arcadia.Library.List", R_List, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_List_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_SizeValue requiredFreeCapacity
  )
{
  Arcadia_SizeValue newAvailableFreeCapacity = self->capacity - self->size;
  Arcadia_SizeValue oldCapacity = self->capacity;
  Arcadia_SizeValue newCapacity = oldCapacity;
  while (requiredFreeCapacity > newAvailableFreeCapacity) {
    oldCapacity = self->capacity;
    newCapacity = oldCapacity;
    if (oldCapacity > g_maximumCapacity / 2) {
      // If oldCapacity > maximumCapacity / 2 holds then oldCapacity * 2 > maximumCapacity holds.
      // Consequently, we cannot double the capacity. Try to saturate the capacity.
      if (oldCapacity == g_maximumCapacity) {
        Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
        Arcadia_Process_jump(process);
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  Arcadia_Process_reallocateUnmanaged(process, &self->elements, sizeof(Arcadia_Value) * newCapacity);
  self->capacity = newCapacity;
}

static void
R_List_ensureInitialized
  (
    Arcadia_Process* process
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Arcadia_Value);
    if (g_maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    g_initialized = Arcadia_BooleanValue_True;
  }
}

static void
R_List_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_List* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_List_getType(process);
  R_List_ensureInitialized(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->elements = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  Arcadia_Process_allocateUnmanaged(process, &_self->elements, sizeof(Arcadia_Value) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    Arcadia_Value_setVoidValue(_self->elements + i, Arcadia_VoidValue_Void);
  }
  Arcadia_Object_setType(process, _self, _type);
}

static void
R_List_destruct
  (
    Arcadia_Process* process,
    R_List* self
  )
{
  if (self->elements) {
    Arcadia_Process_deallocateUnmanaged(process, self->elements);
    self->elements = NULL;
  }
}

static void
R_List_visit
  (
    Arcadia_Process* process,
    R_List* self
  )
{
  if (self->elements) {
    for (Arcadia_SizeValue i = 0, n = self->size; i < n; ++i) {
      Arcadia_Value_visit(process, self->elements + i);
    }
  }
}

R_List*
R_List_create
  (
    Arcadia_Process* process
  )
{
  R_List_ensureInitialized(process);
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_List* self = R_allocateObject(process, _R_List_getType(process), 0, &argumentValues[0]);
  return self;
}

void
R_List_clear
  (
    R_List* self
  )
{ self->size = 0; }

Arcadia_SizeValue
R_List_getSize
  (
    R_List* self
  )
{ return self->size; }

void
R_List_append
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_Value value
  )
{
  R_List_insertAt(process, self, self->size, value);
}

void
R_List_prepend
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_Value value
  )
{
  R_List_insertAt(process, self, Arcadia_SizeValue_Literal(0), value);
}

void
R_List_insertAt
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{
  if (index > self->size) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (self->capacity == self->size) {
    R_List_ensureFreeCapacity(process, self, Arcadia_SizeValue_Literal(1));
  }
  if (index < self->size) {
    c_memmove(self->elements + index + 1,
              self->elements + index + 0,
              sizeof(Arcadia_Value) * (self->size - index));
  }
  self->elements[index] = value;
  self->size++;
}

Arcadia_Value
R_List_getAt
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_SizeValue index
  )
{
  if (index >= self->size) {
    Arcadia_Process_setStatus(process, Arcadia_Status_OperationInvalid);
    Arcadia_Process_jump(process);
  }
  return self->elements[index];
}

void
R_List_remove
  (
    Arcadia_Process* process,
    R_List* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  )
{
  if (!self) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if ((Arcadia_SizeValue_Maximum - count) < index) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if ((index + count) > self->size) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue tailLength = (self->size - index) - count;
  if (tailLength) {
    Arcadia_SizeValue tailStart = index + count;
    c_memmove(self->elements + index, self->elements + tailStart, tailLength * sizeof(Arcadia_Value));
  }
  self->size -= count;
}

#define Define(Type, Suffix, Variable) \
  void \
  R_List_append##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    R_List_append(process, self, value); \
  } \
\
  void \
  R_List_prepend##Suffix##Value \
    ( \
      Arcadia_Process* process, \
      R_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    R_List_prepend(process, self, value); \
  } \
\
  Arcadia_BooleanValue \
  R_List_is##Suffix##ValueAt \
    ( \
      Arcadia_Process* process, \
      R_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    return Arcadia_Value_is##Suffix##Value(self->elements + index); \
  } \
\
  Type##Value \
  R_List_get##Suffix##ValueAt \
    ( \
      Arcadia_Process* process, \
      R_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    if (index >= self->size) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    Arcadia_Value* element = self->elements + index; \
    if (!Arcadia_Value_is##Suffix##Value(element)) { \
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Process_jump(process); \
    } \
    return Arcadia_Value_get##Suffix##Value(element); \
  }

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_ForeignProcedure, ForeignProcedure, foreignProcedure)
Define(Arcadia_Integer8, Integer8, integer8)
Define(Arcadia_Integer16, Integer16, integer16)
Define(Arcadia_Integer32, Integer32, integer32)
Define(Arcadia_Integer64, Integer64, integer64)
Define(Arcadia_Natural8, Natural8, natural8)
Define(Arcadia_Natural16, Natural16, natural16)
Define(Arcadia_Natural32, Natural32, natural32)
Define(Arcadia_Natural64, Natural64, natural64)
Define(Arcadia_ObjectReference, ObjectReference, objectReference)
Define(Arcadia_Size, Size, size)
Define(Arcadia_Void, Void, void)

#undef Define