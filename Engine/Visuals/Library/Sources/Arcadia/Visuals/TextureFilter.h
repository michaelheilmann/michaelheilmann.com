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

#if !defined(ARCADIA_VISUALS_TEXTUREFILTER_H_INCLUDED)
#define ARCADIA_VISUALS_TEXTUREFILTER_H_INCLUDED

#if !defined(ARCADIA_VISUALS_PRIVATE) || 1 != ARCADIA_VISUALS_PRIVATE
  #error("do not include directly, include `Arcadia/Visuals/Include.h` instead")
#endif
#include "Arcadia/Ring2/Include.h"

// https://michaelheilmann.com/Arcadia/Visuals/#Arcadia_Visuals_TextureFilter
Arcadia_declareEnumerationType(u8"Arcadia.Visuals.TextureFilter", Arcadia_Visuals_TextureFilter);

enum Arcadia_Visuals_TextureFilter {

  Arcadia_Visuals_TextureFilter_Nearest,

  Arcadia_Visuals_TextureFilter_Linear,

};

#endif // ARCADIA_VISUALS_TEXTUREFILTER_H_INCLUDED
