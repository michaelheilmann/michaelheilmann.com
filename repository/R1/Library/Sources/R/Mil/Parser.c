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

#include "R/Mil/Parser.h"

#include "R/Mil/Scanner.h"
#include "R/Mil/Ast.h"

struct R_Mil_Parser {
  R_Object _parent;
  // The index of the Byte in the input stream at which the current symbol starts.
  R_Mil_Scanner* scanner;
};

static void
R_Mil_Parser_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_Mil_Parser_destruct
  (
    R_Mil_Parser* self
  );

static void
R_Mil_Parser_visit
  (
    R_Mil_Parser* self
  );

static R_BooleanValue
is
  (
    R_Mil_Parser* self,
    R_Mil_TokenType type
  );

static void
next
  (
    R_Mil_Parser* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_Mil_Parser_constructImpl,
  .destruct = &R_Mil_Parser_destruct,
  .visit = &R_Mil_Parser_visit,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Mil.Parser", R_Mil_Parser, "R.Object", R_Object, &_typeOperations);

static void
R_Mil_Parser_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_Mil_Parser* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_Mil_Parser_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  _self->scanner = R_Mil_Scanner_create();
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_Mil_Parser_destruct
  (
    R_Mil_Parser* self
  )
{/*Intentionally empty.*/}

static void
R_Mil_Parser_visit
  (
    R_Mil_Parser* self
  )
{ R_Object_visit(self->scanner); }

static R_Mil_TokenType
getType
  (
    R_Mil_Parser* self
  )
{ return R_Mil_Scanner_getTokenType(self->scanner); }

static R_String*
getText
  (
    R_Mil_Parser* self
  )
{ return R_Mil_Scanner_getTokenText(self->scanner); }

static R_BooleanValue
is
  (
    R_Mil_Parser* self,
    R_Mil_TokenType type
  )
{ return type == getType(self); }

static void
next
  (
    R_Mil_Parser* self
  )
{
  R_Mil_Scanner_step(self->scanner);
  while (R_Mil_TokenType_WhiteSpaces == getType(self) || R_Mil_TokenType_SingleLineComment == getType(self) || R_Mil_TokenType_MultiLineComment == getType(self)) {
    R_Mil_Scanner_step(self->scanner);
  }
}

R_Mil_Parser*
R_Mil_Parser_create
  (
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  R_Mil_Parser* self = R_allocateObject(_R_Mil_Parser_getType(), 0, &argumentValues[0]);
  return self;
}

static R_Mil_OperandAst*
onOperand
  (
    R_Mil_Parser* self
  );

static R_Mil_ExpressionAst*
onExpression
  (
    R_Mil_Parser* self
  );

static void
onEndOfStatement
  (
    R_Mil_Parser* self
  );

static R_Mil_StatementAst*
onStatement
  (
    R_Mil_Parser* self
  );

static R_String*
onParameter
  (
    R_Mil_Parser* self
  );

static R_List*
onParameters
  (
    R_Mil_Parser* self
  );

static R_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_ClassDefinitionAst*
onClassDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    R_Mil_Parser* self
  );

static R_Mil_ModuleAst*
onModule
  (
    R_Mil_Parser* self
  );

/// operand
///   booleanLiteralOperand
///   numberLiteralOperand
///   stringLiteralOperand
///   variableOperand
static R_Mil_OperandAst*
onOperand
  (
    R_Mil_Parser* self
  )
{
  switch (getType(self)) {
    case R_Mil_TokenType_BooleanLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_BooleanLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case R_Mil_TokenType_IntegerLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_IntegerLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case R_Mil_TokenType_RealLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_RealLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case R_Mil_TokenType_StringLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_StringLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case R_Mil_TokenType_VoidLiteral: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_VoidLiteralOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    case R_Mil_TokenType_Name: {
      R_Mil_OperandAst* operandAst = (R_Mil_OperandAst*)R_Mil_VariableOperandAst_create(getText(self));
      next(self);
      return operandAst;
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  };
}

static R_Mil_InvokeExpressionAst*
onInvokeExpression
  (
    R_Mil_Parser* self
  )
{
  next(self);
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  R_Mil_VariableOperandAst* calleeAst = R_Mil_VariableOperandAst_create(getText(self));
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (!is(self, R_Mil_TokenType_LeftParenthesis)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  if (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  R_List* operands = R_List_create();
  if (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightParenthesis)) {
    R_Mil_OperandAst* operand = onOperand(self);
    R_List_appendObjectReferenceValue(operands, (R_ObjectReferenceValue)operand);
    while (is(self, R_Mil_TokenType_Comma) || is(self, R_Mil_TokenType_LineTerminator)) {
      if (is(self, R_Mil_TokenType_LineTerminator)) {
        continue;
      }
      next(self);
      operand = onOperand(self);
      R_List_appendObjectReferenceValue(operands, (R_ObjectReferenceValue)operand);
    }
  }
  if (!is(self, R_Mil_TokenType_RightParenthesis)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  R_Mil_InvokeExpressionAst* invokeExpressionAst = R_Mil_InvokeExpressionAst_create(calleeAst, operands);
  return invokeExpressionAst;
}

// expression :
//   unaryExpression
//   binaryExpression
//   invokeExpression
// 
// invokeExpression :
//  'invoke' variableOperand '(' ( operand (',' operand)* )? ')'
// 
// binaryExpression :
//   'add' <op1>, <op2>
//   'and' <op1>, <op2>
//   'concatenate' <op1>, <op2>
//   'divide' <op1>, <op2>
//   'multiply' <op1>, <op2>
//   'or' <op1>, <op2>
//   'subtract' <op1>, <op2>
//   
// unaryExpression:
//   <op1>
//   'negate' <op1>
//   'not' <op1>
static R_Mil_ExpressionAst*
onExpression
  (
    R_Mil_Parser* self
  )
{
  switch (getType(self)) {
    // constantExpression
    case R_Mil_TokenType_BooleanLiteral:
    case R_Mil_TokenType_IntegerLiteral:
    case R_Mil_TokenType_RealLiteral:
    case R_Mil_TokenType_StringLiteral:
    case R_Mil_TokenType_VoidLiteral: 
    case R_Mil_TokenType_Name: {
      R_Mil_OperandAst* operand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_LoadExpressionAst_create(operand);
    } break;
    // binaryExpression
    case R_Mil_TokenType_Add: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Add, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_And: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_And, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Concatenate: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Concatenate, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Divide: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Divide, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Multiply: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Multiply, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Or: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Or, firstOperand, secondOperand);
    } break;
    case R_Mil_TokenType_Subtract: {
      next(self);
      R_Mil_OperandAst* firstOperand = onOperand(self);
      if (!is(self, R_Mil_TokenType_Comma)) {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      }
      next(self);
      R_Mil_OperandAst* secondOperand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_BinaryExpressionAst_create(R_Mil_BinaryExpressionAstType_Subtract, firstOperand, secondOperand);
    } break;
    // unaryExpression
    case R_Mil_TokenType_Negate: {
      next(self);
      R_Mil_OperandAst* operand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_UnaryExpressionAst_create(R_Mil_UnaryExpressionAstType_Negate, operand);
    } break;
    case R_Mil_TokenType_Not: {
      next(self);
      R_Mil_OperandAst* operand = onOperand(self);
      return (R_Mil_ExpressionAst*)R_Mil_UnaryExpressionAst_create(R_Mil_UnaryExpressionAstType_Not, operand);
    } break;
    case R_Mil_TokenType_Invoke: {
      return (R_Mil_ExpressionAst*)onInvokeExpression(self);
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  }
}

static void
onEndOfStatement
  (
    R_Mil_Parser* self
  )
{
  if (is(self, R_Mil_TokenType_EndOfInput)) {
    return;
  }
  if (!is(self, R_Mil_TokenType_RightCurlyBracket) && !is(self, R_Mil_TokenType_LineTerminator)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
}

/// statement : expressionStatement endOfStatement
///           | labelStatement endOfStatement?
///           | returnStatement endOfStatement
///           | emptyStatement endOfStatement
/// expressionStatement: name '=' expression
/// labelStatement: name ':'
/// returnStatement : 'return' operand?
static R_Mil_StatementAst*
onStatement
  (
    R_Mil_Parser* self
  )
{
  // skip "empty statement" 
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  // "return statement"
  if (is(self, R_Mil_TokenType_Return)) {
    next(self);
    R_Mil_OperandAst* operandAst = NULL;
    if (is(self, R_Mil_TokenType_BooleanLiteral) || is(self, R_Mil_TokenType_IntegerLiteral) || is(self, R_Mil_TokenType_RealLiteral) || is(self, R_Mil_TokenType_StringLiteral) || is(self, R_Mil_TokenType_Name)) {
      operandAst = onOperand(self);
    }
    onEndOfStatement(self);
    R_Mil_ReturnStatementAst* statementAst = R_Mil_ReturnStatementAst_create(operandAst);
    return (R_Mil_StatementAst*)statementAst;
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_Mil_StatementAst* statementAst = NULL;
  R_String* nameString = getText(self);
  next(self);
  switch (getType(self)) {
    case R_Mil_TokenType_EqualsSign: {
      next(self);
      R_Mil_ExpressionAst* expressionAst = onExpression(self);
      statementAst = (R_Mil_StatementAst*)R_Mil_ExpressionStatementAst_create(nameString, expressionAst);
      onEndOfStatement(self);
    } break;
    case R_Mil_TokenType_Colon: {
      next(self);
      statementAst = (R_Mil_StatementAst*)R_Mil_LabelStatementAst_create(nameString);
      // statement terminator injection
      if (is(self, R_Mil_TokenType_EndOfInput) || is(self, R_Mil_TokenType_LineTerminator) || is(self, R_Mil_TokenType_RightCurlyBracket)) {
        if (is(self, R_Mil_TokenType_LineTerminator) || is(self, R_Mil_TokenType_RightCurlyBracket)) {
          next(self);
        }
      }
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  return statementAst;
}

static R_String*
onParameter
  (
    R_Mil_Parser* self
  ) 
{
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_String* parameter = getText(self);
  next(self);
  return parameter;
}

// parameters : '(' (name (',' name)*)? ')'
static R_List*
onParameters
  (
    R_Mil_Parser* self
  )
{ 
  R_List* parameters = R_List_create();
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LeftParenthesis)) {
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    R_String* parameter = NULL;
    if (is(self, R_Mil_TokenType_Name)) {
      parameter = onParameter(self);
      R_List_appendObjectReferenceValue(parameters, (R_ObjectReferenceValue)parameter);
      while (is(self, R_Mil_TokenType_LineTerminator)) {
        next(self);
      }
      while (is(self, R_Mil_TokenType_Comma)) {
        next(self);
        while (is(self, R_Mil_TokenType_LineTerminator)) {
          next(self);
        }
        parameter = onParameter(self);
        R_List_appendObjectReferenceValue(parameters, (R_ObjectReferenceValue)parameter);
        while (is(self, R_Mil_TokenType_LineTerminator)) {
          next(self);
        }
      }
    }
    if (!is(self, R_Mil_TokenType_RightParenthesis)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    next(self);
  }
  return parameters;
}

// constructorDefinition : 'constructor' ('native' string)? constructorParameters? constructorBody?
// constructorParameters : parameters
// constructorBody : '{' statements '}
static R_Mil_ConstructorDefinitionAst*
onConstructorDefinition
  (
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Constructor)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  R_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    nativeName = getText(self);
    next(self);
  }
  R_List* constructorParameters = onParameters(self);
  R_List* constructorBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    constructorBody = R_List_create();
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(self);
      R_List_appendObjectReferenceValue(constructorBody, (R_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    next(self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LeftParenthesis)) {
    if (!is(self, R_Mil_TokenType_RightParenthesis)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
  }
  R_Mil_ConstructorDefinitionAst* constructorDefinitionAst = R_Mil_ConstructorDefinitionAst_create(nativeName, constructorParameters, constructorBody);
  return constructorDefinitionAst;
}

// methodDefinition : 'method' ('native' string)? methodName methodParameters? methodBody?
// methodParameters : parameters
// methodBody : '{' statements '}'
static R_Mil_MethodDefinitionAst*
onMethodDefinition
  (
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Method)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  R_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    nativeName = getText(self);
    next(self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_String* methodName = getText(self);
  next(self);
  R_List* methodParameters = onParameters(self);
  R_List* methodBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    methodBody = R_List_create();
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(self);
      R_List_appendObjectReferenceValue(methodBody, (R_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    next(self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  R_Mil_MethodDefinitionAst* methodDefinitionAst = R_Mil_MethodDefinitionAst_create(nativeName, methodName, methodParameters, methodBody);
  return methodDefinitionAst;
}

// variableDefinition : 'variable' variableName
static R_Mil_VariableDefinitionAst*
onVariableDefinition
  (
    R_Mil_Parser* self
  )
{
  if (R_Mil_TokenType_Variable != getType(self)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  if (R_Mil_TokenType_Name != getType(self)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_Mil_VariableDefinitionAst* variableDefinitionAst = R_Mil_VariableDefinitionAst_create(getText(self));
  return variableDefinitionAst;
}

// classBodyDefinition : classMemberDefinition
// classMemberDefinition : constructorDefinition | methodDefinition | variableDefinition
static R_Mil_ClassMemberDefinitionAst*
onClassMemberDefinition
  (
    R_Mil_Parser* self
  )
{ 
  switch (getType(self)) {
    case R_Mil_TokenType_Constructor: {
      return (R_Mil_ClassMemberDefinitionAst*)onConstructorDefinition(self);
    } break;
    case R_Mil_TokenType_Method: {
      return (R_Mil_ClassMemberDefinitionAst*)onMethodDefinition(self);
    } break;
    case R_Mil_TokenType_Variable: {
      return (R_Mil_ClassMemberDefinitionAst*)onVariableDefinition(self);
    } break;
    default: {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    } break;
  };
}

// classDefinition : 'class' name ('extends' name) classBody
// classBody : '{' classBodyDefinition* '}'
static R_Mil_ClassDefinitionAst*
onClassDefinition
  (
    R_Mil_Parser* self
  )
{
  if (!is(self, R_Mil_TokenType_Class)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_String* className = getText(self);
  next(self);
  R_String* extendedClassName = NULL;
  if (is(self, R_Mil_TokenType_Extends)) {
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    if (!is(self, R_Mil_TokenType_Name)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    extendedClassName = getText(self);
    next(self);
  }
  R_List* classBody = NULL;
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    classBody = R_List_create();  
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_ClassMemberDefinitionAst* classMemberDefinitionAst = onClassMemberDefinition(self);
      R_List_appendObjectReferenceValue(classBody, (R_ObjectReferenceValue)classMemberDefinitionAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    next(self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  R_Mil_ClassDefinitionAst* classDefinitionAst = R_Mil_ClassDefinitionAst_create(className, extendedClassName, classBody);
  return classDefinitionAst;
}

// procedureDefinition : 'procedure' 'entry'? ('native' string)? name procedureParameters? procedureBody?
// procedureParameters : parameters
// procedureBody : '{' statements '}'
static R_Mil_ProcedureDefinitionAst*
onProcedureDefinition
  (
    R_Mil_Parser* self
  )
{
  R_BooleanValue entry = R_BooleanValue_False;
  if (!is(self, R_Mil_TokenType_Procedure)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  if (is(self, R_Mil_TokenType_Entry)) {
    next(self);
    entry = R_BooleanValue_True;
  }
  R_String* nativeName = NULL;
  if (is(self, R_Mil_TokenType_Native)) {
    next(self);
    if (!is(self, R_Mil_TokenType_StringLiteral)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    nativeName = getText(self);
    next(self);
  }
  if (!is(self, R_Mil_TokenType_Name)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  R_String* procedureName = getText(self);
  next(self);
  R_List* procedureParameters = onParameters(self);
  R_List* procedureBody = NULL;
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  if (is(self, R_Mil_TokenType_LeftCurlyBracket)) {
    procedureBody = R_List_create();
    next(self);
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    while (!is(self, R_Mil_TokenType_EndOfInput) && !is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_Mil_StatementAst* statementAst = onStatement(self);
      R_List_appendObjectReferenceValue(procedureBody, (R_ObjectReferenceValue)statementAst);
    }
    if (!is(self, R_Mil_TokenType_RightCurlyBracket)) {
      R_setStatus(R_Status_SyntacticalError);
      R_jump();
    }
    next(self);
  }
  while (is(self, R_Mil_TokenType_LineTerminator)) {
    next(self);
  }
  R_Mil_ProcedureDefinitionAst* procedureDefinitionAst = R_Mil_ProcedureDefinitionAst_create(entry, nativeName, procedureName, procedureParameters, procedureBody);
  return procedureDefinitionAst;
}

/// module : (classDefinition|proceduredefinition)*
static R_Mil_ModuleAst*
onModule
  (
    R_Mil_Parser* self
  )
{
  R_Mil_ModuleAst* moduleAst = R_Mil_ModuleAst_create();
  if (!is(self, R_Mil_TokenType_StartOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  next(self);
  while (!is(self, R_Mil_TokenType_EndOfInput)) {
    while (is(self, R_Mil_TokenType_LineTerminator)) {
      next(self);
    }
    R_Mil_DefinitionAst* definitionAst = NULL;
    switch (getType(self)) {
      case R_Mil_TokenType_Class: {
        definitionAst = (R_Mil_DefinitionAst*)onClassDefinition(self);
        R_Mil_ModuleAst_appendDefinition(moduleAst, definitionAst);
      } break;
      case R_Mil_TokenType_Procedure: {
        definitionAst = (R_Mil_DefinitionAst*)onProcedureDefinition(self);
        R_Mil_ModuleAst_appendDefinition(moduleAst, definitionAst);
      } break;
      default: {
        R_setStatus(R_Status_SyntacticalError);
        R_jump();
      } break;
    };
  }
  if (!is(self, R_Mil_TokenType_EndOfInput)) {
    R_setStatus(R_Status_SyntacticalError);
    R_jump();
  }
  return moduleAst;
}

R_Mil_ModuleAst*
R_Mil_Parser_run
  (
    R_Mil_Parser* self
  )
{ 
  R_Mil_ModuleAst* moduleAst = onModule(self);
  return moduleAst;
}

void
R_Mil_Parser_setInput
  (
    R_Mil_Parser* self,
    R_Utf8Reader* input
  )
{
  R_Mil_Scanner_setInput(self->scanner, input);
}
