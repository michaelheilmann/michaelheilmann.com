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

#if !defined(ARCADIA_VISUALS_INCLUDE_H_INCLUDED)
#define ARCADIA_VISUALS_INCLUDE_H_INCLUDED

#include "Arcadia/Ring2/Include.h"

#include "Module/Visuals/Events/CanvasEvent.h"
#include "Module/Visuals/CullMode.h"
#include "Module/Visuals/DisplayDevice.h"
#include "Module/Visuals/DisplayMode.h"
#include "Module/Visuals/ImageWriterParameters.h"
#include "Module/Visuals/PixelBuffer.h"
#include "Module/Visuals/PixelFormat.h"
#include "Module/Visuals/TextureAddressMode.h"
#include "Module/Visuals/TextureFilter.h"
#include "Module/Visuals/VertexElementSemantics.h"
#include "Module/Visuals/VertexElementSyntax.h"
#include "Module/Visuals/WindingMode.h"
#include "Module/Visuals/LibPngImageWriter.h"

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Module/Visuals/Windows/Application.h"
  #include "Module/Visuals/Windows/TextureFont.h"
  #include "Module/Visuals/Windows/NativeWindowsImageWriter.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Module/Visuals/Linux/Application.h"
#else
  #error("environment not (yet) supported")
#endif

#endif // ARCADIA_VISUALS_INCLUDE_H_INCLUDED
