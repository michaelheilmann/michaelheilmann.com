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

#include "Arcadia/AssetDefinitionLanguage/PixelBufferOperations/FillOperationDefinition.h"

static void
Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition* self
  );

static void
Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.AssetDefinitionLanguage.PixelBufferOperations.FillOperationDefinition", Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition,
                         u8"Arcadia.AssetDefinitionLanguage.Definition", Arcadia_AssetDefinitionLanguage_Definition,
                         &_typeOperations);

static void
Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition_getType(thread);
  {
    Arcadia_Value t = Arcadia_ValueStack_getValue(thread, 2);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 2 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->colorReference = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_String_getType(thread));
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 2 + 1);
}
