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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Thread.h"

#include "Arcadia/Ring1/Implementation/Thread.private.h"
#include "Arcadia/Arms/Include.h"

Arcadia_SizeValue
Arcadia_ValueStack_getSize
  (
    Arcadia_Thread* thread
  )
{ return thread->stack.size; }

Arcadia_Value
Arcadia_ValueStack_getValue
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue index
  )
{
  if (index >= thread->stack.size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return thread->stack.elements[thread->stack.size - 1 - index];
}

void
Arcadia_ValueStack_pushValue
  (
    Arcadia_Thread* thread,
    Arcadia_Value const* value
  )
{
  Arcadia_Thread_ensureValueStackFreeCapacity(thread, 1);
  thread->stack.elements[thread->stack.size] = *value;
  thread->stack.size++;
}

void
Arcadia_ValueStack_popValues
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue count
  )
{
  if (count > thread->stack.size) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  thread->stack.size -= count;
}

void
Arcadia_Thread_pushJumpTarget
  (
    Arcadia_Thread* thread,
    Arcadia_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = thread->jumpTarget;
  thread->jumpTarget = jumpTarget;
}

void
Arcadia_Thread_popJumpTarget
  (
    Arcadia_Thread* thread
  )
{
  thread->jumpTarget = thread->jumpTarget->previous;
}

Arcadia_NoReturn() void
Arcadia_Thread_jump
  (
    Arcadia_Thread* thread
  )
{
  longjmp(thread->jumpTarget->environment, -1);
}

Arcadia_Status
Arcadia_Thread_getStatus
  (
    Arcadia_Thread* thread
  )
{ return thread->status; }

void
Arcadia_Thread_setStatus
  (
    Arcadia_Thread* thread,
    Arcadia_Status status
  )
{ thread->status = status; }

Arcadia_Process*
Arcadia_Thread_getProcess
  (
    Arcadia_Thread* thread
  )
{ return thread->process; }
