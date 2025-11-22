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

#if !defined(ARCADIA_ASSETDEFINITIONLANGUAGE_DEFINITION_H_INCLUDED)
#define ARCADIA_ASSETDEFINITIONLANGUAGE_DEFINITION_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// @brief A "definition".
//
// @code
// class Arcadia.AssetDefinitionLanguage.Definition extends Arcadia.Object {
//
//   field qualifiedName : Arcadia.String;
//
//   constructor(qualifiedName : Arcadia.String);
//
//   method getQualifiedName() : Arcadia.String;
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.AssetDefinitionLanguage.Definition", Arcadia_AssetDefinitionLanguage_Definition,
                          u8"Arcadia.Object");

struct Arcadia_AssetDefinitionLanguage_Definition {
  Arcadia_Object _parent;
};

#endif  // ARCADIA_ASSETDEFINITIONLANGUAGE_DEFINITION_H_INCLUDED
