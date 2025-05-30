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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED

#include "Arcadia/Mil/Frontend/Asts/StatementAst.h"

/// @code
/// class Arcadia.Mil.VariableDefinitionStatement extends Arcadia.Mil.Statement
/// @endcode
/// Represents
/// @code
/// 'variable' VariableName
/// @endcode
Arcadia_declareObjectType(u8"Arcadia.Mil.VariableDefinitionStatementAst", Arcadia_Mil_VariableDefinitionStatementAst, u8"Arcadia.Mil.StatementAst");

struct Arcadia_Mil_VariableDefinitionStatementAst {
  Arcadia_Mil_StatementAst parent;
  Arcadia_String* variableName;
};

/// @brief Create a Mil variable definition statement AST.
/// @return A pointer to this Mil variable definition statement AST.
Arcadia_Mil_VariableDefinitionStatementAst*
Arcadia_Mil_VariableDefinitionStatementAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* variableName
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_VARIABLEDEFINITIONSTATEMENTAST_H_INCLUDED
