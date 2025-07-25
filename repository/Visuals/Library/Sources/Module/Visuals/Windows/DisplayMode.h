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

#if !defined (ARCADIA_VISUALS_WINDOWS_DISPLAYMODE_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOWS_DISPLAYMODE_H_INCLUDED

#include "Module/Visuals/DisplayMode.h"
typedef struct Arcadia_Visuals_Windows_DisplayDevice Arcadia_Visuals_Windows_DisplayDevice;

Arcadia_declareObjectType(u8"Arcadia.Visuals.Windows.DisplayMode", Arcadia_Visuals_Windows_DisplayMode, u8"Arcadia.Visuals.DisplayMode");

struct Arcadia_Visuals_Windows_DisplayMode {
  Arcadia_Visuals_DisplayMode _parent;
  Arcadia_Visuals_Windows_DisplayDevice* device;
  Arcadia_Integer32Value horizontalResolution;
  Arcadia_Integer32Value verticalResolution;
  Arcadia_Integer32Value colorDepth;
  Arcadia_Integer32Value frequency;
};

Arcadia_Visuals_Windows_DisplayMode*
Arcadia_Visuals_Windows_DisplayMode_create
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Windows_DisplayDevice* device,
    Arcadia_Integer32Value horizontalResolution,
    Arcadia_Integer32Value verticalResolution,
    Arcadia_Integer32Value colorDepth,
    Arcadia_Integer32Value frequency
  );

#endif // ARCADIA_VISUALS_WINDOWS_DISPLAYMODE_H_INCLUDED
