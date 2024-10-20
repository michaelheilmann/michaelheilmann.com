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

// Last modified: 2024-09-22

#include "Cilc/Keywords.h"

typedef struct Keyword Keyword;

struct Keyword {
  Keyword* next;
  R_String* string;
  R_Natural32Value type;
};

struct Cil_Keywords {
  R_Object _parent;
  Keyword** buckets;
  R_SizeValue size;
  R_SizeValue capacity;
};

static void
Cil_Keywords_destruct
  (
    Cil_Keywords* self
  );

static void
Cil_Keywords_visit
  (
    Cil_Keywords* self
  );

static void
Cil_Keywords_destruct
  (
    Cil_Keywords* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    while (self->buckets[i]) {
      Keyword* node = self->buckets[i];
      self->buckets[i] = self->buckets[i]->next;
      R_deallocateUnmanaged_nojump(node);
    }
  }
  R_deallocateUnmanaged_nojump(self->buckets);
  self->buckets = NULL;
}

static void
Cil_Keywords_visit
  (
    Cil_Keywords* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    Keyword* node = self->buckets[i];
    while (node) {
      R_Object_visit(node->string);
      node = node->next;
    }
  }
}

Rex_defineObjectType("Cil.Keywords", Cil_Keywords, "R.Object", R_Object, &Cil_Keywords_visit, &Cil_Keywords_destruct);

void
Cil_Keywords_construct
  (
    Cil_Keywords* self
  )
{
  R_Type* _type = _Cil_Keywords_getType();
  R_Object_construct((R_Object*)self);
  self->size = 0;
  self->capacity = 8;
  if (!R_allocateUnmanaged_nojump((void**)&self->buckets, sizeof(Keyword*) * self->capacity)) {
    R_jump();
  }
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
    self->buckets[i] = NULL;
  }
  R_Object_setType((R_Object*)self, _type);
}

Cil_Keywords*
Cil_Keywords_create
  (
  )
{
  Cil_Keywords* self = R_allocateObject(_Cil_Keywords_getType());
  Cil_Keywords_construct(self);
  return self;
}

void
Cil_Keywords_add
  (
    Cil_Keywords* self,
    R_String* string,
    R_Natural32Value type
  )
{
  R_SizeValue hash = R_String_getHash(string);
  R_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    if (R_String_isEqualTo(keyword->string, string)) {
      R_setStatus(R_Status_Exists);
      R_jump();
    }
  }
  Keyword* keyword = NULL;
  if (!R_allocateUnmanaged_nojump(&keyword, sizeof(Keyword))) {
    R_jump();
  }
  keyword->string = string;
  keyword->type = type;
  keyword->next = self->buckets[index];
  self->buckets[index] = keyword;
  self->size++;
}

R_BooleanValue
Cil_Keywords_scan
  (
    Cil_Keywords* self,
    R_String* string,
    R_Natural32Value* tokenType
  )
{
  R_SizeValue hash = R_String_getHash(string);
  R_SizeValue index = hash % self->capacity;
  for (Keyword* keyword = self->buckets[index]; NULL != keyword; keyword = keyword->next) {
    if (R_String_isEqualTo(keyword->string, string)) {
      *tokenType = keyword->type;
      return R_BooleanValue_True;
    }
  }
  return R_BooleanValue_False;
}
