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

#if !defined(ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED)
#define ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED

#include "Module/Visuals/Events/Event.h"
#include "Module/Visuals/Events/KeyboardKey.h"
#include "Module/Visuals/Events/KeyboardKeyAction.h"

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_KeyboardKeyEvent
Arcadia_declareObjectType(u8"Arcadia.Visuals.KeyboardKeyEvent", Arcadia_Visuals_KeyboardKeyEvent, u8"Arcadia.Visuals.Event");

struct Arcadia_Visuals_KeyboardKeyEvent {
  Arcadia_Visuals_Event _parent;
  Arcadia_Visuals_KeyboardKey key;
  Arcadia_Visuals_KeyboardKeyAction action;
};

Arcadia_Visuals_KeyboardKeyEvent*
Arcadia_Visuals_KeyboardKeyEvent_create
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value timestamp,
    Arcadia_Visuals_KeyboardKey key,
    Arcadia_Visuals_KeyboardKeyAction action
  );

Arcadia_Visuals_KeyboardKeyAction
Arcadia_Visuals_KeyboardKeyEvent_getAction
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  );

Arcadia_Visuals_KeyboardKey
Arcadia_Visuals_KeyboardKeyEvent_getKey
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_KeyboardKeyEvent* self
  );

#endif // ARCADIA_VISUALS_EVENTS_KEYBOARDKEYEVENT_H_INCLUDED
