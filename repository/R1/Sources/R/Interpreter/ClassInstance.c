#include "R/Interpreter/ClassInstance.h"

static const R_ObjectType_Operations objectTypeOperations = {
  .construct = NULL,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations typeOperations = {
  .objectTypeOperations = &objectTypeOperations,
  .add = NULL,
  . and = NULL,
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
  . or = NULL,
  .subtract = NULL,
};


Rex_defineObjectType("R.Interpreter.ClassInstance", R_Interpreter_ClassInstance, "R.Object", R_Object, &typeOperations);
