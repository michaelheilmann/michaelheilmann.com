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

#if !defined(ARCADIA_ASSETDEFINITIONLANGUAGE_COLORDEFINITION_H_INCLUDED)
#define ARCADIA_ASSETDEFINITIONLANGUAGE_COLORDEFINITION_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/AssetDefinitionLanguage/Definition.h"

// @brief
// The definition of a "color".
//
// @code
// {
//   type  : "Types.Color",
//   name  : "Colors.Red",
//   red   : 255,
//   green : 0,
//   blue  : 0,
// }
// @endcode
//
// @code
// class Arcadia.AssetDefinitionLanguage.ColorDefinition extends Arcadia.AssetDefinitionLanguage.Definition {
//
//   field red, green, blue : Arcadia.Natural8;
//
//   constructor(name : Arcadia.String, red, green, blue : Arcadia.Natural8);
//
//   method getRed() : Arcadia.Natural8;
//   method getGreen() : Arcadia.Natural8;
//   method getBlue() : Arcadia.Natural8;
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.AssetDefinitionLanguage.ColorDefinition", Arcadia_AssetDefinitionLanguage_ColorDefinition,
                          u8"Arcadia.Object");

struct Arcadia_AssetDefinitionLanguage_ColorDefinition {
  Arcadia_AssetDefinitionLanguage_Definition _parent;
  Arcadia_Natural8Value red;
  Arcadia_Natural8Value green;
  Arcadia_Natural8Value blue;
};

Arcadia_AssetDefinitionLanguage_ColorDefinition*
Arcadia_AssetDefinitionLanguage_ColorDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue
  );

/**
 * @code
 * {
 *   type  : "Types.Color",
 *   name  : "Colors.Red",
 *   red   : 255,
 *   green : 0,
 *   blue  : 0,
 * }
 * @endcode
 */
Arcadia_AssetDefinitionLanguage_ColorDefinition*
Arcadia_AssetDefinitionLAnguage_ColorDefinition_parse
  (
    Arcadia_Thread* thread,
    Arcadia_String* input
  );

#endif  // ARCADIA_ASSETDEFINITIONLANGUAGE_COLORDEFINITION_H_INCLUDED
