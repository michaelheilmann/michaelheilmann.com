// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

#include "R/Interpreter/ProcessState.private.h"

#include "R.h"
#include "R/Interpreter/Include.h"
#include "R/ArgumentsValidation.h"
#include "R/cstdlib.h"

static R_Interpreter_ProcessState* g_singleton = NULL;

R_Interpreter_ProcessState*
R_Interpreter_ProcessState_get
  (
  )
{ return g_singleton; }

void
R_Interpreter_ProcessState_startup
  (
  )
{
  if (g_singleton) {
    R_setStatus(R_Status_Initialized);
    R_jump();
  }
  R_Interpreter_ProcessState* singleton = NULL;
  if (!R_allocateUnmanaged_nojump(&singleton, sizeof(R_Interpreter_ProcessState))) {
    R_jump();
  }
  R_JumpTarget jumpTarget;

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    singleton->constants = R_Interpreter_Code_Constants_create();
    singleton->globals = R_Map_create();
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(singleton);
    singleton = NULL;
    R_jump();
  }

  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    singleton->mainThread = R_Interpreter_ThreadState_create();
    singleton->currentThread = singleton->mainThread;
    R_popJumpTarget();
  } else {
    R_popJumpTarget();
    R_deallocateUnmanaged_nojump(singleton);
    singleton = NULL;
    R_jump();
  }

  g_singleton = singleton;
}

void
R_Interpreter_ProcessState_shutdown
  (
  )
{
  if (!g_singleton) {
    R_setStatus(R_Status_NotInitialized);
    R_jump();
  }
  R_Interpreter_ProcessState* singleton = g_singleton;
  g_singleton = NULL;
  singleton->currentThread = NULL;

  R_Interpreter_ThreadState_destroy(singleton->mainThread);
  singleton->mainThread = NULL;

  singleton->globals = NULL;
  singleton->constants = NULL;
  
  R_deallocateUnmanaged_nojump(singleton);
  singleton = NULL;
}

void
R_Interpreter_ProcessState_visit
  (
    R_Interpreter_ProcessState* processState
  )
{
  R_Object_visit(processState->globals);
  R_Object_visit(processState->constants);

  R_Interpreter_ThreadState_visit(processState->currentThread);
  R_Interpreter_ThreadState_visit(processState->mainThread);
}

void
R_Interpreter_ProcessState_defineGlobalProcedure
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Procedure* procedure
  )
{ 
  if (!procedure) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedure->unqualifiedName };
  R_Value value = R_Map_get(self->globals, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  value = (R_Value){ .tag = R_ValueTag_ObjectReference, .objectReferenceValue = procedure };
  R_Map_set(self->globals, key, value);
}

void
R_Interpreter_ProcessState_defineGlobalClass
  (
    R_Interpreter_ProcessState* self,
    R_Interpreter_Class* class
  )
{
  if (!class) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = class->className };
  R_Value value = R_Map_get(self->globals, key);
  if (!R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_Exists);
    R_jump();
  }
  value = (R_Value){ .tag = R_ValueTag_ObjectReference, .objectReferenceValue = class };
  R_Map_set(self->globals, key, value);
}

R_Value
R_Interpreter_ProcessState_getGlobal
  (
    R_Interpreter_ProcessState* self,
    R_String* name
  )
{ 
  if (!name) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  R_Value key = { .tag = R_ValueTag_ObjectReference, .objectReferenceValue = name };
  R_Value value = R_Map_get(self->globals, key);
  if (R_Value_isVoidValue(&value)) {
    R_setStatus(R_Status_NotExists);
    R_jump();
  }
  return value;
}

R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getMainThread
  (
    R_Interpreter_ProcessState* self
  )
{ return self->mainThread; }

R_Interpreter_ThreadState*
R_Interpreter_ProcessState_getCurrentThread
  (
    R_Interpreter_ProcessState* self
  )
{ return self->currentThread; }

R_Interpreter_Code_Constants*
R_Interpreter_ProcessState_getConstants
  (
    R_Interpreter_ProcessState* self
  )
{ return self->constants; }
