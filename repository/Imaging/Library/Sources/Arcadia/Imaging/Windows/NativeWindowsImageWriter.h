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

#if !defined(ARCADIA_VISUALS_NATIVEWINDOWSIMAGEWRITER_H_INCLUDED)
#define ARCADIA_VISUALS_NATIVEWINDOWSIMAGEWRITER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/ImageWriter.h"
#include "Arcadia/Imaging/PixelBuffer.h"

// WIC header
#define COBJMACROS (1)
#include <wincodec.h>

Arcadia_declareObjectType(u8"NativeWindowsImageWriter", NativeWindowsImageWriter, u8"ImageWriter");

struct NativeWindowsImageWriter {
  ImageWriter _parent;
  Arcadia_ImmutableList* supportedTypes;

  IWICImagingFactory* piFactory;
  HGLOBAL hMemory;
  IStream* piMemoryStream; // NULL if there is no memory stream
  IWICStream* piStream;
  IWICBitmapEncoder* piEncoder;

  IWICBitmapFrameEncode* piBitmapFrame;
  IPropertyBag2* pPropertyBag;
};

NativeWindowsImageWriter*
NativeWindowsImageWriter_create
  (
    Arcadia_Thread* thread
  );

#endif // ARCADIA_VISUALS_NATIVEWINDOWSIMAGEWRITER_H_INCLUDED
