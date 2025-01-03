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

// Last modified: 2024-08-27

#include "R/JumpTarget.h"

static R_JumpTarget* g_jumpTargets = NULL;

void
R_pushJumpTarget
  (
    R_JumpTarget* jumpTarget
  )
{
  jumpTarget->previous = g_jumpTargets;
  g_jumpTargets = jumpTarget;
}

void
R_popJumpTarget
  (
  )
{
  g_jumpTargets = g_jumpTargets->previous;
}

c_noreturn() void
R_jump
  (
  )
{
  longjmp(g_jumpTargets->environment, -1);
}
