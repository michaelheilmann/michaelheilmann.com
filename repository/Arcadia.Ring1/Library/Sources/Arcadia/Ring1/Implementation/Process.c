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

// Last modified: 2025-01-01

#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Ring1/Implementation/Process1.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include <stdio.h>
#include <malloc.h>
#include "Arms.h"

typedef uint32_t ReferenceCount;

#define ReferenceCount_Minimum (UINT32_C(0))
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

struct Arcadia_Process {
  ReferenceCount referenceCount;
  Arcadia_Process1* process1;
};

static Arcadia_Process* g_process = NULL;

Arcadia_ProcessStatus
Arcadia_Process_acquire
  (
    Arcadia_Process* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || ReferenceCount_Maximum == process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  process->referenceCount++;
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process_relinquish
  (
    Arcadia_Process* process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (ReferenceCount_Minimum == process->referenceCount || !g_process) {
    /* This is, actually, undefined behavior. */
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  if (ReferenceCount_Minimum == --process->referenceCount) {
    Arcadia_Process1_relinquish(g_process->process1);
    g_process->process1 = NULL;
    free(g_process);
    g_process = NULL;
  }
  return Arcadia_ProcessStatus_Success;
}

Arcadia_ProcessStatus
Arcadia_Process_get
  (
    Arcadia_Process** process
  )
{
  if (!process) {
    return Arcadia_ProcessStatus_ArgumentValueInvalid;
  }
  if (!g_process) {
    g_process = malloc(sizeof(Arcadia_Process));
    if (!g_process) {
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    if (Arcadia_Process1_get(&g_process->process1)) {
      free(g_process);
      g_process = NULL;
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    *process = g_process;
    return Arcadia_ProcessStatus_Success;
  }
  if (ReferenceCount_Maximum == g_process->referenceCount) {
    return Arcadia_ProcessStatus_OperationInvalid;
  }
  g_process->referenceCount++;
  *process = g_process;
  return Arcadia_ProcessStatus_Success;
}

void
Arcadia_Process_pushJumpTarget
  (
    Arcadia_Process* process,
    R_JumpTarget* jumpTarget
  )
{
  Arcadia_Process1_pushJumpTarget(process->process1, jumpTarget);
}

void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  )
{
  Arcadia_Process1_popJumpTarget(process->process1);
}

Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  )
{
  Arcadia_Process1_jump(process->process1);
}

Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  )
{ return Arcadia_Process1_getStatus(process->process1); }

void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  )
{ Arcadia_Process1_setStatus(process->process1, status); }

bool
Arcadia_Process_allocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{ return Arcadia_Process1_allocateUnmanaged_nojump(process->process1, p, n); }

bool
Arcadia_Process_deallocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void* p
  )
{ return Arcadia_Process1_deallocateUnmanaged_nojump(process->process1, p); }

bool
Arcadia_Process_reallocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{ return Arcadia_Process1_reallocateUnmanaged_nojump(process->process1, p, n); }

void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  )
{ Arcadia_Process1_visitObject(process->process1, object); }

Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process1_lockObject(process->process1, object); }

Arcadia_Status
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process1_unlockObject(process->process1, object); }
