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

#if !defined(VISUALS_IMAGEMAGICK_H_INCLUDED)
#define VISUALS_IMAGEMAGICK_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Module/Visuals/PixelBuffer.h"

void
_Visuals_Linux_writeBmpToByteBuffer
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_PixelBuffer* pixelBuffer,
    Arcadia_ByteBuffer* byteBuffer
  );

#endif // VISUALS_IMAGEMAGICK_H_INCLUDED
