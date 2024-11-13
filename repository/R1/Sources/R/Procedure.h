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

#if !defined(R_PROCEDURE_H_INCLUDED)
#define R_PROCEDURE_H_INCLUDED

#include "R/Object.h"
#include "R/Value.h"
#include "R/Machine/Code/Include.h"

Rex_declareObjectType("R.Procedure", R_Procedure, "R.Object");

struct R_Procedure {
  R_Object _parent;
  R_Machine_Code* code;
};

// Currently, there is no restriction in code for a procedure.
void
R_Procedure_construct
  (
    R_Procedure* self,
    R_Machine_Code* code
  );

R_Procedure*
R_Procedure_create
  (
    R_Machine_Code* code
  );

R_Machine_Code*
R_Procedure_getCode
  (
    R_Procedure* self
  );

#endif // R_PROCEDURE_H_INCLUDED