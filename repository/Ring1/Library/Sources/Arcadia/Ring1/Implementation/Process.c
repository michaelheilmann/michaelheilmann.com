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
#include "Arcadia/Ring1/Implementation/Process.h"

#include "Arcadia/Arms/Include.h"
#include "Arcadia/Ring1/Implementation/StaticAssert.h"
#include "Arcadia/Ring1/Implementation/Diagnostics.h"
#include "Arcadia/Ring1/Implementation/Atoms.private.h"
#include "Arcadia/Ring1/Implementation/Thread.private.h"
#include "Arcadia/Ring1/Implementation/Types.private.h"
#include <stdbool.h>
#include <string.h>

typedef const ModuleInfo* (GetModuleInfo)();
static GetModuleInfo* g_modules[] = {
  &Arcadia_Atoms_getModule,
  &Arcadia_Types_getModule,
};
static size_t g_initializedModules = 0;
static const size_t g_numberOfModules = sizeof(g_modules) / sizeof(const ModuleInfo*);

static void
startupModules
  (
    Arcadia_Process* process
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    for (size_t i = 0, n = g_numberOfModules; i < n; ++i) {
      g_modules[i]()->onStartUp(thread);
      g_initializedModules++;
    }
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    while (g_initializedModules > 0) {
      Arcadia_Process_runArms(process, true);
      g_modules[--g_initializedModules]()->onShutDown(thread);
    }
    Arcadia_Process_runArms(process, true);
    Arcadia_Thread_jump(thread);
  }
}

static void
shutdownModules
  (
    Arcadia_Process* process
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  while (g_initializedModules > 0) {
    Arcadia_Process_runArms(process, true);
    g_modules[--g_initializedModules]()->onShutDown(thread);
  }
  Arcadia_Process_runArms(process, true);
}

typedef struct ArmsCallbackNode ArmsCallbackNode;

struct ArmsCallbackNode {
  ArmsCallbackNode* next;
  void (*onPreMark)(Arcadia_Thread*, bool);
  void (*onVisit)(Arcadia_Thread*);
  void (*onFinalize)(Arcadia_Thread*, size_t*);
};

static Arcadia_Status
startupArms
  (
  );

static Arcadia_Status
shutdownArms
  (
  );

static Arcadia_Status
startupArms
  (
  )
{
  Arcadia_Arms_Status status = Arms_startup();
  switch (status) {
    case Arcadia_Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arcadia_Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arcadia_Arms_Status_OperationInvalid:
    case Arcadia_Arms_Status_ArgumentValueInvalid:
    case Arcadia_Arms_Status_TypeExists:
    case Arcadia_Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

static Arcadia_Status
shutdownArms
  (
  )
{
  Arcadia_Arms_Status status = Arms_shutdown();
  switch (status) {
    case Arcadia_Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arcadia_Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arcadia_Arms_Status_OperationInvalid:
    case Arcadia_Arms_Status_ArgumentValueInvalid:
    case Arcadia_Arms_Status_TypeExists:
    case Arcadia_Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

/// @brief The type of a reference counter.
typedef uint32_t ReferenceCount;

/// @brief The minimum value of a reference counter.
#define ReferenceCount_Minimum (UINT32_C(0))

/// @brief The maximum value of a reference counter.
#define ReferenceCount_Maximum (UINT32_MAX)

Arcadia_StaticAssert(ReferenceCount_Minimum < ReferenceCount_Maximum, "environment not (yet) supported");

/// @brief Increment a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return the new reference count value
static inline ReferenceCount ReferenceCount_increment(ReferenceCount* referenceCount) {
  return ++(*referenceCount);
}

/// @brief Decrement a reference counter.
/// @param referenceCounter A pointer to the reference counter.
/// @return the new reference count value
static inline ReferenceCount ReferenceCount_decrement(ReferenceCount* referenceCount) {
  return --(*referenceCount);
}

struct Arcadia_Process {
  ReferenceCount referenceCount;
  Arcadia_Thread thread;
  ArmsCallbackNode* armsCallbackNodes;
};

static Arcadia_Process* g_process = NULL;

Arcadia_Thread*
Arcadia_Process_getThread
  (
    Arcadia_Process* process
  )
{ return &process->thread; }

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
    shutdownModules(process);
    Arcadia_Thread_uninitialize(&process->thread);
    Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), g_process);
    g_process = NULL;
    if (Arms_shutdown()) {
      Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
    }
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
    if (Arms_startup()) {
      return Arcadia_ProcessStatus_EnvironmentFailed;
    }
    if (Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), &g_process, sizeof(Arcadia_Process))) {
      if (Arms_shutdown()) {
        Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
      return Arcadia_ProcessStatus_AllocationFailed;
    }
    g_process->referenceCount = ReferenceCount_Minimum + 1;
    Arcadia_Thread_initialize(&g_process->thread);
    g_process->armsCallbackNodes = NULL;
    g_process->thread.process1 = g_process;

    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(&g_process->thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      startupModules(g_process);
      Arcadia_Thread_popJumpTarget(&g_process->thread);
    } else {
      Arcadia_Thread_popJumpTarget(&g_process->thread);
      shutdownModules(g_process);
      Arcadia_Thread_uninitialize(&g_process->thread);
      Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), g_process);
      g_process = NULL;
      if (Arms_shutdown()) {
        Arcadia_logf(Arcadia_LogFlags_Error, "%s:%d: %s failed\n", __FILE__, __LINE__, "Arms_shutdown");
      }
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
Arcadia_Process_fillMemory
  (
    Arcadia_Process* process,
    void* p,
    size_t n,
    uint8_t v
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  memset(p, v, n);
}

void
Arcadia_Process_copyMemory
  (
    Arcadia_Process* process,
    void* p,
    const void* q,
    size_t n
  )
{
  Arcadia_StaticAssert(UINTPTR_MAX == SIZE_MAX, "environment not (yet) supported");

  if (UINTPTR_MAX - n < ((uintptr_t)p) || UINTPTR_MAX - n < ((uintptr_t)q)) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  // Determine if the intervals a = [a.start, a.end] and b = [b.start, b.end] DO overlap.
  //
  // They do NOT overlap if condition [1] or condition [2] is fulfilled:
  // [1] a is completely behind b that is a.start > b.end.
  // [2] b is completely behind a that is b.start > a.end
  // That is, they do not overlap if
  // ([1] OR [1])
  // holds.
  // Consequently, a and b overlap if
  // NOT ([1] OR [2])
  // holds which can be rewritten
  //     NOT ([1] OR [2])
  // <=> NOT [1] AND NOT [2]
  // <=> NOT (a.start > b.end) AND NOT (b.start > a.end)
  // <=> a.start <= b.end AND b.start <= a.end
  //
  // Now let s.start = ((uintptr_t)p), a.end = ((uintptr_t)p) + n, b.start = ((uintptr_t)q), b.end = ((uintptr_t)q) + n to obtain
  bool overlapping = (((uintptr_t)p) <= ((uintptr_t)q) + n)
                  && (((uintptr_t)q) <= ((uintptr_t)p) + n);
  if (!overlapping) {
    memmove(p, q, n);
  } else {
    memcpy(p, q, n);
  }
}

Arcadia_Integer32Value
Arcadia_Process_compareMemory
  (
    Arcadia_Process* process,
    const void* p,
    const void* q,
    Arcadia_SizeValue n
  )
{
  if (!p || !q) {
    Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  return memcmp(p, q, n);
}

void
Arcadia_Process_allocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{
  Arcadia_Arms_Status status = Arms_MemoryManager_allocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arcadia_Arms_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arcadia_Arms_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_deallocateUnmanaged
  (
    Arcadia_Process* process,
    void* p
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_deallocate(Arms_getDefaultMemoryManager(), p);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_reallocateUnmanaged
  (
    Arcadia_Process* process,
    void** p,
    size_t n
  )
{
  Arms_MemoryManager_Status status = Arms_MemoryManager_reallocate(Arms_getDefaultMemoryManager(), p, n);
  if (status) {
    if (status == Arms_MemoryManager_Status_ArgumentValueInvalid) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
    } else if (status == Arms_MemoryManager_Status_AllocationFailed) {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
    } else {
      Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed); /*@todo As ARMs behaves incorrectly, we should use Arcadia_Status_EnvironmentInvalid.*/
    }
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_visitObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  if (object) {
    Arms_visit(object);
  }
}

Arcadia_Status
Arcadia_Process_lockObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  Arcadia_Arms_Status status = Arms_lock(object);
  switch (status) {
    case Arcadia_Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arcadia_Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arcadia_Arms_Status_OperationInvalid: {
      return Arcadia_Status_OperationInvalid;
    } break;
    case Arcadia_Arms_Status_ArgumentValueInvalid: {
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process_unlockObject
  (
    Arcadia_Process* process,
    void* object
  )
{
  Arcadia_Arms_Status status = Arms_unlock(object);
  switch (status) {
    case Arcadia_Arms_Status_Success: {
      return Arcadia_Status_Success;
    } break;
    case Arcadia_Arms_Status_AllocationFailed: {
      return Arcadia_Status_AllocationFailed;
    } break;
    case Arcadia_Arms_Status_OperationInvalid: {
      return Arcadia_Status_OperationInvalid;
    } break;
    case Arcadia_Arms_Status_ArgumentValueInvalid: {
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
    default: {
      // This should not happen.
      return Arcadia_Status_ArgumentValueInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process_stepArms
  (
    Arcadia_Process* process
  )
{
  Arms_RunStatistics statistics = { .destroyed = 0 };
  Arcadia_Arms_Status status = Arms_run(&statistics);
  switch (status) {
    case Arcadia_Arms_Status_Success:
    { return Arcadia_Status_Success; }
    break;
    case Arcadia_Arms_Status_AllocationFailed:
    case Arcadia_Arms_Status_OperationInvalid:
    case Arcadia_Arms_Status_ArgumentValueInvalid:
    case Arcadia_Arms_Status_TypeExists:
    case Arcadia_Arms_Status_TypeNotExists:
    default: {
      // This should not happen.
      // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
      // Suggestion is Arcadia_Status_EnvironmentInvalid.
      return Arcadia_Status_OperationInvalid;
    } break;
  };
}

Arcadia_Status
Arcadia_Process_runArms
  (
    Arcadia_Process* process,
    bool purgeCaches
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arms_RunStatistics statistics = { .destroyed = 0 };
  do {
    for (ArmsCallbackNode* node = process->armsCallbackNodes; NULL != node; node = node->next) {
      if (node->onPreMark) {
        node->onPreMark(thread, purgeCaches);
      }
    }
    Arcadia_Arms_Status status = Arms_run(&statistics);
    switch (status) {
      case Arcadia_Arms_Status_Success:
      {/*Intentionally empty.*/ }
      break;
      case Arcadia_Arms_Status_AllocationFailed:
      case Arcadia_Arms_Status_OperationInvalid:
      case Arcadia_Arms_Status_ArgumentValueInvalid:
      case Arcadia_Arms_Status_TypeExists:
      case Arcadia_Arms_Status_TypeNotExists:
      default: {
        // This should not happen.
        // @todo A different error code shall be returned if Arms_shutdown returns an unspecified error code.
        // Suggestion is Arcadia_Status_EnvironmentInvalid.
        return Arcadia_Status_OperationInvalid;
      } break;
    };
    for (ArmsCallbackNode* node = process->armsCallbackNodes; NULL != node; node = node->next) {
      if (node->onFinalize) {
        size_t destroyed;
        node->onFinalize(thread, &destroyed);
        if (SIZE_MAX - destroyed < statistics.destroyed) {
          statistics.destroyed = SIZE_MAX;
        } else {
          statistics.destroyed += destroyed;
        }
      }
    }
  } while (statistics.destroyed > 0);
  return Arcadia_Status_Success;
}

void
Arcadia_Process_addArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = NULL;
  armsCallbackNode->onPreMark = callback;
  armsCallbackNode->onVisit = NULL;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsPreMarkCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_PreMarkCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onPreMark == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_addArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = NULL;
  armsCallbackNode->onPreMark = NULL;
  armsCallbackNode->onVisit = callback;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsVisitCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_VisitCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onVisit == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_addArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  )
{
  ArmsCallbackNode* armsCallbackNode = NULL;
  Arcadia_Process_allocateUnmanaged(process, &armsCallbackNode, sizeof(ArmsCallbackNode));
  armsCallbackNode->onFinalize = callback;
  armsCallbackNode->onPreMark = NULL;
  armsCallbackNode->onVisit = NULL;
  armsCallbackNode->next = process->armsCallbackNodes;
  process->armsCallbackNodes = armsCallbackNode;
}

void
Arcadia_Process_removeArmsFinalizeCallback
  (
    Arcadia_Process* process,
    Arcadia_Process_FinalizeCallback* callback
  )
{
  ArmsCallbackNode** previous = &process->armsCallbackNodes;
  ArmsCallbackNode* current = process->armsCallbackNodes;
  while (current) {
    if (current->onFinalize == callback) {
      *previous = current->next;
      ArmsCallbackNode* node = current;
      Arcadia_Process_deallocateUnmanaged(process, node);
      break;
    } else {
      previous = &current->next;
      current = current->next;
    }
  }
}

void
Arcadia_Process_registerType
  (
    Arcadia_Process* process,
    const char* name,
    size_t nameLength,
    void* context,
    void (*typeRemoved)(void*, uint8_t const*, size_t),
    void (*visit)(void*, void*),
    void (*finalize)(void*, void*)
  )
{
  Arcadia_Arms_Status status = Arms_addType(name, nameLength, context, typeRemoved, visit, finalize);
  if (status) {
    switch (status) {
      case Arcadia_Arms_Status_AllocationFailed: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
      } break;
      case Arcadia_Arms_Status_ArgumentValueInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
      } break;
      case Arcadia_Arms_Status_OperationInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
      case Arcadia_Arms_Status_TypeExists: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
    };
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
}

void
Arcadia_Process_allocate
  (
    Arcadia_Process* process,
    void** p,
    const char* name,
    size_t nameLength,
    size_t size
  )
{
  void* q = NULL;
  Arcadia_Arms_Status status = Arms_allocate(&q, name, nameLength, size);
  if (status) {
    switch (status) {
      case Arcadia_Arms_Status_AllocationFailed: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_AllocationFailed);
      } break;
      case Arcadia_Arms_Status_TypeNotExists: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TypeNotExists);
      } break;
      case Arcadia_Arms_Status_ArgumentValueInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_ArgumentValueInvalid);
      } break;
      case Arcadia_Arms_Status_OperationInvalid: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
      default: {
        Arcadia_Thread_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_OperationInvalid);
      } break;
    };
    Arcadia_Thread_jump(Arcadia_Process_getThread(process));
  }
  *p = q;
}

void
Arcadia_Process_reverseMemory16
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural16Value* front = p;
    Arcadia_Natural16Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural16Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Process_reverseMemory32
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural32Value* front = p;
    Arcadia_Natural32Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural32Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Process_reverseMemory64
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural64Value* front = p;
    Arcadia_Natural64Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural64Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}

void
Arcadia_Process_reverseMemory8
  (
    Arcadia_Thread* thread,
    void* p,
    size_t n
  )
{
  if (n) {
    Arcadia_Natural8Value* front = p;
    Arcadia_Natural8Value* back = front + (n - 1);
    for (Arcadia_SizeValue i = 0, m = n / 2; i < m; ++i) {
      Arcadia_Natural8Value temporary = *front;
      *front = *back;
      *back = temporary;
      ++front;
      --back;
    }
  }
}
