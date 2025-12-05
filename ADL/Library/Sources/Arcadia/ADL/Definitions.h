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

#if !defined(ARCADIA_ADL_DEFINITIONS_H_INCLUDED)
#define ARCADIA_ADL_DEFINITIONS_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

// @brief A set of definitions.
//
// @code
// class Arcadia.ADL.Definitions extends Arcadia.Object {
//
//   field definitions : Arcadia.Map;
//
//   constructor();
//
//   method getQualifiedName(name : Arcadia.String) : Arcadia.ADL.Definition
//
// };
// @endcode
Arcadia_declareObjectType(u8"Arcadia.ADL.Definitions", Arcadia_ADL_Definitions,
                          u8"Arcadia.Object");

struct Arcadia_ADL_Definitions {
  Arcadia_Object _parent;
  Arcadia_Map* definitions;
};

Arcadia_ADL_Definitions*
Arcadia_ADL_Definitions_create
  (
    Arcadia_Thread* thread
  ); 

#endif  // ARCADIA_ADL_DEFINITIONS_H_INCLUDED
