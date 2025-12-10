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

#if !defined(ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED

#if !defined(ARCADIA_ADL_PRIVATE)
  #error("do not include directly, include `Arcadia/ADL/Include.h` instead")
#endif
#include "Arcadia/ADL/Definition.h"

// A definition of a pixel buffer.
//
// @code
// {
//   type  : "PixelBuffer",
//   name  : "MyGame.CheckerboardPixelBuffer",
// }
// @endcode
//
// @code
// class Arcadia.ADL.PixelBufferDefinition extends Arcadia.ADL.Definition {
//
//   constructor(definitions : Arcadia.ADL.Definitions, qualifiedName : Arcadia.String)
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.PixelBufferDefinition", Arcadia_ADL_PixelBufferDefinition,
                          u8"Arcadia.ADL.Definition");

struct Arcadia_ADL_PixelBufferDefinition {
  Arcadia_ADL_Definition _parent;
};

Arcadia_ADL_PixelBufferDefinition*
Arcadia_ADL_PixelBufferDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* qualifiedName
  );

#endif  // ARCADIA_ADL_DEFINITIONS_FILLOPERATIONDEFINITION_H_INCLUDED
