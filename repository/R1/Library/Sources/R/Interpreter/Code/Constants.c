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

// Last modified: 2024-12-07

#include "R/Interpreter/Code/Constants.h"

#include "R/ArmsIntegration.h"
#include "R/DynamicArrayUtilities.h"
#include "R/String.h"
#include "R/Interpreter/Include.h"
#include "R/cstdlib.h"

static void
constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
destructImpl
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self
  );

static void
visitImpl
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self
  );

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    R_Value const* constant
  );

static const R_ObjectType_Operations objectTypeOperations = {
  .construct = &constructImpl,
  .destruct = &destructImpl,
  .visit = &visitImpl,
};

static const Arcadia_Type_Operations typeOperations = {
  .objectTypeOperations = &objectTypeOperations,
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

Rex_defineObjectType(u8"R.Interpreter.Code.Constants", R_Interpreter_Code_Constants, u8"R.Object", R_Object, &typeOperations);

static void
constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_Interpreter_Code_Constants* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Code_Constants_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  if (!R_allocateUnmanaged_nojump(process, &_self->p, 0)) {
    Arcadia_Process_jump(process);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
destructImpl
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(process, self->p);
    self->p = NULL;
  }
}

static void
visitImpl
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    R_Value_visit(self->p + i);
  }
}

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Interpreter_Code_Constants* self = R_allocateObject(process, _R_Interpreter_Code_Constants_getType(process), 0, &argumentValues[0]);
  return self;
}

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    R_Value const* constant
  )
{ 
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    if (R_Value_isEqualTo(process, self->p + i, constant)) {
      return i;
    }
  }
  R_DynamicArrayUtilities_ensureFreeCapacity(&self->p, sizeof(R_Value), self->sz, &self->cp, 1, R_DynamicArrayUtilities_GrowthStrategy4);
  self->p[self->sz++] = *constant;
  return self->sz - 1;
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_BooleanValue booleanValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Boolean, .booleanValue = booleanValue };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_ForeignProcedureValue foreignProcedureValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedureValue };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer16Value integer16Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer16, .integer16Value = integer16Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer32Value integer32Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer32, .integer32Value = integer32Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer64Value integer64Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer32, .integer64Value = integer64Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer8Value integer8Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Integer8, .integer8Value = integer8Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural16Value natural16Value
  )
{ 
  R_Value const constant = { .tag = R_ValueTag_Natural16, .natural16Value = natural16Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural32Value natural32Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural32, .natural32Value = natural32Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural64Value natural64Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural64, .natural64Value = natural64Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural8Value natural8Value
  )
{
  R_Value const constant = { .tag = R_ValueTag_Natural8, .natural8Value = natural8Value };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_SizeValue sizeValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Size, .sizeValue = sizeValue };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    R_String* stringValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = stringValue };
  return getOrCreate(process, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants* self,
    Arcadia_VoidValue voidValue
  )
{
  R_Value const constant = { .tag = R_ValueTag_Void, .voidValue = voidValue };
  return getOrCreate(process, self, &constant);
}

R_Value const*
R_Interpreter_Code_Constants_getAt
  (
    Arcadia_Process* process,
    R_Interpreter_Code_Constants const* self,
    Arcadia_Natural32Value index
  )
{
  if (index >= self->sz) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  return self->p + index;
}
