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

#include "R/ArmsIntegration.private.h"

#include "Arms.h"

R_Status
R_Arms_startup
  (
  )
{
  Arms_Status status = Arms_startup();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

R_Status
R_Arms_shutdown
  (
  )
{
  Arms_Status status = Arms_shutdown();
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

R_Status
R_Arms_step
  (
  )
{
  Arms_RunStatistics statistics = { .destroyed = 0 };
  Arms_Status status = Arms_run(&statistics);
  switch (status) {
    case Arms_Status_Success:
    { return R_Status_Success; }
    break;
    case Arms_Status_AllocationFailed:
    case Arms_Status_OperationInvalid:
    case Arms_Status_ArgumentValueInvalid:
    case Arms_Status_TypeExists:
    case Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is R_Status_EnvironmentInvalid.
      return R_Status_OperationInvalid;
    } break;
  };
}

R_Status
R_Arms_run
  (
  )
{
  Arms_RunStatistics statistics = { .destroyed = 0 };
  do {
    Arms_Status status = Arms_run(&statistics);
    switch (status) {
      case Arms_Status_Success:
      {/*Intentionally empty.*/ }
      break;
      case Arms_Status_AllocationFailed:
      case Arms_Status_OperationInvalid:
      case Arms_Status_ArgumentValueInvalid:
      case Arms_Status_TypeExists:
      case Arms_Status_TypeNotExists:
      default: {
        // This should not happen.
        // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
        // Suggestion is R_Status_EnvironmentInvalid.
        return R_Status_OperationInvalid;
      } break;
    };
  } while (statistics.destroyed > 0);
  return R_Status_Success;
}

void
R_Arms_visit
  (
    void* object
  )
{
  if (object) {
    Arms_visit(object);
  }
}

R_Status
R_Arms_lock
  (
    void* object
  )
{
  Arms_Status status = Arms_lock(object);
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid: {
      return R_Status_OperationInvalid;
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      return R_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return R_Status_ArgumentValueInvalid;
    } break;
  };
}

R_Status
R_Arms_unlock
  (
    void* object
  )
{
  Arms_Status status = Arms_unlock(object);
  switch (status) {
    case Arms_Status_Success: {
      return R_Status_Success;
    } break;
    case Arms_Status_AllocationFailed: {
      return R_Status_AllocationFailed;
    } break;
    case Arms_Status_OperationInvalid: {
      return R_Status_OperationInvalid;
    } break;
    case Arms_Status_ArgumentValueInvalid: {
      return R_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return R_Status_ArgumentValueInvalid;
    } break;
  };
}

R_BooleanValue
R_Arms_registerType_nojump
  (
    void const* name,
    R_SizeValue nameLength,
    void (*typeRemoved)(uint8_t const*, size_t),
    void (*visit)(void*),
    void (*finalize)(void*)
  )
{
  Arms_Status status = Arms_addType(name, nameLength, typeRemoved, visit, finalize);
  if (status) {
    switch (status) {
      case Arms_Status_AllocationFailed: {
        R_setStatus(R_Status_AllocationFailed);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        R_setStatus(R_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        R_setStatus(R_Status_OperationInvalid);
      } break;
      case Arms_Status_TypeExists: {
        R_setStatus(R_Status_OperationInvalid);
      } break;
      default: {
        R_setStatus(R_Status_OperationInvalid);
      } break;
    };
    return R_BooleanValue_False;
  } else {
    return R_BooleanValue_True;
  }
}

R_BooleanValue
R_allocate_nojump
  (
    void** p,
    char const* name,
    size_t nameLength,
    size_t size
  )
{
  void* q = NULL;
  Arms_Status status = Arms_allocate(&q, name, nameLength, size);
  if (status) {
    switch (status) {
      case Arms_Status_AllocationFailed: {
        R_setStatus(Arms_Status_AllocationFailed);
      } break;
      case Arms_Status_TypeNotExists: {
        R_setStatus(Arms_Status_TypeNotExists);
      } break;
      case Arms_Status_ArgumentValueInvalid: {
        R_setStatus(Arms_Status_ArgumentValueInvalid);
      } break;
      case Arms_Status_OperationInvalid: {
        R_setStatus(Arms_Status_OperationInvalid);
      } break;
      default: {
        R_setStatus(Arms_Status_OperationInvalid);
      } break;
    };
    return R_BooleanValue_False;
  } else {
    *p = q;
    return R_BooleanValue_True;
  }
}

R_BooleanValue
R_allocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  )
{
  Arms_Status status = Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else if (status == Arms_Status_AllocationFailed) {
      R_setStatus(R_Status_AllocationFailed);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}

R_BooleanValue
R_deallocateUnmanaged_nojump
  (
    void* p
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), p);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}

R_BooleanValue
R_reallocateUnmanaged_nojump
  (
    void** p,
    R_SizeValue n
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      R_setStatus(R_Status_ArgumentValueInvalid);
    } else if (status == Arms_MemoryManager_Status_AllocationFailed) {
      R_setStatus(R_Status_AllocationFailed);
    } else {
      R_setStatus(R_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use R_Status_EnvironmentInvalid.*/
    }
    return R_BooleanValue_False;
  }
  return R_BooleanValue_True;
}
