#include "R/Interpreter/ClassInstance.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"
#include "Arms.h"

static void
R_Interpreter_ClassInstance_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Interpreter_ClassInstance_destruct
  (
    R_Interpreter_ClassInstance* self
  );

static void
R_Interpreter_ClassInstance_visit
  (
    R_Interpreter_ClassInstance* self
  );

static const R_ObjectType_Operations objectTypeOperations = {
  .construct = &R_Interpreter_ClassInstance_constructImpl,
  .destruct = &R_Interpreter_ClassInstance_destruct,
  .visit = &R_Interpreter_ClassInstance_visit,
};

static const R_Type_Operations typeOperations = {
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

Rex_defineObjectType("R.Interpreter.ClassInstance", R_Interpreter_ClassInstance, "R.Object", R_Object, &typeOperations);

static void
R_Interpreter_ClassInstance_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Interpreter_ClassInstance* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Interpreter_ClassInstance_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  R_Interpreter_Class* class = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_Interpreter_Class_getType());
  R_Interpreter_Class_complete(class, R_Interpreter_ProcessState_get());
  _self->variables = NULL;
  if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &_self->variables, sizeof(R_Value) * class->numberOfVariables)) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->class = class;
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Interpreter_ClassInstance_destruct
  (
    R_Interpreter_ClassInstance* self
  )
{
  Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), self->variables);
  self->variables = NULL;
}

static void
R_Interpreter_ClassInstance_visit
  (
    R_Interpreter_ClassInstance* self
  )
{
  R_Object_visit(self->class);
}

R_Interpreter_ClassInstance*
R_Interpreter_ClassInstance_create
  (
    R_Interpreter_Class* class
  )
{
  R_Value argumentValues[] = {
    {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = class },
  };
  R_Interpreter_ClassInstance* self = R_allocateObject(_R_Interpreter_ClassInstance_getType(), 1, &argumentValues[0]);
  return self;
}
