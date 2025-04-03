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

#if !defined(ARCADIA_MIL_KEYWORDS_H_INCLUDED)
#define ARCADIA_MIL_KEYWORDS_H_INCLUDED

#include "R/Mil/TokenType.h"

/// @code
/// class Arcadia.MilKeywords
/// @endcode
Rex_declareObjectType(u8"Arcadia.MilKeywords", Arcadia_Mil_Keywords, u8"Arcadia.Object");

/// @brief Create a MIL keywords object.
/// @return A pointer to this CIL keywords object.
Arcadia_Mil_Keywords*
Arcadia_Mil_Keywords_create
  (
    Arcadia_Thread* thread
  );

/// @brief Add a MIL keyword.
/// @param string The string of the keyword.
/// @param type The type of the keyword
/// @error Arcadia_Status_Exists The keyword already was added.
void
Arcadia_Mil_Keywords_add
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value type
  );

/// @brief Get the token type.
/// @param self A pointer to this MIL keyword scanner.
/// @param string The string to be tested for being a keyword.
/// @param tokenType A pointer to a variable that is assigned the keyword's token type if the string is a keyword. Not modified otherwise.
/// @return Arcadia_BooleanValue_True if the specified string was a keyword. #Arcadia_BooleanValue_False otherwise.
Arcadia_BooleanValue
Arcadia_Mil_Keywords_scan
  (
    Arcadia_Thread* thread,
    Arcadia_Mil_Keywords* self,
    Arcadia_String* string,
    Arcadia_Natural32Value* tokenType
  );

#endif // ARCADIA_MIL_KEYWORDS_H_INCLUDED

