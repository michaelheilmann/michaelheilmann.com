// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Collections/List.h"

#include "Arcadia/Ring2/Include.h"

static void
Arcadia_List_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_List_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.List", Arcadia_List,
                         u8"Arcadia.Collection", Arcadia_Collection,
                         &_typeOperations);

static void
Arcadia_List_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_List* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_List_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 0 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->getAt = NULL;
  self->insertAt = NULL;
  self->insertBack = NULL;
  self->insertFront = NULL;
  self->removeAt = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1);
}

Arcadia_Value
Arcadia_List_getAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index
  )
{ return self->getAt(thread, self, index); }

void
Arcadia_List_insertBack
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  )
{ self->insertBack(thread, self, value); }

void
Arcadia_List_insertFront
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value value
  )
{ self->insertFront(thread, self, value); }

void
Arcadia_List_insertAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index,
    Arcadia_Value value
  )
{ self->insertAt(thread, self, index, value); }

void
Arcadia_List_removeAt
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue count
  )
{ self->removeAt(thread, self, index, count); }

#define Define(Type, Suffix, Variable) \
  void \
  Arcadia_List_insertBack##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_List_insertBack(thread, self, value); \
  } \
\
  void \
  Arcadia_List_insertFront##Suffix##Value \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Type##Value Variable##Value \
    ) \
  { \
    Arcadia_Value value; \
    Arcadia_Value_set##Suffix##Value(&value, Variable##Value); \
    Arcadia_List_insertFront(thread, self, value); \
  } \
\
  Arcadia_BooleanValue \
  Arcadia_List_is##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    Arcadia_Value v = Arcadia_List_getAt(thread, self, index); \
    return Arcadia_Value_is##Suffix##Value(&v); \
  } \
\
  Type##Value \
  Arcadia_List_get##Suffix##ValueAt \
    ( \
      Arcadia_Thread* thread, \
      Arcadia_List* self, \
      Arcadia_SizeValue index \
    ) \
  { \
    Arcadia_Value v = Arcadia_List_getAt(thread, self, index); \
    if (!Arcadia_Value_is##Suffix##Value(&v)) { \
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid); \
      Arcadia_Thread_jump(thread); \
    } \
    return Arcadia_Value_get##Suffix##Value(&v); \
  }

Define(Arcadia_Boolean, Boolean, boolean)
Define(Arcadia_BigInteger, BigInteger, bigInteger)
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

Arcadia_List*
Arcadia_List_filter
  (
    Arcadia_Thread* thread,
    Arcadia_List* self,
    Arcadia_Value context,
    Arcadia_BooleanValue(*predicate)(Arcadia_Thread* thread, Arcadia_Value context, Arcadia_Value value)
  )
{
  Arcadia_List* result = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)self); i < n; ++i) {
    Arcadia_Value v = Arcadia_List_getAt(thread, self, i);
    if ((*predicate)(thread, context, v)) {
      Arcadia_List_insertBack(thread, result, v);
    }
  }
  return result;
}
