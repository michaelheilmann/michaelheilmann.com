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

#if !defined(ARCADIA_MIL_FRONTEND_ASTS_METHODDEFINITIONAST_H_INCLUDED)
#define ARCADIA_MIL_FRONTEND_ASTS_METHODDEFINITIONAST_H_INCLUDED

#include "Arcadia/Mil/Frontend/Asts/Ast.h"

Arcadia_declareObjectType(u8"Arcadia.Mil.MethodDefinitionAst", Arcadia_Mil_MethodDefinitionAst, u8"Arcadia.Mil.Ast");

struct Arcadia_Mil_MethodDefinitionAst {
  Arcadia_Mil_Ast _parent;
  Arcadia_String* nativeName;
  Arcadia_String* methodName;
  Arcadia_List* methodParameters;
  Arcadia_List* methodBody;
};

Arcadia_Mil_MethodDefinitionAst*
Arcadia_Mil_MethodDefinitionAst_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* nativeName,
    Arcadia_String* methodName,
    Arcadia_List* methodParameters,
    Arcadia_List* methodBody
  );

#endif // ARCADIA_MIL_FRONTEND_ASTS_METHODDEFINITIONAST_H_INCLUDED
