// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-26

#if !defined(AUDIALS_INCLUDE_H_INCLUDED)
#define AUDIALS_INCLUDE_H_INCLUDED

#include "Audials/Configure.h"
#include "R.h"

void
Audials_startup
  (
  );

void
Audials_shutdown
  (
  );

// A sound can be "lost" if the audio system shuts down.
// It will raise a "R_Status_Uninitialized" error.
Rex_declareObjectType("Audials.Sound", Audials_Sound, "R_Object");

/// @brief Create a sound.
/// @return A pointer to the sound.
/// @error R_Status_Uninitialized the audio system is uninitialized.
Audials_Sound*
Audials_Sound_create
  (
  );

/// @brief Play the sound.
/// @param self A pointer to the sound.
/// @error R_Status_Uninitialized the audio system is uninitialized.
void
Audials_Sound_play
  (
    Audials_Sound* self
  );

#endif // AUDIALS_INCLUDE_H_INCLUDED
