// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#define ARCADIA_VISUALS_PRIVATE (1)
#include "Arcadia/Visuals/Texture.h"

static void
Arcadia_Visuals_Texture_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Texture_constructImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Texture", Arcadia_Visuals_Texture,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Visuals_Texture_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Texture_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (0 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  self->getAddressModeU = NULL;
  self->getAddressModeV = NULL;
  self->getHeight = NULL;
  self->getMagnificationFilter = NULL;
  self->getMinificationFilter = NULL;
  self->getWidth = NULL;
  self->upload = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Texture_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getAddressModeU(thread, self); }

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Texture_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getAddressModeV(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Texture_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getHeight(thread, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Texture_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getMagnificationFilter(thread, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Texture_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getMinificationFilter(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Texture_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self
  )
{ return self->getWidth(thread, self); }

void
Arcadia_Visuals_Texture_upload
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Texture* self,
    Arcadia_Visuals_BackendContext* backendContext
  )
{ self->upload(thread, self, backendContext); }
