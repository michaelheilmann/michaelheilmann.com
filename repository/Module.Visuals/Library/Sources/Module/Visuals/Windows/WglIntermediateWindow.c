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

#include "Module/Visuals/Windows/WglIntermediateWindow.h"

#define ClassName "Arcadia.Visuals.Windows.WglIntermediateWindow"

#if 0
static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );
#endif

#if 0
static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  )
{ return DefaultWindowProc(hWnd, uMsg, wParam, lParam); }
#endif

static LRESULT CALLBACK
WindowProc
  (
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
  );

static void
Visuals_Window_WglIntermediateWindow_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
Visuals_Window_WglIntermediateWindow_destruct
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Visuals_Window_WglIntermediateWindow_constructImpl,
  .destruct = &Visuals_Window_WglIntermediateWindow_destruct,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType(u8"Visuals.Windows.WglIntermediateWindow", Visuals_Window_WglIntermediateWindow, u8"Arcadia.Object", Visuals_Window_WglIntermediateWindow, &_typeOperations);

static void
Visuals_Window_WglIntermediateWindow_destruct
  (
    Arcadia_Thread* thread,
    Visuals_Window_WglIntermediateWindow* self
  )
{
  if (self->gldc) {
    if (self->gldc == wglGetCurrentContext()) {
      wglMakeCurrent(self->dc, NULL);
    }
    wglDeleteContext(self->gldc);
    self->gldc = NULL;
  }
  if (self->dc) {
    ReleaseDC(self->wnd, self->dc);
    self->dc = NULL;
  }
  if (self->wnd) {
    DestroyWindow(self->wnd);
    self->wnd = NULL;
  }
  if (self->module) {
    UnregisterClass(ClassName, self->module);
    self->module = NULL;
  }
}

static void
Visuals_Window_WglIntermediateWindow_constructImpl
  (
    Arcadia_Process* process,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Visuals_Window_WglIntermediateWindow* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Visuals_Window_WglIntermediateWindow_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  _self->module = NULL;
  _self->cls = 0;
  _self->wnd = NULL;
  _self->dc = NULL;
  _self->gldc = NULL;
  Arcadia_Object_setType(Arcadia_Process_getThread(process), _self, _type);
}

Visuals_Window_WglIntermediateWindow*
Visuals_Window_WglIntermediateWindow_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Visuals_Window_WglIntermediateWindow* self = Arcadia_allocateObject(thread, _Visuals_Window_WglIntermediateWindow_getType(thread), 0, &argumentValues[0]);
  return self;
}
