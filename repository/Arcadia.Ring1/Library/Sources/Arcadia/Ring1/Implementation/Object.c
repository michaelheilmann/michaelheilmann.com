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

// At R_startupTypes(), we register R.Internal.TypeNode as an ARMS type.
// When we add such a type node, then it is locked.
// On R_shutdownTypes(), all type nodes are unlocked and ARMS is run.


#include "Arcadia/Ring1/Implementation/Object.h"

#include "Arcadia/Ring1/Implementation/ArmsIntegration.h"
#include "Arcadia/Ring1/Implementation/Atoms.h"
#include "Arcadia/Ring1/Include.h"
#include <stdio.h>

static void
R_Object_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Object_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  );

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Object_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = &equalTo,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = &hash,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = &notEqualTo,
  .or = NULL,
  .subtract = NULL,
};

void
R_Object_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Object* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = Arcadia_getType(process, u8"Arcadia.Object", sizeof(u8"Arcadia.Object") - 1);
  R_Object_setType(process, _self, _type);
}

static void
equalTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(other)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getObjectReferenceValue(self) == Arcadia_Value_getObjectReferenceValue(other));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
}

static void
hash
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self
  )
{
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)(uintptr_t)Arcadia_Value_getObjectReferenceValue(self));
}

static void
notEqualTo
  (
    Arcadia_Process* process,
    R_Value* target,
    R_Value const* self,
    R_Value const* other
  )
{
  if (!Arcadia_Value_isObjectReferenceValue(other)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getObjectReferenceValue(self) != Arcadia_Value_getObjectReferenceValue(other));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
}

#define ObjectTypeName u8"Arcadia.Object"

typedef struct ObjectTag ObjectTag;

struct ObjectTag {
  Arcadia_TypeValue type;
};

static bool g_objectRegistered = false;

static void
onObjectTypeRemoved
  (
    Arcadia_Process* process,
    uint8_t const* name,
    size_t nameLength
  );

static void
onFinalizeObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
onVisitObject
  (
    Arcadia_Process* process,
    void* object
  );

static void
onObjectTypeRemoved
  (
    Arcadia_Process* process,
    const uint8_t* name,
    size_t nameLength
  )
{
  g_objectRegistered = false;
}

static void
onFinalizeObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  ObjectTag* objectTag = (ObjectTag*)object;
  Arcadia_TypeValue type = (Arcadia_TypeValue)objectTag->type;
  if (Arcadia_Arms_unlock(process, type)) {
    fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
  }
  if (type == _Arcadia_Memory_getType(process)) {
    return;
  }
  while (type) {
    Arcadia_Type_DestructObjectCallbackFunction* destruct = Arcadia_Type_getDestructObjectCallbackFunction(type);
    if (destruct) {
      destruct(process, ((ObjectTag*)object) + 1);
    }

    type = Arcadia_Type_getParentObjectType(type);
    objectTag->type = type;
  }
}

static void
onVisitObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  ObjectTag* objectTag = (ObjectTag*)object;
  Arcadia_TypeValue type = (Arcadia_TypeValue)objectTag->type;
  if (type == _Arcadia_Memory_getType(process)) {
    return;
  }
  while (type) {
    Arcadia_Type_VisitObjectCallbackFunction* visit = Arcadia_Type_getVisitObjectCallbackFunction(type);
    if (visit) {
      visit(process, ((ObjectTag*)object) + 1);
    }
    type = Arcadia_Type_getParentObjectType(type);
  }
}

void*
R_allocateObject
  (
    Arcadia_Process* process,
    Arcadia_TypeValue type,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  if (!type) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isObjectKind(type)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }

  Arcadia_Type* memoryType = _Arcadia_Memory_getType(process);

  ObjectTag* tag = NULL;
  if (SIZE_MAX - sizeof(ObjectTag) < Arcadia_Type_getValueSize(type)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_allocate_nojump(process, &tag, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(ObjectTag) + Arcadia_Type_getValueSize(type))) {
    Arcadia_Process_jump(process);
  }
  tag->type = memoryType;
  if (Arcadia_Arms_lock(process, memoryType)) {
    fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
  }
  R_Value selfValue = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)(R_Object*)(tag + 1) };
  Arcadia_Type_getOperations(type)->objectTypeOperations->construct(process, &selfValue, numberOfArgumentValues, &argumentValues[0]);
  return (void*)(tag + 1);
}

static Arcadia_TypeValue g__R_Object_type = NULL;

static void
typeDestructing
  (
    void* context
  )
{ g__R_Object_type = NULL; }

Arcadia_TypeValue
_R_Object_getType
  (
    Arcadia_Process* process
  )
{
  if (!g_objectRegistered) {
    if (!Arcadia_Arms_registerType_nojump(process, ObjectTypeName, sizeof(ObjectTypeName) - 1, process, &onObjectTypeRemoved, &onVisitObject, &onFinalizeObject)) {
      Arcadia_Process_jump(process);
    }
    g_objectRegistered = Arcadia_BooleanValue_True;
  }
  if (!g__R_Object_type) {
    g__R_Object_type = Arcadia_registerObjectType(process, ObjectTypeName, sizeof(ObjectTypeName) - 1, sizeof(R_Object), NULL, &_typeOperations, &typeDestructing);
  }
  return g__R_Object_type;
}

void
R_Object_setType
  (
    Arcadia_Process* process,
    void* self,
    Arcadia_TypeValue type
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  if (type) {
    if (Arcadia_Arms_lock(process, type)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  if (objectTag->type) {
    if (Arcadia_Arms_unlock(process, objectTag->type)) {
      fprintf(stderr, "%s:%d: <error>\n", __FILE__, __LINE__);
    }
  }
  objectTag->type = type;
}

void
R_Object_visit
  (
    Arcadia_Process* process,
    void* self
  )
{
  ObjectTag* tag = ((ObjectTag*)self) - 1;
  Arcadia_Arms_visit(process, tag->type);
  Arcadia_Arms_visit(process, tag);
}

void
R_Object_lock
  (
    Arcadia_Process* process,
    void* self
  )
{
  Arcadia_Status status = Arcadia_Arms_lock(process, ((ObjectTag*)self) - 1);
  if (status) {
    Arcadia_Process_setStatus(process, status);
    Arcadia_Process_jump(process);
  }
}

void
R_Object_unlock
  (
    Arcadia_Process* process,
    void* self
  )
{
  Arcadia_Status status = Arcadia_Arms_unlock(process, ((ObjectTag*)self) - 1);
  if (status) {
    Arcadia_Process_setStatus(process, status);
    Arcadia_Process_jump(process);
  }
}

Arcadia_TypeValue
R_Object_getType
  (
    void* self
  )
{
  ObjectTag* objectTag = ((ObjectTag*)self) - 1;
  return objectTag->type;
}

Arcadia_SizeValue
R_Object_hash
  (
    Arcadia_Process* process,
    R_Object* self
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  R_Value resultValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  operations->hash(process, &resultValue, &selfValue);
  return Arcadia_Value_getSizeValue(&resultValue);
}

R_Object*
R_Object_add
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  R_Value resultValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  operations->add(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getObjectReferenceValue(&resultValue);
}

R_Object*
R_Object_subtract
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  R_Value resultValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  operations->subtract(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getObjectReferenceValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_equalTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->equalTo(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_greaterThan
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->greaterThan(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_greaterThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->greaterThanOrEqualTo(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_lowerThan
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->lowerThan(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_lowerThanOrEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->lowerThanOrEqualTo(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

Arcadia_BooleanValue
R_Object_notEqualTo
  (
    Arcadia_Process* process,
    R_Object* self,
    R_Value const* other
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->notEqualTo(process, &resultValue, &selfValue, other);
  return Arcadia_Value_getBooleanValue(&resultValue);
}

R_String*
R_Object_toString
  (
    Arcadia_Process* process,
    R_Object* self
  )
{
  Arcadia_TypeValue type = R_Object_getType(self);
  Arcadia_Type_Operations const* operations = Arcadia_Type_getOperations(type);
  R_Value selfValue;
  Arcadia_Value_setObjectReferenceValue(&selfValue, (Arcadia_ObjectReferenceValue)self);
  R_Value resultValue;
  operations->toString(process, &resultValue, &selfValue);
  return Arcadia_Value_getObjectReferenceValue(&resultValue);
}