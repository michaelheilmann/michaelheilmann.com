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

#if !defined(ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED)
#define ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Visuals/Implementation/Configure.h"

#if Arcadia_Visuals_Implementation_Configuration_Direct3D12_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/Direct3D12/Backend.h"
#endif

#if Arcadia_Visuals_Implementation_Configuration_OpenGL4_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/OpenGL4/Backend.h"
#endif

#if Arcadia_Visuals_Implementation_Configuration_Vulkan_Backend_Enabled
  #include "Arcadia/Visuals/Implementation/Vulkan/Backend.h"
#endif

#if Arcadia_Configuration_OperatingSystem_Windows == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Implementation/OpenGL4/WGL/System.h"
  #include "Arcadia/Visuals/Implementation/Windows/TextureFont.h"
#elif Arcadia_Configuration_OperatingSystem_Linux == Arcadia_Configuration_OperatingSystem
  #include "Arcadia/Visuals/Implementation/OpenGL4/GLX/System.h"
#else
  #error("environment not (yet) supported")
#endif

#endif // ARCADIA_VISUALS_IMPLEMENTATION_INCLUDE_H_INCLUDED
