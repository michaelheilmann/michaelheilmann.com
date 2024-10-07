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

#include "Tools/Cilc/Keywords.h"

typedef struct Keyword Keyword;

struct Keyword {
  Keyword* next;
  R_String* string;
  R_Natural32Value type;
};

struct Cil_Keywords {
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
{/*Intentionally empty.*/}

static void
Cil_Keywords_visit
  (
    Cil_Keywords* self
  )
{
  for (R_SizeValue i = 0, n = self->capacity; i < n; ++i) {
  }
}

void
_Cil_Keywords_registerType
  (
  )
{
  R_registerObjectType("Cil.Keywords", sizeof("Cil.Keywords") - 1, sizeof(Cil_Keywords), NULL, NULL, &Cil_Keywords_visit, &Cil_Keywords_destruct);
}

Cil_Keywords*
Cil_Keywords_create
  (
  )
{
  Cil_Keywords* self = R_allocateObject(R_getObjectType("Cil.Keywords", sizeof("Cil.Keywords") - 1));
  return self;
}

R_BooleanValue
Cil_Keywords_scan
  (
    Cil_Keywords* self,
    void const* p,
    R_SizeValue n,
    Cil_TokenType* tokenType
  )
{
  return R_BooleanValue_False;
}