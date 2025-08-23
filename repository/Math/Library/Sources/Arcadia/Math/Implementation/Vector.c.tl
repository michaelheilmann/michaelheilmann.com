// The author of this software is Michael Heilmann (contact@@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@@michaelheilmann.com).
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

#define ARCADIA_MATH_PRIVATE (1)
#include "Arcadia/Math/Implementation/Vector@{dimensionality}@{scalarSuffix}.h"

static void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_constructImpl,
  .destruct = NULL,
  .visit = NULL,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Math.Vector@{dimensionality}@{scalarSuffix}", Arcadia_Math_Vector@{dimensionality}@{scalarSuffix},
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_getType(thread);
  {
    if (0 != numberOfArgumentValues) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_superTypeConstructor(thread, _type, self, 1, &argumentValues[0]);
  }
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    _self->elements[i] = @{zeroScalarLiteral};
  }
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_assign
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* other
  )
{
  if (self != other) {
    for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
      self->elements[i] = other->elements[i];
    }
  }
}

void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_invert
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    self->elements[i] = -other->elements[i];
  }
}

void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_add
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    self->elements[i] += other->elements[i];
  }
}

void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* other
  )
{
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    self->elements[i] -= other->elements[i];
  }
}

void
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* other,
    @{scalarType} t
  )
{
  if (t == @{zeroScalarLiteral}) {
    /* Intentionally empty. */
  } else if (t == @{oneScalarLiteral}) {
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_assign(thread, self, other);
  } else {
    @{scalarType} s = @{oneScalarLiteral} - t;
    for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
      self->elements[i] = s * self->elements[i] + t * self->elements[i];
    }
  }
}

@{scalarType}
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_getLength
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self
  )
{
  return Arcadia_sqrt@{scalarSuffix}Value(thread, Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_getSquaredLength(thread, self));
}

@{scalarType}
Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}_getSquaredLength
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Vector@{dimensionality}@{scalarSuffix}* self
  )
{
  @{scalarType} squaredLength = @{zeroScalarLiteral};
  for (Arcadia_SizeValue i = 0; i < @{dimensionality}; ++i) {
    squaredLength += self->elements[i] * self->elements[i];
  }
  return squaredLength;
}
