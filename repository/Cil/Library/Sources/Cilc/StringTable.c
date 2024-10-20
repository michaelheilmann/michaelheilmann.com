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

// Last modified: 2024-10-14

#include "Cilc/StringTable.h"

// memcmp, memcpy, memmove
#include <string.h>
// fprintf, stderr
#include <stdio.h>

static void
Cil_StringTable_maybeResize_nojump
  (
    Cil_StringTable* self
  )
{
  if (self->size >= self->capacity) {
    R_SizeValue maximumCapacity = R_SizeValue_Maximum / sizeof(Cil_StringTable_Node*);
    R_SizeValue oldCapacity = self->capacity;
    R_SizeValue newCapacity;
    if (oldCapacity > maximumCapacity / 2) {
      if (oldCapacity == maximumCapacity) {
        return; // Cannot grow. Still a success.
      }
      newCapacity = maximumCapacity;
    } else {
      newCapacity = oldCapacity * 2;
    }
    Cil_StringTable_Node** oldBuckets = self->buckets;
    Cil_StringTable_Node** newBuckets = NULL;
    if (!R_allocateUnmanaged_nojump((void**)&newBuckets, sizeof(Cil_StringTable_Node*) * newCapacity)) {
      R_setStatus(R_Status_Success);
      return;
    }
    for (R_SizeValue i = 0, n = newCapacity; i < n; ++i) {
      newBuckets[i] = NULL;
    }
    for (R_SizeValue i = 0, n = oldCapacity; i < n; ++i) {
      while (oldBuckets[i]) {
        Cil_StringTable_Node* node = oldBuckets[i];
        oldBuckets[i] = oldBuckets[i]->next;
        R_SizeValue hash = R_String_getHash(node->string);
        R_SizeValue index = hash % newCapacity;
        node->next = newBuckets[i];
        newBuckets[i] = node;
      }
    }
    R_deallocateUnmanaged_nojump(oldBuckets);
    self->buckets = newBuckets;
    self->capacity = newCapacity;
  }
}

static R_SizeValue
Cil_StringTable_hashBytes
  (
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{ 
  R_SizeValue hash = numberOfBytes;
  for (R_SizeValue i = 0, n = numberOfBytes; i < n; ++i) {
    hash = hash * 37 + bytes[i];
  }
  return hash;
}

static void
Cil_StringTable_visit
  (
    Cil_StringTable* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Cil_StringTable_Node* node = self->buckets[i];
    while (node) {
      R_Object_visit(node->string);
      node = node->next;
    }
  }
}

static void
Cil_StringTable_finalize
  (
    Cil_StringTable* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while(self->buckets[i]) {
      Cil_StringTable_Node* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(node);
    }
  }
}

Rex_defineObjectType("Cil.StringTable", Cil_StringTable, "R.Object", R_Object, &Cil_StringTable_visit, &Cil_StringTable_finalize);

void
Cil_StringTable_construct
  (
    Cil_StringTable* self
  )
{
  R_Type* _type = _Cil_StringTable_getType();
  R_Object_construct((R_Object*)self);
  self->buckets = NULL;
  self->size = R_SizeValue_Literal(0);
  self->capacity = R_SizeValue_Literal(0);
  static R_SizeValue const g_defaultCapacity = 8;
  if (!R_allocateUnmanaged_nojump((void**)&self->buckets, sizeof(Cil_StringTable_Node*) * g_defaultCapacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = g_defaultCapacity; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  self->capacity = g_defaultCapacity;
  R_Object_setType((R_Object*)self, _type);
}

Cil_StringTable*
Cil_StringTable_create
  (
  )
{
  Cil_StringTable* self = R_allocateObject(_Cil_StringTable_getType());
  Cil_StringTable_construct(self);
  return self;
}

R_String*
Cil_StringTable_getOrCreateString
  (
    Cil_StringTable* self,
    R_StringBuffer* stringBuffer
  )
{
  R_SizeValue hash = Cil_StringTable_hashBytes(R_StringBuffer_getBytes(stringBuffer), R_StringBuffer_getNumberOfBytes(stringBuffer));
  R_SizeValue index = hash % self->capacity;
  for (Cil_StringTable_Node* node = self->buckets[index]; NULL != node; node = node->next) {
    if (R_String_getHash(node->string) == hash && R_String_getNumberOfBytes(node->string)) {
      if (!memcmp(R_String_getBytes(node->string), R_StringBuffer_getBytes(stringBuffer), R_String_getNumberOfBytes(node->string))) {
        return node->string;
      }
    }
  }
  R_Value temporary;
  R_Value_setObjectReferenceValue(&temporary, stringBuffer);
  R_String* string = R_String_create(temporary);
  Cil_StringTable_Node* node = NULL;
  if (!R_allocateUnmanaged_nojump(&node, sizeof(Cil_StringTable_Node))) {
    R_jump();
  }
  node->string = string;
  node->next = self->buckets[index];
  self->buckets[index] = node;
  self->size++;
  
  Cil_StringTable_maybeResize_nojump(self);

  return string;
}
