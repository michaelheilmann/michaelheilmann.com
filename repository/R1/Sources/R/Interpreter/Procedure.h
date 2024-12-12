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

#if !defined(R_INTERPRETER_PROCEDURE_H_INCLUDED)
#define R_INTERPRETER_PROCEDURE_H_INCLUDED

#include "R/ForeignProcedure.h"
#include "R/Interpreter/Code.h"
#include "R/Object.h"
#include "R/Value.h"

Rex_declareObjectType("R.Interpreter.Procedure", R_Interpreter_Procedure, "R.Object");

struct R_Interpreter_Procedure {
  R_Object _parent;
  /// The name of this procedure.
  R_String* procedureName;
  /// R_BooleanValue_True indicates that code is invalid and foreignProcedure points to a foreign procedure of this procedure.
  /// R_BooleanValue_False indicates that foreignProcedure is invalid and code points to the code of this procedure.
  R_BooleanValue isForeign;
  union {
    R_ForeignProcedureValue foreignProcedure;
    R_Interpreter_Code* code;
  };
};

R_Interpreter_Procedure*
R_Interpreter_Procedure_createForeign
  ( 
    R_String* procedureName,
    R_ForeignProcedureValue foreignProcedure
  );

R_Interpreter_Procedure*
R_Interpreter_Procedure_create
  (
    R_String* name,
    R_Interpreter_Code* code
  );

R_Interpreter_Code*
R_Interpreter_Procedure_getCode
  (
    R_Interpreter_Procedure* self
  );

#endif // R_INTERPRETER_PROCEDURE_H_INCLUDED
