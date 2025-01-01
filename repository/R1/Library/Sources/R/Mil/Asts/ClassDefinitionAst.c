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

#include "R/Mil/Asts/ClassDefinitionAst.h"

#include "R/ArgumentsValidation.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// construct(className:R.String, extendedClassName:R.String, classBody:R.List)
/// @endcode
static void
R_Mil_ClassDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_Mil_ClassDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ClassDefinitionAst* self
  );

static const R_ObjectType_Operations _R_Mil_ClassDefinitionAst_objectTypeOperations = {
  .construct = &R_Mil_ClassDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &R_Mil_ClassDefinitionAst_visit,
};

static const Arcadia_Type_Operations _R_Mil_ClassDefinitionAst_typeOperations = {
  .objectTypeOperations = &_R_Mil_ClassDefinitionAst_objectTypeOperations,
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

Rex_defineObjectType(u8"R.Mil.ClassDefinitionAst", R_Mil_ClassDefinitionAst, u8"R.Mil.DefinitionAst", R_Mil_DefinitionAst, &_R_Mil_ClassDefinitionAst_typeOperations);

static void
R_Mil_ClassDefinitionAst_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{ 
  R_Mil_ClassDefinitionAst* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Mil_ClassDefinitionAst_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (3 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->className = R_Argument_getObjectReferenceValue(process, &argumentValues[0], _R_String_getType(process));
  _self->extendedClassName = R_Argument_getObjectReferenceValueOrNull(process, &argumentValues[1], _R_String_getType(process));
  _self->classBody = R_Argument_getObjectReferenceValue(process, &argumentValues[2], _R_List_getType(process));
  R_Object_setType(_self, _type);
}

static void
R_Mil_ClassDefinitionAst_visit
  (
    Arcadia_Process* process,
    R_Mil_ClassDefinitionAst* self
  )
{
  R_Object_visit(self->className);
  if (self->extendedClassName) {
    R_Object_visit(self->extendedClassName);
  }
  if (self->classBody) {
    R_Object_visit(self->classBody);
  }
}

R_Mil_ClassDefinitionAst*
R_Mil_ClassDefinitionAst_create
  (
    Arcadia_Process* process,
    R_String* className,
    R_String* extendedClassName,
    R_List* classBody
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = className },
    {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void },
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = classBody },
  };
  if (extendedClassName) {
    R_Value_setObjectReferenceValue(&argumentValues[1], extendedClassName);
  }
  R_Mil_ClassDefinitionAst* self = R_allocateObject(process, _R_Mil_ClassDefinitionAst_getType(process), 3, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
