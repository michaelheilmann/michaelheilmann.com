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

// Last modified: 2024-11-11

#if !defined(MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED)
#define MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED

#include "R.h"
#include "Module/Visuals/NativeWindow.h"
#include "Module/Visuals/NativeWindowsIcon.h"
#include "Module/Visuals/PixelBuffer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

// The window is in "closed" state when it is creeated by NativeWindowsWindow_create.
// A successful call to NativeWindowsWindow_open puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to NativeWindowsWindow_close.
Rex_declareObjectType("NativeWindowsWindow", NativeWindowsWindow, "NativeWindow");

struct NativeWindowsWindow {
  NativeWindow _parent;
  HINSTANCE instanceHandle;
  HWND windowHandle;
  HDC windowDeviceContextHandle;

  R_String* title;
  NativeWindowsIcon* smallIcon;
  NativeWindowsIcon* bigIcon;
};

NativeWindowsWindow*
NativeWindowsWindow_create
  (
  );

#if 0
void
NativeWindowsWindow_open
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_close
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
R_BooleanValue
NativeWindowsWindow_getQuitRequested
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_setQuitRequested
  (
    NativeWindowsWindow* self,
    R_BooleanValue quitRequested
  );
#endif

#if 0
void
NativeWindowsWindow_update
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_getRequiredBigIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );
#endif

#if 0
void
NativeWindowsWindow_getRequiredSmallIconSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );
#endif

#if 0
NativeWindowsIcon*
NativeWindowsWindow_getBigIcon 
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_setBigIcon
  (
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );
#endif

#if 0
NativeWindowsIcon*
NativeWindowsWindow_getSmallIcon
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_setSmallIcon
  (
    NativeWindowsWindow* self,
    NativeWindowsIcon* icon
  );
#endif

#if 0
R_String*
NativeWindowsWindow_getTitle
  (
    NativeWindowsWindow* self
  );
#endif

#if 0
void
NativeWindowsWindow_setTitle
  (
    NativeWindowsWindow* self,
    R_String* title
  );
#endif

#if 0
void
NativeWindowsWindow_getCanvasSize
  (
    NativeWindowsWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  );
#endif

#endif // MODULE_VISUALS_NATIVEWINDOWSWINDOW_H_INCLUDED
