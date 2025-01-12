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

#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R/Mil/Include.h"

static void
expectAndNext
  (
    Arcadia_Process* process,
    R_Mil_Scanner* scanner,
    R_Mil_TokenType tokenType,
    Arcadia_Natural8Value const* tokenText,
    Arcadia_SizeValue tokenTextLength
  )
{
  if (tokenType != R_Mil_Scanner_getTokenType(scanner)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  if (!R_String_isEqualTo_pn(R_Mil_Scanner_getTokenText(process, scanner), tokenText, tokenTextLength)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_TestFailed);
    Arcadia_Process_jump(process);
  }
  R_Mil_Scanner_step(process, scanner);
}

static void
testScanner3
  (
    Arcadia_Process* process
  )
{
  static const char* input =
    //
    u8"multiply"
    u8"\n"
    u8"divide"
    u8"\n"
    u8"add"
    u8"\n"
    u8"subtract"
    u8"\n"
    //
    u8"negate"
    u8"\n"
    //
    u8"concatenate"
    u8"\n"
    //
    u8"not"
    u8"\n"
    u8"and"
    u8"\n"
    u8"or"
    u8"\n"
    //
    u8"class"
    u8"\n"
    u8"extends"
    u8"\n"
    u8"implements"
    u8"\n"
    u8"native"
    u8"\n"
    u8"procedure"
    u8"\n"
    u8"method"
    u8"\n"
    u8"constructor"
    u8"\n"
    u8"variable"
    u8"\n"
    ;
  R_Mil_Scanner* scanner = R_Mil_Scanner_create(process);
  R_Mil_Scanner_setInput(process, scanner, (R_Utf8Reader*)R_Utf8StringReader_create(process, R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, input, strlen(input)))));

  //
  expectAndNext(process, scanner, R_Mil_TokenType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_Multiply, u8"multiply", sizeof(u8"multiply") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Divide, u8"divide", sizeof(u8"divide") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Add, u8"add", sizeof(u8"add") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Subtract, u8"subtract", sizeof(u8"subtract") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_Negate, u8"negate", sizeof(u8"negate") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_Concatenate, u8"concatenate", sizeof(u8"concatenate") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_Not, u8"not", sizeof(u8"not") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_And, u8"and", sizeof(u8"and") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Or, u8"or", sizeof(u8"or") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_Class, u8"class", sizeof(u8"class") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Extends, u8"extends", sizeof(u8"extends") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Implements, u8"implements", sizeof(u8"implements") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Native, u8"native", sizeof(u8"native") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Procedure, u8"procedure", sizeof(u8"procedure") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Method, u8"method", sizeof(u8"method") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Constructor, u8"constructor", sizeof(u8"constructor") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Variable, u8"variable", sizeof(u8"variable") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  //
  expectAndNext(process, scanner, R_Mil_TokenType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner2
  (
    Arcadia_Process* process
  )
{
  static const char* input =
    u8"Name"
    u8"\n"
    u8"17"
    u8"\n"
    u8"17.23"
    u8"\n"
    u8"\"Hello, World!\n\""
    u8"\n"
    u8"="
    u8"\n"
    u8"//\n"
    u8"/**/"
    u8"\n"
    u8":"
    u8"\n"
    u8","
    u8"\n"
    ;
  R_Mil_Scanner* scanner = R_Mil_Scanner_create(process);
  R_Mil_Scanner_setInput(process, scanner, (R_Utf8Reader*)R_Utf8StringReader_create(process, R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, input, strlen(input)))));

  expectAndNext(process, scanner, R_Mil_TokenType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Name, u8"Name", sizeof(u8"Name") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_IntegerLiteral, u8"17", sizeof(u8"17") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_RealLiteral, u8"17.23", sizeof(u8"17.23") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_StringLiteral, u8"Hello, World!\n", sizeof(u8"Hello, World!\n") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_EqualsSign, u8"=", sizeof(u8"=") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_SingleLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_MultiLineComment, u8"", sizeof(u8"") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Colon, u8":", sizeof(u8":") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_Comma, u8",", sizeof(u8",") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_LineTerminator, u8"<line terminator>", sizeof(u8"<line terminator>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

static void
testScanner1
  (
    Arcadia_Process* process
  )
{
  static const char* input =
    u8""
    ;
  R_Mil_Scanner* scanner = R_Mil_Scanner_create(process);
  R_Mil_Scanner_setInput(process, scanner, (R_Utf8Reader*)R_Utf8StringReader_create(process, R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, input, strlen(input)))));

  expectAndNext(process, scanner, R_Mil_TokenType_StartOfInput, u8"<start of input>", sizeof(u8"<start of input>") - 1);
  expectAndNext(process, scanner, R_Mil_TokenType_EndOfInput, u8"<end of input>", sizeof(u8"<end of input>") - 1);
}

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char** argv
  )
{
  testScanner1(process);
  testScanner2(process);
  testScanner3(process);
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Status status[2];
  status[0] = R_startup();
  if (status[0]) {
    return EXIT_FAILURE;
  }
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    R_shutdown();
    return EXIT_FAILURE;
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
    Arcadia_Process_popJumpTarget(process);
  }
  status[0] = Arcadia_Process_getStatus(process);
  Arcadia_Process_relinquish(process);
  process = NULL;
  status[1] = R_shutdown();
  if (status[1] || status[0]) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
