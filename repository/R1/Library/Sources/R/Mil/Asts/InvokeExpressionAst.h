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

#if !defined(R_MIL_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED)
#define R_MIL_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED

#include "R/Mil/Asts/ExpressionAst.h"
typedef struct R_Mil_VariableOperandAst R_Mil_VariableOperandAst;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @code
/// class R.Mil.InvokeExpressionAst extends R.Mil.ExpressionAst
/// @endcode
/// Represents an unary epxression like
/// @code
/// invoke variableOperand '(' (operand (',' operand)*)? ')'
/// @endcode
Rex_declareObjectType(u8"R.Mil.InvokeExpressionAst", R_Mil_InvokeExpressionAst, u8"R.Mil.ExpressionAst");

struct R_Mil_InvokeExpressionAst {
  R_Mil_ExpressionAst parent;
  R_Mil_VariableOperandAst* callee;
  R_List* operands;
};

R_Mil_InvokeExpressionAst*
R_Mil_InvokeExpressionAst_create
  (
    Arcadia_Process* process,
    R_Mil_VariableOperandAst* callee,
    R_List* operands
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_MIL_ASTS_INVOKEEXPRESSIONAST_H_INCLUDED