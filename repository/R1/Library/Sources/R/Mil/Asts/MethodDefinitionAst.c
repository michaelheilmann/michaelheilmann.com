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

// Last modified: 2025-01-01

#include "R/Mil/Asts/MethodDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(methodName:R.String, methodParameters:R.List, methodBody:R.List)
/// @endcode
static void
R_Mil_MethodDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_MethodDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_MethodDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_MethodDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_MethodDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_MethodDefinitionAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_MethodDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_MethodDefinitionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.MethodDefinitionAst", R_Mil_MethodDefinitionAst, u8"R.Mil.ClassMemberDefinitionAst", R_Mil_ClassMemberDefinitionAst, &_R_Mil_MethodDefinitionAst_typeOperations);

static void
R_Mil_MethodDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Mil_MethodDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_MethodDefinitionAst_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (4 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->nativeName = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[0], _R_String_getType(process));
  _self->methodName = (R_String*)R_Argument_getObjectReferenceValue(process, &argumentValues[1], _R_String_getType(process));
  _self->methodParameters = (R_List*)R_Argument_getObjectReferenceValue(process, &argumentValues[2], _R_List_getType(process));
  _self->methodBody = (R_List*)R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[3], _R_List_getType(process));
  R_Object_setType(_self, _type);
}

static void
R_Mil_MethodDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_MethodDefinitionAst* self
  )
{
  R_Object_visit(self->nativeName);
  R_Object_visit(self->methodName);
  R_Object_visit(self->methodParameters);
  R_Object_visit(self->methodBody);
}

R_Mil_MethodDefinitionAst*
R_Mil_MethodDefinitionAst_create
  (
    Arcadia_Process* process,
    R_String* nativeName,
    R_String* methodName,
    R_List* methodParameters,
    R_List* methodBody
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = methodName },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = methodParameters },
                               {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void }, };
  if (nativeName) {
    R_Value_setObjectReferenceValue(&argumentValues[0], nativeName);
  }
  if (methodBody) {
    R_Value_setObjectReferenceValue(&argumentValues[3], methodBody);
  }
  R_Mil_MethodDefinitionAst* self = R_allocateObject(process, _R_Mil_MethodDefinitionAst_getType(process), 4, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
