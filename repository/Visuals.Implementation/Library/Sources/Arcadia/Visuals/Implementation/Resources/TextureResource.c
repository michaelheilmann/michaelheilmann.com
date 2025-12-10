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

#include "Arcadia/Visuals/Implementation/Resources/TextureResource.h"

static void
Arcadia_Visuals_Implementation_TextureResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_TextureResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

static void
Arcadia_Visuals_Implementation_TextureResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&Arcadia_Visuals_Implementation_TextureResource_constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&Arcadia_Visuals_Implementation_TextureResource_destructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Visuals_Implementation_TextureResource_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Visuals.Implementation.TextureResource", Arcadia_Visuals_Implementation_TextureResource,
                         u8"Arcadia.Visuals.Implementation.Resource", Arcadia_Visuals_Implementation_Resource,
                         &_typeOperations);

static void
Arcadia_Visuals_Implementation_TextureResource_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Visuals_Implementation_TextureResource_getType(thread);
  Arcadia_SizeValue numberOfArgumentValues = Arcadia_ValueStack_getNatural8Value(thread, 0);
  if (1 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  {
    Arcadia_Value t;
    t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }

  self->getAddressModeU = NULL;
  self->getAddressModeV = NULL;

  self->getHeight = NULL;

  self->getMagnificationFilter = NULL;
  self->getMinificationFilter = NULL;

  self->getWidth = NULL;

  self->setAddressModeU = NULL;
  self->setAddressModeV = NULL;

  self->setHeight = NULL;
  
  self->setMagnificationFilter = NULL;
  self->setMinificationFilter = NULL;

  self->setWidth = NULL;  

  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, numberOfArgumentValues + 1);
}

static void
Arcadia_Visuals_Implementation_TextureResource_destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_Visuals_Implementation_TextureResource_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{/*Intentionally empty.*/}

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_TextureResource_getAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getAddressModeU(thread, self); }

Arcadia_Visuals_TextureAddressMode
Arcadia_Visuals_Implementation_TextureResource_getAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getAddressModeV(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Implementation_TextureResource_getHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getHeight(thread, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_TextureResource_getMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getMagnificationFilter(thread, self); }

Arcadia_Visuals_TextureFilter
Arcadia_Visuals_Implementation_TextureResource_getMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getMinificationFilter(thread, self); }

Arcadia_Integer32Value
Arcadia_Visuals_Implementation_TextureResource_getWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self
  )
{ return self->getWidth(thread, self); }

void
Arcadia_Visuals_Implementation_TextureResource_setAddressModeU
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  )
{ self->setAddressModeU(thread, self, addressMode); }

void
Arcadia_Visuals_Implementation_TextureResource_setAddressModeV
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureAddressMode addressMode
  )
{ self->setAddressModeU(thread, self, addressMode); }

void
Arcadia_Visuals_Implementation_TextureResource_setHeight
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Integer32Value height
  )
{ self->setHeight(thread, self, height); }

void
Arcadia_Visuals_Implementation_TextureResource_setMagnificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureFilter magnificationFilter
  )
{ self->setMagnificationFilter(thread, self, magnificationFilter); }

void
Arcadia_Visuals_Implementation_TextureResource_setMinificationFilter
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Visuals_TextureFilter minificationFilter
  )
{ self->setMinificationFilter(thread, self, minificationFilter); }

void
Arcadia_Visuals_Implementation_TextureResource_setWidth
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Implementation_TextureResource* self,
    Arcadia_Integer32Value width
  )
{ self->setWidth(thread, self, width); }
