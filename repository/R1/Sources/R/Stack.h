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

#if !defined(R_STACK_H_INCLUDED)
#define R_STACK_H_INCLUDED

#include "R/Value.h"

typedef struct R_Stack R_Stack;

void _R_Stack_registerType();

struct R_Stack {
  R_Value* elements;
  R_SizeValue size;
  R_SizeValue capacity;
};

void
R_Stack_clear
  (
    R_Stack* self
  );

R_Stack*
R_Stack_create
  (
  );

R_SizeValue
R_Stack_getSize
  (
    R_Stack* self
  );

void
R_Stack_push
  (
    R_Stack* self,
    R_Value value
  );

void
R_Stack_pop
  (
    R_Stack* self
  );

R_Value
R_Stack_peek
  (
    R_Stack* self
  );

#define Define(Suffix, Prefix) \
  void \
  R_Stack_push##Suffix##Value \
    ( \
      R_Stack* self, \
      R_##Suffix##Value Prefix##Value \
    ); \
\
  R_BooleanValue \
  R_Stack_is##Suffix##Value \
    ( \
      R_Stack* self, \
      R_SizeValue index \
    ); \
\
  R_##Suffix##Value \
  R_Stack_get##Suffix##Value \
    ( \
      R_Stack* self, \
      R_SizeValue index \
    );

Define(Boolean, boolean)
Define(ForeignFunctionReference, foreignFunctionReference)
Define(Integer8, integer8)
Define(Integer16, integer16)
Define(Integer32, integer32)
Define(Integer64, integer64)
Define(Natural8, natural8)
Define(Natural16, natural16)
Define(Natural32, natural32)
Define(Natural64, natural64)
Define(Size, size)
Define(Void, void)

#undef Define

#endif // R_STACK_H_INCLUDED