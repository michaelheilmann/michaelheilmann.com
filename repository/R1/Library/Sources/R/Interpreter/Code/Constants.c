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

#include "R/Interpreter/Include.h"

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  );

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Value const* constant
  );

static const Arcadia_ObjectType_Operations objectTypeOperations = {
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

Rex_defineObjectType(u8"R.Interpreter.Code.Constants", R_Interpreter_Code_Constants, u8"Arcadia.Object", Arcadia_Object, &typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  R_Interpreter_Code_Constants* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_Interpreter_Code_Constants_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->p = NULL;
  _self->sz = 0;
  _self->cp = 0;
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &_self->p, 0);
  Arcadia_Object_setType(thread, _self, _type);
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  )
{
  if (self->p) {
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->p);
    self->p = NULL;
  }
}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self
  )
{
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    Arcadia_Value_visit(thread, self->p + i);
  }
}

R_Interpreter_Code_Constants*
R_Interpreter_Code_Constants_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_Interpreter_Code_Constants* self = Arcadia_allocateObject(thread, _R_Interpreter_Code_Constants_getType(thread), 0, &argumentValues[0]);
  return self;
}

static Arcadia_Natural32Value
getOrCreate
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Value const* constant
  )
{ 
  for (Arcadia_SizeValue i = 0, n = self->cp; i < n; ++i) {
    if (Arcadia_Value_isEqualTo(thread, self->p + i, constant)) {
      return i;
    }
  }
  Arcadia_Arrays_resizeByFreeCapacity(thread, Arms_getDefaultMemoryManager(), &self->p, sizeof(Arcadia_Value), self->sz, &self->cp, 1, Arcadia_Arrays_ResizeStrategy_Type4);
  self->p[self->sz++] = *constant;
  return self->sz - 1;
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateBoolean
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_BooleanValue booleanValue
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Boolean, .booleanValue = booleanValue };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateForeignProcedure
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_ForeignProcedureValue foreignProcedureValue
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_ForeignProcedure, .foreignProcedureValue = foreignProcedureValue };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer16Value integer16Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Integer16, .integer16Value = integer16Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer32Value integer32Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Integer32, .integer32Value = integer32Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer64Value integer64Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Integer32, .integer64Value = integer64Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateInteger8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Integer8Value integer8Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Integer8, .integer8Value = integer8Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural16
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural16Value natural16Value
  )
{ 
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Natural16, .natural16Value = natural16Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural32
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural32Value natural32Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Natural32, .natural32Value = natural32Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural64
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural64Value natural64Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Natural64, .natural64Value = natural64Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateNatural8
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_Natural8Value natural8Value
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Natural8, .natural8Value = natural8Value };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateSize
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_SizeValue sizeValue
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Size, .sizeValue = sizeValue };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateString
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_String* stringValue
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = stringValue };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Natural32Value
R_Interpreter_Code_Constants_getOrCreateVoid
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants* self,
    Arcadia_VoidValue voidValue
  )
{
  Arcadia_Value const constant = { .tag = Arcadia_ValueTag_Void, .voidValue = voidValue };
  return getOrCreate(thread, self, &constant);
}

Arcadia_Value const*
R_Interpreter_Code_Constants_getAt
  (
    Arcadia_Thread* thread,
    R_Interpreter_Code_Constants const* self,
    Arcadia_Natural32Value index
  )
{
  if (index >= self->sz) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return self->p + index;
}
