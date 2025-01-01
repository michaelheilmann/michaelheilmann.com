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

// Last modified: 2024-12-31

#include "Module/Visuals/NativeWindow.h"

static void
NativeWindow_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &NativeWindow_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
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

Rex_defineObjectType("NativeWindow", NativeWindow, "R.Object", R_Object, &_typeOperations);

static void
NativeWindow_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  NativeWindow* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _NativeWindow_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Type_getOperations(R_Type_getParentObjectType(_type))->objectTypeOperations->construct(self, 0, &argumentValues[0]);
  }
  _self->open = NULL;
  _self->close = NULL;
  _self->getQuitRequested = NULL;
  _self->setQuitRequested = NULL;
  _self->update = NULL;
  _self->getRequiredBigIconSize = NULL;
  _self->getRequiredSmallIconSize = NULL;
  _self->getBigIcon = NULL;
  _self->setBigIcon = NULL;
  _self->getSmallIcon = NULL;
  _self->setSmallIcon = NULL;
  _self->getTitle = NULL;
  _self->setTitle  = NULL;
  _self->getCanvasSize = NULL;
  R_Object_setType(_self, _type);
}

void
NativeWindow_open
  (
    NativeWindow* self
  )
{ self->open(self); }

void
NativeWindow_close
  (
    NativeWindow* self
  ) 
{ self->close(self); }

R_BooleanValue
NativeWindow_getQuitRequested
  (
    NativeWindow* self
  )
{ return self->getQuitRequested(self); }

void
NativeWindow_setQuitRequested
  (
    NativeWindow* self,
    R_BooleanValue quitRequested
  )
{ self->setQuitRequested(self, quitRequested); }

void
NativeWindow_update
  (
    NativeWindow* self
  )
{ self->update(self); }

void
NativeWindow_getRequiredBigIconSize
  (
    NativeWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{ self->getRequiredBigIconSize(self, width, height); }

void
NativeWindow_getRequiredSmallIconSize
  (
    NativeWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{ self->getRequiredSmallIconSize(self, width, height); }

NativeIcon*
NativeWindow_getBigIcon
  (
    NativeWindow* self
  )
{ return self->getBigIcon(self); }

void
NativeWindow_setBigIcon
  (
    NativeWindow* self,
    NativeIcon* icon
  )
{ self->setBigIcon(self, icon); }

NativeIcon*
NativeWindow_getSmallIcon
  (
    NativeWindow* self
  )
{ return self->getSmallIcon(self); }

void
NativeWindow_setSmallIcon
  (
    NativeWindow* self,
    NativeIcon* icon
  )
{ self->setSmallIcon(self, icon); }

R_String*
NativeWindow_getTitle
  (
    NativeWindow* self
  )
{ return self->getTitle(self); }

void
NativeWindow_setTitle
  (
    NativeWindow* self,
    R_String* title
  )
{ self->setTitle(self, title); }

void
NativeWindow_getCanvasSize
  (
    NativeWindow* self,
    R_Integer32Value* width,
    R_Integer32Value* height
  )
{ self->getCanvasSize(self, width, height); }
