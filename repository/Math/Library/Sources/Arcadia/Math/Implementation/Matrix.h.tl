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

#if !defined(ARCADIA_MATH_IMPLEMENTATION_MATRIX@{dimensionality}@{scalarSuffixUppercase}_H_INCLUDED)
#define ARCADIA_MATH_IMPLEMENTATION_MATRIX@{dimensionality}@{scalarSuffixUppercase}_H_INCLUDED

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Math.Matrix@{dimensionality}@{scalarSuffix}", Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix},
                          u8"Arcadia.Object");
                          
struct Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix} {
  Arcadia_Object _parent;
  @{scalarType} elements[@{dimensionality}][@{dimensionality}];
};

Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}*
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_create
  (
    Arcadia_Thread* thread
  );

/// @@brief Assign the values of another matrix to this matrix.
/// @@param thread A pointer to this thread.
/// @@param self A pointer to this matrix.
/// @@param other A pointer to the other matrix.
/// @@remarks @@a self and @@a other may refer to the same object.
/// @@post This matrix was assigned the values of the other matrix. 
void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_assign
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  );
  
/// @@brief Compute the inversion of one matrix and assign the result to this matrix.
/// @@param thread A pointer to this thread.
/// @@param self A pointer to this matrix.
/// @@param other A pointer to the other matrix.
/// @@post This matrix was assigned the values of the inversion of the other matrix.
void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_invert
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  );

/// @@brief Compute the sum of this matrix and another matrix and assign the result to this matrix.
/// @@param thread A pointer to this thread.
/// @@param self A pointer to this matrix.
/// @@param other A pointer to the other matrix.
/// @@remarks @@a self and @@a other may refer to the same object.
/// @@post This matrix was assigned the result. 
void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_add
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  );

/// @@brief Compute the difference of this matrix and another matrix and assign the result to this matrix.
/// @@param thread A pointer to this thread.
/// @@param self A pointer to this matrix.
/// @@param other A pointer to the other matrix.
/// @@remarks @@a self and @@a other may refer to the same object.
/// @@post This matrix was assigned the result.
void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other
  );

/// @@brief Linearily interpolate between this matrix and another matrix and assign the result to this matrix.
/// @@param thread A pointer to this thread.
/// @@param self A pointer to this matrix.
/// @@param other A pointer to the other matrix.
/// @@param t The interpolation value.
/// @@remarks @@a self and @@a other may refer to the same object.
/// @@post This matrix was assigned the result.
void
Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}_lerp
  (
    Arcadia_Thread* thread,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* self,
    Arcadia_Math_Matrix@{dimensionality}@{scalarSuffix}* other,
    @{scalarType} t
  );

#endif // ARCADIA_MATH_IMPLEMENTATION_MATRIX@{dimensionality}@{scalarSuffixUppercase}_H_INCLUDED
