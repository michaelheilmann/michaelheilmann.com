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

#if !defined(ARCADIA_ENGINE_ENGINE_H_INCLUDED)
#define ARCADIA_ENGINE_ENGINE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
typedef struct Arcadia_Engine_Event Arcadia_Engine_Event;
typedef struct Arcadia_Engine_System Arcadia_Engine_System;

/// @code
/// class Arcadia.Engine {
///   construct
///     (
///     )
/// }
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Engine", Arcadia_Engine,
                          u8"Arcadia.Object")

struct Arcadia_Engine {
  Arcadia_Object _parent;

  /// Set of Arcadia.Visuals.Backend derived type objects.
  Arcadia_Set* visualBackendTypes;
  
  /// Set of Arcadia.Audials.Backend derived type objects.
  Arcadia_Set* audialsBackendTypes;
  
  /// Pointer to the active visuals system if any, null otherwise.
  Arcadia_Engine_System* visualsSystem;
  
  /// Pointer to the active audials system if any, null otherwise.
  Arcadia_Engine_System* audialsSystem;
    
  /// @brief The event queue.
  Arcadia_Deque* events;

  void (*update)(Arcadia_Thread* thread, Arcadia_Engine* self);
};

/// @brief Enque an event to this application.
/// @param thread A pointer to this thread.
/// @param self A pointer to this application.
/// @param event A pointer to the event.
void
Arcadia_Engine_enqueEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self,
    Arcadia_Engine_Event* event
  );

/// @brief Deque an event from this engine.
/// @param thread A pointer to this thread.
/// @param self A pointer to this engine.
/// @return A pointer to the event (if there is an event), a null pointer otherwise.
Arcadia_Engine_Event*
Arcadia_Engine_dequeEvent
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
  );

/// @brief Update this engine.
/// @param thread A pointer to this thread.
/// @param self A pointer to this engine.
void
Arcadia_Engine_update
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* self
  );

/// @brief Get or create the engine singleton.
/// @param thread A pointer to this thread.
/// @return A pointer to the engine singleton.
Arcadia_Engine*
Arcadia_Engine_getOrCreate
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_ENGINE_ENGINE_H_INCLUDED
