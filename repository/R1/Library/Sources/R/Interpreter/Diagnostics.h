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

// Last modified: 2024-12-07

#if !defined(R_INTERPRETER_DIAGNOSTICS_H_INCLUDED)
#define R_INTERPRETER_DIAGNOSTICS_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"
typedef struct R_Interpreter_Code R_Interpreter_Code;
typedef struct R_Interpreter_Procedure R_Interpreter_Procedure;

/// The thread state consists
/// - registers (at least 256)
/// - parameter passing registers (at least 32)
/// - stack of register frames which allow for pushing and restoring ranges of registers
Rex_declareObjectType("R.Interpreter.Diagnostics", R_Interpreter_Diagnostics, "R.Object");

// @private
// @brief Create a diagnostics object.
// @return A pointer to the diagnostics object.
// @error #R_Status_AllocationFailed an allocation failed
R_Interpreter_Diagnostics*
R_Interpreter_Diagnostics_create
  (
  );

#endif // R_INTERPRETER_DIAGNOSTICS_H_INCLUDED
