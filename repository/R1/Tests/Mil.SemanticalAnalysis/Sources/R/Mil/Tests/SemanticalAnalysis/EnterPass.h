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

// Last modified: 2024-10-18

#if !defined(R_MIL_ENTER_H_INCLUDED)
#define R_MIL_ENTER_H_INCLUDED

#include "R/Include.h"
#include "R/Mil/Tests/SemanticalAnalysis/Pass.h"
#include "R/Mil/Include.h"
typedef struct Arcadia_Mil_CallableContext Arcadia_Mil_CallableContext;

void
Arcadia_Mil_EnterPass_onModule
  (
    Arcadia_Process* process,
    R_Interpreter_ProcessState* interpreterProcess,
    Arcadia_Map* symbolTable,
    Arcadia_Map* foreignProcedures,
    Arcadia_Mil_ModuleAst* moduleAst
  );

/// The first pass (enter pass) of the compiler.
/// Guarantees:
/// - no class-class, prodecure-procedure, class-procedure name collision
/// - no label name collision
Rex_declareObjectType(u8"Arcadia.Mil.EnterPass", Arcadia_Mil_EnterPass, u8"Arcadia.Mil.Pass");

struct Arcadia_Mil_EnterPass {
  Arcadia_Mil_Pass _parent;
};

Arcadia_Mil_EnterPass*
Arcadia_Mil_EnterPass_create
  (
    Arcadia_Process* process
  );

#endif // R_MIL_ENTER_H_INCLUDED
