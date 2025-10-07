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
#include "Arcadia/Ring2/Collections/HashMap.h"

#include "Arcadia/Ring2/Include.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

struct _Arcadia_HashMap_Node {
  _Arcadia_HashMap_Node* next;
  Arcadia_SizeValue hash;
  Arcadia_Value key;
  Arcadia_Value value;
};

static void
Arcadia_HashMap_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
Arcadia_HashMap_ensureInitialized
  (
    Arcadia_Thread* thread
  );

static void
Arcadia_HashMap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static void
Arcadia_HashMap_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static void
Arcadia_HashMap_visit
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static void
Arcadia_HashMap_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static Arcadia_SizeValue
Arcadia_HashMap_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static Arcadia_BooleanValue
Arcadia_HashMap_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static Arcadia_Value
Arcadia_HashMap_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key
  );

static void
Arcadia_HashMap_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

static void
Arcadia_HashMap_setImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  );

static Arcadia_List*
Arcadia_HashMap_getValuesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static Arcadia_List*
Arcadia_HashMap_getKeysImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_HashMap_constructImpl,
  .destruct = &Arcadia_HashMap_destruct,
  .visit = &Arcadia_HashMap_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.HashMap", Arcadia_HashMap,
                         u8"Arcadia.Map", Arcadia_Map,
                         &_typeOperations);

static void
Arcadia_HashMap_ensureFreeCapacity
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
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
        Arcadia_Thread_setStatus(thread, Arcadia_Status_AllocationFailed);
        Arcadia_Thread_jump(thread);
      } else {
        newCapacity = g_maximumCapacity;
      }
    } else {
      newCapacity = oldCapacity * 2;
    }
    newAvailableFreeCapacity = newCapacity - self->size;
  }
  _Arcadia_HashMap_Node** oldBuckets = self->buckets;
  _Arcadia_HashMap_Node** newBuckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashMap_Node*) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      _Arcadia_HashMap_Node* node = oldBuckets[i];
      oldBuckets[i] = oldBuckets[i]->next;
      Arcadia_SizeValue j = node->hash % newCapacity;
      node->next = newBuckets[j];
      newBuckets[j] = node;
    }
  }
  Arcadia_Memory_deallocateUnmanaged(thread, oldBuckets);
  self->buckets = newBuckets;
  self->capacity = newCapacity;
}

static void
Arcadia_HashMap_ensureInitialized
  (
    Arcadia_Thread* thread
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(_Arcadia_HashMap_Node*);
    if (g_maximumCapacity > Arcadia_Integer32Value_Maximum) {
      g_maximumCapacity = Arcadia_Integer32Value_Maximum;
    }
    if (g_minimumCapacity > g_maximumCapacity) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    g_initialized = Arcadia_BooleanValue_True;
  }
}

static void
Arcadia_HashMap_destruct
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_HashMap_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
      node = NULL;
    }
  }
  if (self->buckets) {
    Arcadia_Memory_deallocateUnmanaged(thread, self->buckets);
    self->buckets = NULL;
  }
}

static void
Arcadia_HashMap_visit
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      _Arcadia_HashMap_Node* node = self->buckets[i];
      while (node) {
        Arcadia_Value_visit(thread, &node->key);
        Arcadia_Value_visit(thread, &node->value);
        node = node->next;
      }
    }
  }
}

static void
Arcadia_HashMap_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_HashMap_getType(thread);
  Arcadia_HashMap_ensureInitialized(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural8Value nargs = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 == nargs) {
    self->buckets = NULL;
    self->capacity = 0;
    self->size = 0;
    self->capacity = g_minimumCapacity;
    self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashMap_Node*) * self->capacity);
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      self->buckets[i] = NULL;
    }
  } else if (1 == nargs) {
    Arcadia_HashMap* other = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_HashMap_getType(thread));
    self->buckets = NULL;
    self->size = 0;
    self->capacity = other->capacity;
    self->buckets = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashMap_Node*) * self->capacity);
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      self->buckets[i] = NULL;
    }
    for (Arcadia_SizeValue i = 0, n = other->capacity; i < n; ++i) {
      for (_Arcadia_HashMap_Node* otherNode = other->buckets[i]; NULL != otherNode; otherNode = otherNode->next) {
        _Arcadia_HashMap_Node* selfNode = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashMap_Node));
        selfNode->hash = otherNode->hash;
        selfNode->key = otherNode->key;
        selfNode->value = otherNode->value;
        selfNode->next = self->buckets[i];
        self->buckets[i] = selfNode;
      }
    }
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Collection*)self)->clear = (void (*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashMap_clearImpl;
  ((Arcadia_Collection*)self)->getSize = (Arcadia_SizeValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashMap_getSizeImpl;
  ((Arcadia_Collection*)self)->isImmutable = (Arcadia_BooleanValue(*)(Arcadia_Thread*, Arcadia_Collection*)) & Arcadia_HashMap_isImmutableImpl;
  ((Arcadia_Map*)self)->get = (Arcadia_Value (*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value)) &Arcadia_HashMap_getImpl;
  ((Arcadia_Map*)self)->remove = (void (*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value, Arcadia_Value*, Arcadia_Value*))  &Arcadia_HashMap_removeImpl;
  ((Arcadia_Map*)self)->set = (void (*)(Arcadia_Thread*, Arcadia_Map*, Arcadia_Value, Arcadia_Value, Arcadia_Value*, Arcadia_Value*)) & Arcadia_HashMap_setImpl;
  ((Arcadia_Map*)self)->getKeys = (Arcadia_List *(*)(Arcadia_Thread*, Arcadia_Map*)) & Arcadia_HashMap_getKeysImpl;
  ((Arcadia_Map*)self)->getValues = (Arcadia_List *(*)(Arcadia_Thread*, Arcadia_Map*)) &Arcadia_HashMap_getValuesImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, nargs + 1);
}

static void
Arcadia_HashMap_clearImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      _Arcadia_HashMap_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Memory_deallocateUnmanaged(thread, node);
      node = NULL;
    }
  }
  self->size = 0;
}

static Arcadia_SizeValue
Arcadia_HashMap_getSizeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{ return self->size; }

static Arcadia_BooleanValue
Arcadia_HashMap_isImmutableImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{ return Arcadia_BooleanValue_False; }

static Arcadia_Value
Arcadia_HashMap_getImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key
  )
{
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &key);
  Arcadia_SizeValue index = hash % self->capacity;

  for (_Arcadia_HashMap_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (Arcadia_Value_isEqualTo(thread, &key, &node->key)) {
        return node->value;
      }
    }
  }
  return Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
}

static void
Arcadia_HashMap_removeImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &key);
  Arcadia_SizeValue index = hash % self->capacity;
  _Arcadia_HashMap_Node** previous = &self->buckets[index];
  _Arcadia_HashMap_Node* current = self->buckets[index];
  while (current) {
    if (hash == current->hash && Arcadia_Value_isEqualTo(thread, &key, &current->key)) {
      Arcadia_Value oldKeyTemporary = current->key;
      Arcadia_Value oldValueTemporary = current->value;
      *previous = current->next;
      self->size--;
      Arcadia_Memory_deallocateUnmanaged(thread, current);

      if (oldKey) *oldKey = oldKeyTemporary;
      if (oldValue) *oldValue = oldValueTemporary;

      return;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }

  if (oldKey) *oldKey = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
  if (oldValue) *oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);

  return;
}

static void
Arcadia_HashMap_setImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self,
    Arcadia_Value key,
    Arcadia_Value value,
    Arcadia_Value* oldKey,
    Arcadia_Value* oldValue
  )
{
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_Map_remove(thread, (Arcadia_Map*)self, key, oldKey, oldValue);

    return;
  } else {
    Arcadia_SizeValue hash = Arcadia_Value_getHash(thread, &key);
    Arcadia_SizeValue index = hash % self->capacity;
    for (_Arcadia_HashMap_Node* node = self->buckets[index]; NULL != node; node = node->next) {
      if (hash == node->hash) {
        if (Arcadia_Value_isEqualTo(thread, &key, &node->key)) {
          Arcadia_Value oldKeyTemporary = node->key;
          Arcadia_Value oldValueTemporary = node->value;
          node->key = key;
          node->value = value;
          if (oldKey) *oldKey = oldKeyTemporary;
          if (oldValue) *oldValue = oldValueTemporary;

          return;
        }
      }
    }

    _Arcadia_HashMap_Node* node = Arcadia_Memory_allocateUnmanaged(thread, sizeof(_Arcadia_HashMap_Node));
    node->value = value;
    node->key = key;
    node->hash = hash;
    node->next = self->buckets[index];
    self->buckets[index] = node;
    self->size++;
    if (oldKey) *oldKey = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);
    if (oldValue) *oldValue = Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void);

    return;
  }
}

Arcadia_HashMap*
Arcadia_HashMap_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (Arcadia_Value_isVoidValue(&value)) {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
  } else {
    Arcadia_ValueStack_pushValue(thread, &value);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
  }
  ARCADIA_CREATEOBJECT(Arcadia_HashMap);
}

static Arcadia_List*
Arcadia_HashMap_getValuesImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    _Arcadia_HashMap_Node* node = self->buckets[i];
    while (node) {
      Arcadia_List_insertBack(thread, list, node->value);
      node = node->next;
    }
  }
  return list;
}

static Arcadia_List*
Arcadia_HashMap_getKeysImpl
  (
    Arcadia_Thread* thread,
    Arcadia_HashMap* self
  )
{
  Arcadia_List* list = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    _Arcadia_HashMap_Node* node = self->buckets[i];
    while (node) {
      Arcadia_List_insertBack(thread, list, node->key);
      node = node->next;
    }
  }
  return list;
}
