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

// Last modified: 2025-01-20

#if !defined(ARCADIA_RING1_IMPLEMENTATION_TESTS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_TESTS_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Diagnostics.h"

#define Arcadia_Tests_assertTrue(expression) \
  if (!(expression)) { \
    Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: test assertion `%s` failed\n", __FILE__, __LINE__, #expression); \
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed); \
    Arcadia_Process_jump(process); \
  }

static inline Arcadia_BooleanValue
Arcadia_Tests_safeExecute
  (
    void (*f)(Arcadia_Process*)
  )
{
  Arcadia_Status status = Arcadia_Status_Success;
  Arcadia_BooleanValue result = Arcadia_BooleanValue_True;
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    result = Arcadia_BooleanValue_False;
    return result;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    (*f)(process);
  } else {
    result = Arcadia_BooleanValue_False;
  }
  Arcadia_Process_popJumpTarget(process);
  status = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    result = Arcadia_BooleanValue_False;
  }
  return result;
}

#endif // ARCADIA_RING1_IMPLEMENTATION_TESTS_H_INCLUDED
