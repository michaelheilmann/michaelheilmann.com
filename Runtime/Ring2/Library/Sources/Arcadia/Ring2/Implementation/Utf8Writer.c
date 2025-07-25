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

#define ARCADIA_RING2_PRIVATE (1)
#include "Arcadia/Ring2/Implementation/Utf8Writer.h"

static void
Arcadia_Utf8Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Utf8Writer_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Utf8Writer", Arcadia_Utf8Writer, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
Arcadia_Utf8Writer_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Utf8Writer* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Utf8Writer_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->writeBytes = NULL;
  _self->writeCodePoints = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

void
Arcadia_Utf8Writer_writeBytes
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  )
{
  self->writeBytes(thread, self, bytes, numberOfBytes);
}

void
Arcadia_Utf8Writer_writeCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* self,
    Arcadia_Natural32Value const* codePoints,
    Arcadia_SizeValue numberOfCodePoints
  )
{
  self->writeCodePoints(thread, self, codePoints, numberOfCodePoints);
}

void
Arcadia_Utf8Writer_writeString
  (
    Arcadia_Thread* thread,
    Arcadia_Utf8Writer* self,
    Arcadia_String* string
  )
{
  self->writeString(thread, self, string);
}