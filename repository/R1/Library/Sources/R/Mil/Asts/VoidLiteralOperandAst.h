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

// Last modified: 2025-01-01

#if !defined(ARCADIA_MIL_ASTS_VOIDLITERALOPERANDAST_H_INCLUDED)
#define ARCADIA_MIL_ASTS_VOIDLITERALOPERANDAST_H_INCLUDED

#include "R/Mil/Asts/OperandAst.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class Arcadia.Mil.VoidLiteralOperandAst extends Arcadia.Mil.OperandAst
/// @endcode
Rex_declareObjectType(u8"Arcadia.Mil.VoidLiteralOperandAst", Arcadia_Mil_VoidLiteralOperandAst, u8"Arcadia.Mil.OperandAst");

struct Arcadia_Mil_VoidLiteralOperandAst {
  Arcadia_Mil_OperandAst parent;
  Arcadia_String* value;
};

Arcadia_Mil_VoidLiteralOperandAst*
Arcadia_Mil_VoidLiteralOperandAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // ARCADIA_MIL_ASTS_VOIDLITERALOPERANDAST_H_INCLUDED
