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

#if !defined(R_INTERPRETER_CONSTRUCTOR_INCLUDED)
#define R_INTERPRETER_CONSTRUCTOR_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Interpreter/Include.h"

Arcadia_declareObjectType(u8"R.Interpreter.Constructor", R_Interpreter_Constructor, u8"Arcadia.Object");

struct R_Interpreter_Constructor {
  Arcadia_Object _parent;
  /// Arcadia_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this method.
  /// Arcadia_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this method.
  Arcadia_BooleanValue isForeign;
  union {
    Arcadia_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
};

R_Interpreter_Constructor*
R_Interpreter_Constructor_createForeign
  (
    Arcadia_Thread* thread,
    Arcadia_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Constructor*
R_Interpreter_Constructor_create
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Constructor_getCode
  (
    Arcadia_Thread* thread,
    R_Interpreter_Constructor* self
  );

#endif // R_INTERPRETER_CONSTRUCTOR_INCLUDED
