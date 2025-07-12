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

#include "Arcadia/DataDefinitionLanguage/Include.h"

#include <string.h>

static Arcadia_DataDefinitionLanguage_Tree_Node*
doRead
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DataDefinitionLanguage_Parser* parser,
    const char* p,
    size_t n
  )
{ 
  Arcadia_String* input = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, p, n)));
  Arcadia_Utf8Reader* inputReader = (Arcadia_Utf8Reader*)Arcadia_Utf8StringReader_create(thread, input);
  Arcadia_DataDefinitionLanguage_Parser_setInput(thread, parser, inputReader);
  Arcadia_DataDefinitionLanguage_Tree_Node* node = Arcadia_DataDefinitionLanguage_Parser_run(thread, parser);
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis_run(thread, semanticalAnalysis, node);
  return node;
}

static void
doWrite
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_Unparser* unparser,
    Arcadia_DataDefinitionLanguage_Tree_Node* node,
    Arcadia_String* output
  )
{
  Arcadia_StringBuffer* received = Arcadia_StringBuffer_create(thread);
  Arcadia_DataDefinitionLanguage_Unparser_run(thread, unparser, node, received);
  Arcadia_Tests_assertTrue(thread, !Arcadia_StringBuffer_compareTo(thread, received, Arcadia_Value_makeObjectReferenceValue(output)));
}

static inline void
onTest
  (
    Arcadia_Thread* thread,
    Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis,
    Arcadia_DataDefinitionLanguage_Parser* parser,
    Arcadia_DataDefinitionLanguage_Unparser* unparser,
    const char *input,
    const char* output
  )
{
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_DataDefinitionLanguage_Tree_Node* node = doRead(thread, semanticalAnalysis, parser, input, strlen(input));
    doWrite(thread, unparser, node, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, output, strlen(output)))));
    Arcadia_Thread_popJumpTarget(thread);
  } else {
    Arcadia_Thread_popJumpTarget(thread);
    Arcadia_Thread_jump(thread);
  }
}

static void
test1
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_DataDefinitionLanguage_SemanticalAnalysis* semanticalAnalysis = Arcadia_DataDefinitionLanguage_SemanticalAnalysis_create(thread);
  Arcadia_DataDefinitionLanguage_Parser* parser = Arcadia_DataDefinitionLanguage_Parser_create(thread);
  Arcadia_DataDefinitionLanguage_Unparser* unparser = Arcadia_DataDefinitionLanguage_Unparser_create(thread);
  onTest(thread, semanticalAnalysis, parser, unparser,
                 u8"{ prename : \"Michael\", surname: \"Heilmann\" }",
                 u8"{\n  prename : \"Michael\",\n  surname : \"Heilmann\",\n}\n");
}

int
main
  (
    int argc,
    char** argv
  )
{
  if (!Arcadia_Tests_safeExecute(&test1)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
