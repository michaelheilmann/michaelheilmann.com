#if !defined(R_RUNTIME_CLASSINSTANCE_H_INCLUDED)
#define R_RUNTIME_CLASSINSTANCE_H_INCLUDED

#include "R/Object.h"
typedef struct R_Interpreter_Class R_Interpreter_Class;

Rex_declareObjectType("R.Interpreter.ClassInstance", R_Interpreter_ClassInstance, "R.Object");

struct R_Interpreter_ClassInstance {
  R_Object _parent;
  R_Interpreter_ClassInstance* parent;
  /// The class of this interpreter object.
  R_Interpreter_Class* cls;
};

R_Interpreter_ClassInstance*
R_Interpreter_ClassInstance_create
  (
    R_Interpreter_Class** cls
  );

void
R_Interpreter_ClassInstance_set
  (
    R_Interpreter_ClassInstance* self,
    R_String name,
    R_Value value
  );

R_Value
R_Interpreter_ClassInstance_get
  (
    R_Interpreter_ClassInstance* self,
    R_String name
  );

#endif // R_RUNTIME_CLASSINSTANCE_H_INCLUDED
