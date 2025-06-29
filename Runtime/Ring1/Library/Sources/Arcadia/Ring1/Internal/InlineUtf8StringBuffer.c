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
#include "Arcadia/Ring1/Internal/InlineUtf8StringBuffer.h"

#include "Arcadia/Ring1/Implementation/Process.h"

void
Arcadia_InlineUtf8StringBuffer_initialize
  (
    Arcadia_Thread* thread,
    Arcadia_InlineUtf8StringBuffer* self,
    Arcadia_SizeValue initialCapacity
  )
{
  self->capacity = initialCapacity;
  self->size = 0;
  Arcadia_Process_allocateUnmanaged(Arcadia_Thread_getProcess(thread), &self->elements, initialCapacity);
}

void
Arcadia_InlineUtf8StringBuffer_uninitialize
  (
    Arcadia_Thread* thread,
    Arcadia_InlineUtf8StringBuffer* self
  )
{
  if (self->elements) {
    Arcadia_Process_deallocateUnmanaged(Arcadia_Thread_getProcess(thread), self->elements);
    self->elements = NULL;
  }
}
