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

// Last modified: 2024-09-22

#if !defined(R_MIL_PARSER_H_INCLUDED)
#define R_MIL_PARSER_H_INCLUDED

#include "R.h"

typedef enum R_Mil_AstType {
  // A program.
  R_Mil_AstType_Program,
  // A statement.
  R_Mil_AstType_Statement,
} R_Mil_AstType;

/// @code
/// class Cil.Parser
/// @endcode
Rex_declareObjectType("Cil.Parser", R_Mil_Parser, "R.Object");

void
R_Mil_Parser_construct
  (
    R_Mil_Parser* self
  );

/// @brief Create a CIL parser.
/// @return A pointer to this CIL parser.
R_Mil_Parser*
R_Mil_Parser_create
  (
  );

/// @brief Translate the token stream into an AST.
/// @param self A pointer to this CIL parser. 
void
R_Mil_Parser_run
  (
    R_Mil_Parser* self
  );

/// @brief Set the input.
/// @param self A pointer to this CIL parser.
/// @param input A pointer to the UTF8 reader.
void
R_Mil_Parser_setInput
  (
    R_Mil_Parser* self,
    R_Utf8Reader* input
  );

#endif // R_MIL_PARSER_H_INCLUDED
