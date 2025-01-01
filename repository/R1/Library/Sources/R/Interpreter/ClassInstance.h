#if !defined(R_RUNTIME_CLASSINSTANCE_H_INCLUDED)
#define R_RUNTIME_CLASSINSTANCE_H_INCLUDED

#include "R/Object.h"
typedef struct R_Interpreter_Class R_Interpreter_Class;

Rex_declareObjectType("R.Interpreter.ClassInstance", R_Interpreter_ClassInstance, "R.Object");

struct R_Interpreter_ClassInstance {
  R_Object _parent;
  /// The class of this interpreter object.
  R_Interpreter_Class* class;
  /// The array of variables.
  R_Value *variables;
};

R_Interpreter_ClassInstance*
R_Interpreter_ClassInstance_create
  (
    R_Interpreter_Class* class
  );

#endif // R_RUNTIME_CLASSINSTANCE_H_INCLUDED
