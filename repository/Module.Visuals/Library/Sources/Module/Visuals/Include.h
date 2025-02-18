// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-16

#if !defined(MODULE_VISUALS_INCLUDE_H_INCLUDED)
#define MODULE_VISUALS_INCLUDE_H_INCLUDED

#include "R/Include.h"

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Module/Visuals/Font.h"
  #include "Module/Visuals/NativeWindowsImageWriter.h"
  #include "Module/Visuals/NativeWindowsIcon.h"
  #include "Module/Visuals/NativeWindowsWindow.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Module/Visuals/NativeLinuxImageWriter.h"
#else
  #error("environment not (yet) supported")
#endif
#include "Module/Visuals/ImageWriterParameters.h"
#include "Module/Visuals/PixelBuffer.h"


#endif // MODULE_VISUALS_INCLUDE_H_INCLUDED
