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

#include "Arcadia/Mil/Frontend/Asts/InvokeExpressionAst.h"

#include "Arcadia/Mil/Frontend/Include.h"

/// @code
/// construct(callee:Arcadia.Mil.VariableOperandAst,operands:Arcadia.List)
/// @endcode
static void
Arcadia_Mil_InvokeExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Arcadia_Mil_InvokeExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_InvokeExpressionAst* self
  );

static const Arcadia_ObjectType_Operations _Arcadia_Mil_InvokeExpressionAst_objectTypeOperations = {
  .construct = &Arcadia_Mil_InvokeExpressionAst_constructImpl,
  .destruct = NULL,
  .visit = &Arcadia_Mil_InvokeExpressionAst_visit,
};

static const Arcadia_Type_Operations _Arcadia_Mil_InvokeExpressionAst_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Mil_InvokeExpressionAst_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Mil.InvokeExpressionAst", Arcadia_Mil_InvokeExpressionAst, u8"Arcadia.Mil.ExpressionAst", Arcadia_Mil_ExpressionAst, &_Arcadia_Mil_InvokeExpressionAst_typeOperations);

void
Arcadia_Mil_InvokeExpressionAst_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Mil_InvokeExpressionAst* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Mil_InvokeExpressionAst_getType(thread);
  {
    Arcadia_Value argumentValues[] = { Arcadia_Value_Initializer() };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->callee = (Arcadia_Mil_VariableOperandAst*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Arcadia_Mil_VariableOperandAst_getType(thread));
  _self->operands = (Arcadia_List*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_List_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
Arcadia_Mil_InvokeExpressionAst_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_InvokeExpressionAst* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->callee);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->operands);
}

Arcadia_Mil_InvokeExpressionAst*
Arcadia_Mil_InvokeExpressionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_VariableOperandAst* callee,
    Arcadia_List* operands
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)callee),
    Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)operands),
  };
  Arcadia_Mil_InvokeExpressionAst* self = Arcadia_allocateObject(thread, _Arcadia_Mil_InvokeExpressionAst_getType(thread), 2, &argumentValues[0]);
  return self;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
