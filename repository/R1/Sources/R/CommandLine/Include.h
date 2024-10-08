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

// Last modified: 2024-09-28

#if !defined(R_COMMANDLINE_INCLUDE_H_INCLUDED)
#define R_COMMANDLINE_INCLUDE_H_INCLUDED

#include "R/Boolean.h"
#include "R/Utf8Reader.h"
#include "R/String.h"

// A command-line argument is of the form
// @code
// <argument> : '--'<name>('='<value>)?
// <name> : /* one or more symbols not equal to '=' */
// <value> : /* zero more symbols */
// @endcode
// @code{<name>} is returned in @code{*key}.
// If a @code{<value>} is specified, it is returned in @code{*value}.
// Otherwise *value is assigned NULL.
R_BooleanValue
R_CommandLine_parseArgument
  (
    R_Utf8Reader* reader,
    R_String** key,
    R_String** value
  );

void
R_CommandLine_raiseRequiredArgumentMissingError
  (
    R_String* key
  );

void
R_CommandLine_raiseUnknownArgumentError
  (
    R_String* key,
    R_String* value
  );

void
R_CommandLine_raiseNoValueError
  (
    R_String* key
  );

void
R_CommandLine_raiseValueInvalidError
  (
    R_String* key,
    R_String* value
  );

#endif // R_COMMANDLINE_INCLUDE_H_INCLUDED
