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

// Last modified: 2025-01-06

#if !defined(ARCADIA_RING1_ARMSINTEGRATION_H_INCLUDED)
#define ARCADIA_RING1_ARMSINTEGRATION_H_INCLUDED

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Size.h"
#include "Arcadia/Ring1/Implementation/Process.h"

// run once
Arcadia_Status
Arcadia_Arms_step
  (
  );

/// run until nothing can be freed anymore
Arcadia_Status
Arcadia_Arms_run
  (
  );

void
Arcadia_Arms_visit
  (
    Arcadia_Process* process,
    void* object
  );

static inline Arcadia_Status
Arcadia_Arms_lock
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process_lockObject(process, object); }

static inline Arcadia_Status
Arcadia_Arms_unlock
  (
    Arcadia_Process* process,
    void* object
  )
{ return Arcadia_Process_unlockObject(process, object); }

Arcadia_BooleanValue
Arcadia_Arms_registerType_nojump
  (
    Arcadia_Process* process,
    void const* name,
    Arcadia_SizeValue nameLength,
    void *context,
    void (*typeRemoved)(void*,const uint8_t*, size_t),
    void (*visit)(void*,void*),
    void (*finalize)(void*,void*)
  );

/// @brief Allocate managed memory.
/// @param p A pointer to a <code>void*</code> variable.
/// @param name A pointer to an array of Bytes.
/// @param nameLength The number of Bytes in the array pointed to by @a name.
/// @param size The size, in Bytes, of the memory to allocate. @a 0 is a valid size.
/// @return
/// Arcadia_Status_Success on success.
/// - Arcadia_Status_AllocationFailed if an allocation failed.
/// - Arcadia_Status_TypeNotExists if the type does not exist.
/// - Arcadia_Status_ArgumentInvalid if @a p or @a name is a null pointer.
Arcadia_BooleanValue
Arcadia_allocate_nojump
  (
    Arcadia_Process* process,
    void** p,
    char const* name,
    size_t nameLength,
    size_t size
  );

#endif // ARCADIA_RING1_ARMSINTEGRATION_H_INCLUDED
