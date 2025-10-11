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

<<<<<<<< HEAD:repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/DefinitionStatementNode.h
#if !defined(ARCADIA_MIL_AST_DEFINITIONSTATEMENTNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_DEFINITIONSTATEMENTNODE_H_INCLUDED
========
#if !defined(ARCADIA_MIL_AST_LABELINSTRUCTIONNODE_H_INCLUDED)
#define ARCADIA_MIL_AST_LABELINSTRUCTIONNODE_H_INCLUDED
>>>>>>>> b196ceae (Update Week 4 August 2025):repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/Instructions/LabelInstructionNode.h

#include "Arcadia/MIL/AST/InstructionNode.h"

/// @code
<<<<<<<< HEAD:repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/DefinitionStatementNode.h
/// class Arcadia.MIL.AST.DefinitionStatementNode extends Arcadia.MIL.AST.StatementNode {
========
/// class Arcadia.MIL.AST.LabelInstructionNode extends Arcadia.MIL.AST.InstructionNode {
>>>>>>>> b196ceae (Update Week 4 August 2025):repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/Instructions/LabelInstructionNode.h
///   ...
/// }
/// @endcode
/// represents
/// @code
/// definitionStatement : labelDefinitionStatement
///                     | variableDefinitionStatement
/// @endcode
<<<<<<<< HEAD:repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/DefinitionStatementNode.h
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.DefinitionStatementNode", Arcadia_MIL_AST_DefinitionStatementNode,
                          u8"Arcadia.MIL.AST.StatementNode");

struct Arcadia_MIL_AST_DefinitionStatementNode {
  Arcadia_MIL_AST_StatementNode _parent;
};

#endif // ARCADIA_MIL_AST_DEFINITIONSTATEMENTNODE_H_INCLUDED
========
/// 
Arcadia_declareObjectType(u8"Arcadia.MIL.AST.LabelInstructionNode", Arcadia_MIL_AST_LabelInstructionNode,
                          u8"Arcadia.MIL.AST.InstructionNode");

struct Arcadia_MIL_AST_LabelInstructionNode {
  Arcadia_MIL_AST_InstructionNode parent;
  Arcadia_String* labelName;
};

/// @brief Create a MIL label instruction AST node.
/// @return A pointer to this MIL label instruction AST node.
Arcadia_MIL_AST_LabelInstructionNode*
Arcadia_MIL_AST_LabelInstructionNode_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* labelName
  );

#endif // ARCADIA_MIL_AST_LABELINSTRUCTIONNODE_H_INCLUDED
>>>>>>>> b196ceae (Update Week 4 August 2025):repository/MIL.AST/Library/Sources/Arcadia/MIL/AST/Instructions/LabelInstructionNode.h
