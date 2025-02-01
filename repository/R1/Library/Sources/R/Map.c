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

#include "R/Map.h"

#include "R/DynamicArrayUtilities.h"
#include "R/cstdlib.h"

static Arcadia_BooleanValue g_initialized = Arcadia_BooleanValue_False;

static Arcadia_SizeValue g_minimumCapacity = -1;
static Arcadia_SizeValue g_maximumCapacity = -1;

typedef struct Node Node;

struct Node {
  Node* next;
  Arcadia_SizeValue hash;
  Arcadia_Value key;
  Arcadia_Value value;
};

struct R_Map {
  Arcadia_Object _parent;
  Node** buckets;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

static void
R_Map_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Map* self,
    Arcadia_SizeValue requiredFreeCapacity
  );

static void
R_Map_ensureInitialized
  (
    Arcadia_Process* process
  );

static void
R_Map_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
R_Map_destruct
  (
    Arcadia_Process* process,
    R_Map* self
  );

static void
R_Map_visit
  (
    Arcadia_Process* process,
    R_Map* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Map_constructImpl,
  .destruct = &R_Map_destruct,
  .visit = &R_Map_visit,
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

Rex_defineObjectType(u8"Arcadia.Library.Map", R_Map, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
R_Map_ensureFreeCapacity
  (
    Arcadia_Process* process,
    R_Map* self,
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
  Node** oldBuckets = self->buckets;
  Node** newBuckets = NULL;
  Arcadia_Process_allocateUnmanaged(process, (void**)&newBuckets, sizeof(Node*) * newCapacity);
  for (Arcadia_SizeValue i = 0, n = newCapacity; i < n; ++i) {
    newBuckets[i] = NULL;
  }
  for (Arcadia_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
    while (oldBuckets[i]) {
      Node* node = oldBuckets[i];
      oldBuckets[i] = oldBuckets[i]->next;
      Arcadia_SizeValue j = node->hash % newCapacity;
      node->next = newBuckets[j];
      newBuckets[j] = node;
    }
  }
  Arcadia_Process_deallocateUnmanaged(process, oldBuckets);
  self->buckets = newBuckets;
  self->capacity = newCapacity;
}

static void
R_Map_ensureInitialized
  (
    Arcadia_Process* process
  )
{
  if (!g_initialized) {
    g_minimumCapacity = 8;
    g_maximumCapacity = SIZE_MAX / sizeof(Node*);
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
R_Map_destruct
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Process_deallocateUnmanaged(process, node);
      node = NULL;
    }
  }
  if (self->buckets) {
    Arcadia_Process_deallocateUnmanaged(process, self->buckets);
    self->buckets = NULL;
  }
}

static void
R_Map_visit
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  if (self->buckets) {
    for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
      Node* node = self->buckets[i];
      while (node) {
        Arcadia_Value_visit(process, &node->key);
        Arcadia_Value_visit(process, &node->value);
        node = node->next;
      }
    }
  }
}

static void
R_Map_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Map* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Map_getType(process);
  R_Map_ensureInitialized(process);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->buckets = NULL;
  _self->capacity = 0;
  _self->size = 0;
  _self->capacity = g_minimumCapacity;
  Arcadia_Process_allocateUnmanaged(process, (void**)&_self->buckets, sizeof(Node*) * _self->capacity);
  for (Arcadia_SizeValue i = 0, n = _self->capacity; i < n; ++i) {
    _self->buckets[i] = NULL;
  }
  Arcadia_Object_setType(process, _self, _type);
}

R_Map*
R_Map_create
  (
    Arcadia_Process* process
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Map* self = R_allocateObject(process, _R_Map_getType(process), 0, &argumentValues[0]);
  return self;
}

R_Map*
R_Map_clone
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  R_Map* clone = R_Map_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    for (Node* node = self->buckets[i]; NULL != node; node = node->next) {
      R_Map_set(process, clone, node->key, node->value);
    }
  }
  return clone;
}

void
R_Map_clear
  (
    Arcadia_Process* process,
    R_Map* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      Arcadia_Process_deallocateUnmanaged(process, node);
      node = NULL;
    }
  }
  self->size = 0;
}


Arcadia_SizeValue
R_Map_getSize
  (
    R_Map const* self
  )
{ return self->size; }

void
R_Map_set
  (
    Arcadia_Process* process,
    R_Map* self,
    Arcadia_Value key,
    Arcadia_Value value
  )
{ 
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(process, &key);
  Arcadia_SizeValue index = hash % self->capacity;
  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (Arcadia_Value_isEqualTo(process, &key, &node->key)) {
        node->key = key;
        node->value = value;
        return;
      }
    }
  }
  Node* node = NULL;
  Arcadia_Process_allocateUnmanaged(process, &node, sizeof(Node));
  node->value = value;
  node->key = key;
  node->hash = hash;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
}

Arcadia_Value
R_Map_get
  (
    Arcadia_Process* process,
    R_Map const* self,
    Arcadia_Value key
  )
{ 
  if (Arcadia_Value_isVoidValue(&key)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_SizeValue hash = Arcadia_Value_getHash(process, &key);
  Arcadia_SizeValue index = hash % self->capacity;

  for (Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (hash == node->hash) {
      if (Arcadia_Value_isEqualTo(process, &key, &node->key)) {
        return node->value;
      }
    }
  }
  Arcadia_Value temporary;
  Arcadia_Value_setVoidValue(&temporary, Arcadia_VoidValue_Void);
  return temporary;
}

R_List*
R_Map_getValues
  (
    Arcadia_Process* process,
    R_Map const* self
  )
{
  R_List* list = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(process, list, node->value);
      node = node->next;
    }
  }
  return list;
}

R_List*
R_Map_getKeys
  (
    Arcadia_Process* process,
    R_Map const* self
  )
{
  R_List* list = R_List_create(process);
  for (Arcadia_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Node* node = self->buckets[i];
    while (node) {
      R_List_append(process, list, node->key);
      node = node->next;
    }
  }
  return list;
}
