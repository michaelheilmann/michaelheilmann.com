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

// Last modified: 2024-08-27

#if !defined(ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED)
#define ARCADIA_RING1_IMPLEMENTATION_PROCESS_H_INCLUDED

#include "Arcadia/Ring1/Implementation/NoReturn.h"
#include "Arcadia/Ring1/Implementation/Process1.h"
#include <stdint.h>
#include <setjmp.h>

/// the process object provides access to the current thread.
/// the current thread provides access to the thread's jump target stack and the thread's status variable.
typedef struct Arcadia_Process Arcadia_Process;

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process_acquire
  (
    Arcadia_Process* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
Arcadia_ProcessStatus
Arcadia_Process_relinquish
  (
    Arcadia_Process* process
  );

/// @return #Arcadia_ProcessStatus_Success on success.
/// - #Arcadia_ProcessStatus_ArgumentValueInvalid @a process is a null pointer
/// - #Arcadia_ProcessStatus_OperationInvalid the reference counter would overflow or underflow from this call
/// - #Arcadia_ProcessStatus_EnvironmentFailed initialization of Arcadia ARMS failed
/// - #Arcadia_ProcessStatus_AllocationFailed an allocation failed
Arcadia_ProcessStatus
Arcadia_Process_get
  (
    Arcadia_Process** process
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined @a jumpTarget does not point to an Arcadia_JumpTarget object
void
Arcadia_Process_pushJumpTarget
  (
    Arcadia_Process* process,
    R_JumpTarget* jumpTarget
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined the jump target stack of the Arcadia_Process object is empty
void
Arcadia_Process_popJumpTarget
  (
    Arcadia_Process* process
  );

/// @undefined @a process does not refer to a Arcadia_Process object
/// @undefined the jump target stack of the Arcadia_Process object is empty
Arcadia_NoReturn() void
Arcadia_Process_jump
  (
    Arcadia_Process* process
  );

/// @return the status value
/// @undefined @a process does not refer to a Arcadia_Process object
Arcadia_Status
Arcadia_Process_getStatus
  (
    Arcadia_Process* process
  );

/// @param status the status value
/// @undefined @a process does not refer to a Arcadia_Process object
void
Arcadia_Process_setStatus
  (
    Arcadia_Process* process,
    Arcadia_Status status
  );

/// @brief
/// Allocate unmanaged memory.
/// @param process A pointer to the Arcadia_Process1 object
/// @return
/// #true on success. #false on failure
/// @remarks
/// This function sets the status variable on failure. However, it does not invoke Arcadia_Process1_jump(),
/// If <code>p</code> is a null pointer, then #Arcadia_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #Arcadia_Status_AllocationFailed is assigned.
bool
Arcadia_Process_allocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  );

/// @brief
/// Reallocate unmanaged memory.
/// @param process A pointer to the Arcadia_Process1 object
/// @return
/// #true on success. #false on failure
/// @remarks
/// This function sets the status variable on failure. However, it does not invoke Arcadia_Process1_jump(),
/// If <code>p</code> is a null pointer, then #Arcadia_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #Arcadia_Status_AllocationFailed is assigned.
bool
Arcadia_Process_deallocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void* p
  );

/// @brief
/// Deallocate unmanaged memory.
/// @param process A pointer to the Arcadia_Process1 object
/// @return
/// #true on success. #false on failure
/// @remarks
/// This function sets the status variable on failure. However, it does not invoke Arcadia_Process1_jump(),
/// If <code>p</code> is a null pointer, then #Arcadia_Status_ArgumentValueInvalid is assigned.
/// If the allocation failed, then #Arcadia_Status_AllocationFailed is assigned.
bool
Arcadia_Process_reallocateUnmanaged_nojump
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  );

/// @param process A pointer to the Arcadia_Process object
void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process object
Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
    void* object
  );

/// @param process A pointer to the Arcadia_Process object
Arcadia_Status
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
    void* object
  );

#endif // R_JUMPTARGET_H_INCLUDED