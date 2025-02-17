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

// Last modified: 2024-09-22

#if !defined(R_MIL_SCANNER_H_INCLUDED)
#define R_MIL_SCANNER_H_INCLUDED

#include "R/Mil/TokenType.h"

/// @code
/// class Arcadia.MilScanner
/// @endcode
Rex_declareObjectType(u8"Arcadia.Mil.Scanner", Arcadia_Mil_Scanner, u8"Arcadia.Object");

/// @brief Create a MIL scanner.
/// @return A pointer to this MIL scanner.
Arcadia_Mil_Scanner*
Arcadia_Mil_Scanner_create
  (
    Arcadia_Process* process
  );

/// @brief Get the text of the token.
/// @param self A pointer to this MIL scanner.
/// @return The text of the token.
Arcadia_String*
Arcadia_Mil_Scanner_getTokenText
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scanner* self
  );

/// @brief Get the type of the token.
/// @param self A pointer to this MIL scanner.
/// @return The type of the token.
Arcadia_Natural32Value
Arcadia_Mil_Scanner_getTokenType
  (
    Arcadia_Mil_Scanner* self
  );

/// @brief Move to next token.
/// @param self A pointer to this MIL scanner.
void
Arcadia_Mil_Scanner_step
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scanner* self
  );

/// @brief Set the input.
/// @param self A pointer to this MIL scanner.
/// @param input A pointer to the UTF8 reader.
void
Arcadia_Mil_Scanner_setInput
  (
    Arcadia_Process* process,
    Arcadia_Mil_Scanner* self,
    Arcadia_Utf8Reader* input
  );

#endif // R_MIL_SCANNER_H_INCLUDED
