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

// Last modified: 2024-12-12

#include "R/Interpreter/Procedure.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static void
R_Interpreter_Procedure_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Interpreter_Procedure_visit
  (
    R_Interpreter_Procedure* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Interpreter_Procedure_constructImpl,
  .destruct = NULL,
  .visit = &R_Interpreter_Procedure_visit,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("R.Interpreter.Procedure", R_Interpreter_Procedure, "R.Object", R_Object, &_typeOperations);

static void
R_Interpreter_Procedure_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_Procedure* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Interpreter_Procedure_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->parameterNames = R_List_create();
  _self->unqualifiedName = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_String_getType());
  if (R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_ForeignProcedureValue_getType())) {
    _self->isForeign = R_BooleanValue_True;
    _self->foreignProcedure = R_Value_getForeignProcedureValue(&argumentValues[1]);
  } else if (R_Type_isSubType(R_Value_getType(&argumentValues[1]), _R_Interpreter_Code_getType())) {
    _self->isForeign = R_BooleanValue_False;
    _self->code = R_Value_getObjectReferenceValue(&argumentValues[1]);
  } else {
    R_setStatus(R_Status_ArgumentTypeInvalid);
    R_jump();
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_Procedure_visit
  (
    R_Interpreter_Procedure* self
  )
{
  if (!self->isForeign) {
    R_Object_visit(self->code);
  }
  R_Object_visit(self->unqualifiedName);
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_createForeign
  (
    R_String* name,
    R_ForeignProcedureValue foreignProcedure
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = name },
    {.tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedure },
  };
  R_Interpreter_Procedure* self = R_allocateObject(_R_Interpreter_Procedure_getType(), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Procedure*
R_Interpreter_Procedure_create
  (
    R_String* name,
    R_Interpreter_Code* code
  )
{
  R_Value argumentValues[] = { 
    { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name },
    { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = code },
  };
  R_Interpreter_Procedure* self = R_allocateObject(_R_Interpreter_Procedure_getType(), 2, &argumentValues[0]);
  return self;
}

R_Interpreter_Code*
R_Interpreter_Procedure_getCode
  (
    R_Interpreter_Procedure* self
  )
{ return self->code; }
