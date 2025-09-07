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

#if !defined(ARCADIA_VISUALS_EVENTS_WINDOWSIZECHANGEDEVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_WINDOWSIZECHANGEDEVENT_H_INCLUDED

#include "Arcadia/Engine/Include.h"
typedef struct Arcadia_Visuals_Window Arcadia_Visuals_Window;

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_WindowSizeChangedEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.WindowSizeChangedEvent", Arcadia_Visuals_WindowSizeChangedEvent,
                          u8"Arcadia.Visuals.WindowSizeChangedEvent");

struct Arcadia_Visuals_WindowSizeChangedEvent {
  Arcadia_Engine_Event _parent;
  Arcadia_Visuals_Window* window;
  Arcadia_Integer32Value horizontalSize;
  Arcadia_Integer32Value verticalSize;
};

Arcadia_Visuals_WindowSizeChangedEvent*
Arcadia_Visuals_WindowSizeChangedEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_Window* window,
    Arcadia_Integer32Value horizontalSize,
    Arcadia_Integer32Value verticalSize
  );

#endif // ARCADIA_VISUALS_EVENTS_WINDOWSIZECHANGEDEVENT_H_INCLUDED
