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

#include "Arcadia/Mil/Frontend/Asts/ProcedureDefinitionAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

/// @code
/// construct(nativeName:Arcadia.String, procedureName:Arcadia.String,procedureParameters:R.List,procedureBody:List)
/// @endcode
static void
Arcadia_Mil_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_ProcedureDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ProcedureDefinitionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_ProcedureDefinitionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_ProcedureDefinitionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_ProcedureDefinitionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_ProcedureDefinitionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_ProcedureDefinitionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.ProcedureDefinitionAst", Arcadia_Mil_ProcedureDefinitionAst, u8"Arcadia.Mil.Ast", Arcadia_Mil_Ast, &_Arcadia_Mil_ProcedureDefinitionAst_typeOperations);

static void
Arcadia_Mil_ProcedureDefinitionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_ProcedureDefinitionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_ProcedureDefinitionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void) };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }

  if (5 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->entry = Arcadia_Value_getBooleanValue(&argumentValues[0]);
  _self->nativeName = Arcadia_ArgumentsValidation_getObjectReferenceValueOrNull(thread, &argumentValues[1], _Arcadia_String_getType(thread));
  _self->procedureName = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[2], _Arcadia_String_getType(thread));
  _self->procedureParameters = Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[3], _Arcadia_List_getType(thread));
  _self->procedureBody = Arcadia_ArgumentsValidation_getObjectReferenceValueOrNull(thread, &argumentValues[4], _Arcadia_List_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_ProcedureDefinitionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_ProcedureDefinitionAst* self
  )
{
  if (self->nativeName) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->nativeName);
  }
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureName);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureParameters);
  if (self->procedureBody) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->procedureBody);
  }
}

Arcadia_Mil_ProcedureDefinitionAst*
Arcadia_Mil_ProcedureDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue entry,
    Arcadia_String* nativeName,
    Arcadia_String* procedureName,
    Arcadia_List* procedureParameters,
    Arcadia_List* procedureBody
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeBooleanValue(entry),
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    Arcadia_Value_makeObjectReferenceValue(procedureName),
    Arcadia_Value_makeObjectReferenceValue(procedureParameters),
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  if (nativeName) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[1], nativeName);
  }
  if (procedureBody) {
    Arcadia_Value_setObjectReferenceValue(&argumentValues[4], procedureBody);
  }
  Arcadia_Mil_ProcedureDefinitionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_ProcedureDefinitionAst_getType(thread), 5, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
