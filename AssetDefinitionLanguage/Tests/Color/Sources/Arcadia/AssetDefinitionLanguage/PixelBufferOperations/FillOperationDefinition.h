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

#if !defined(ARCADIA_ASSETDEFINITIONLANGUAGE_PIXELBUFFEROPERATIONS_FILLOPERATIONDEFINITION_H_INCLUDED)
#define ARCADIA_ASSETDEFINITIONLANGUAGE_PIXELBUFFEROPERATIONS_FILLOPERATIONDEFINITION_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/AssetDefinitionLanguage/Definition.h"

// A definition of a "fill operation".
//
// @code
// {
//   type  : "Types.PixelBufferOperations.FillOperation",
//   name  : "PixelBuffOperations.FillRed",
//   color : "Colors.Red",
// }
// @endcode
//
// @code
// class Arcadia.AssetDefinitionLanguage.PixelBufferOperations.FillOperationDefinition extends Arcadia.AssetDefinitionLanguage.Definition {
//
//   field color : Arcadia.String;
//
//   constructor(qualifiedName : Arcadia.String, color : Arcadia.String);
//
//   method getColor() : Arcadia.String;
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.AssetDefinitionLanguage.PixelBufferOperations.FillOperationDefinition", Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition,
                          u8"Arcadia.AssetDefinitionLanguage.Definition");

struct Arcadia_AssetDefinitionLanguage_PixelBufferOperations_FillOperationDefinition {
  Arcadia_AssetDefinitionLanguage_Definition _parent;
  Arcadia_String* colorReference;
};

#endif  // ARCADIA_ASSETDEFINITIONLANGUAGE_PIXELBUFFEROPERATIONS_FILLOPERATIONDEFINITION_H_INCLUDED
