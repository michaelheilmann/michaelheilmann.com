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

#if !defined(ARCADIA_VISUALS_EVENTS_WINDOWPOSITIONCHANGEDEVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_WINDOWPOSITIONCHANGEDEVENT_H_INCLUDED

#include "Arcadia/Visuals/Events/Event.h"
#include "Arcadia/Visuals/Window.h"

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_WindowPositionChangedEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.WindowPositionChangedEvent", Arcadia_Visuals_WindowPositionChangedEvent,
                          u8"Arcadia.Visuals.Event");

struct Arcadia_Visuals_WindowPositionChangedEvent {
  Arcadia_Visuals_Event _parent;
  Arcadia_Visuals_Window* window;
  Arcadia_Integer32Value horizontalPosition;
  Arcadia_Integer32Value verticalPosition;
};

Arcadia_Visuals_WindowPositionChangedEvent*
Arcadia_Visuals_WindowPositionChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_Window* window,
    Arcadia_Integer32Value horizontalPosition,
    Arcadia_Integer32Value verticalPosition
  );

#endif // ARCADIA_VISUALS_EVENTS_WINDOWPOSITIONCHANGEDEVENT_H_INCLUDED
