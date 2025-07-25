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

#include "Tools/TemplateEngine/FileContext.h"

static Arcadia_BooleanValue
is
  (
    Arcadia_Thread* thread,
    FileContext* context,
    uint32_t expectedCodePoint
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return expectedCodePoint == currentCodePoint;
}

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '+') || is(thread, context, '-');
}

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  return ('0' <= current && current <= '9');
}

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '_');
}

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, '(');
}

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return is(thread, context, ')');
}

static void
onIdentifier
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!isUnderscore(thread, context) && !isLetter(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  do {
    Arcadia_Natural32Value targetCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
    Arcadia_Utf8Reader_next(thread, context->source);
  } while (isUnderscore(thread, context) || isLetter(thread, context) || isDigit(thread, context));
}

static void
onString
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!is(thread, context, '"')) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);

  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (true) {
    if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          Arcadia_Natural32Value targetCodePoint = '\\';
          Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        case '"': {
          Arcadia_Natural32Value targetCodePoint = '"';
          Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        default: {
          Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Thread_jump(thread);
        } break;
      };
    } else {
      if (current == '"') {
        Arcadia_Utf8Reader_next(thread, context->source);
        return;
      } else if (current == '\\') {
        lastWasSlash = Arcadia_BooleanValue_True;
        Arcadia_Utf8Reader_next(thread, context->source);
      } else {
        Arcadia_Utf8Writer_writeCodePoints(thread, context->context->temporary, &current, 1);
        Arcadia_Utf8Reader_next(thread, context->source);
      }
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Thread_jump(thread);
}

#include "Tools/TemplateEngine/Ast.h"

static Arcadia_String*
getLiteral
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  return Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz));
}

static void
evalAst
  (
    Arcadia_Thread* thread,
    FileContext* context,
    Ast* ast
  )
{
  switch (ast->type) {
    case GETVARIABLE: {
      Arcadia_Value k = Arcadia_Value_Initializer();
      Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)ast->name);
      Arcadia_Value v = Arcadia_Map_get(thread, context->environment, k);
      if (Arcadia_Value_isVoidValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"variable `", sizeof(u8"variable `") - 1);
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"` not defined\n\0", sizeof(u8"` not defined\n\0") - 1);
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      } else  if (!Arcadia_Value_isObjectReferenceValue(&v)) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"variable `", sizeof(u8"variable `") - 1);
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"` is not of type string\n\0", sizeof(u8"` is not of type string\n\0") - 1);
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Object* object = Arcadia_Value_getObjectReferenceValue(&v);
      if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, object), _Arcadia_String_getType(thread))) {
        // Error.
        Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"variable `", sizeof(u8"variable `") - 1);
        Arcadia_StringBuffer_insertBack(thread, sb, k);
        Arcadia_StringBuffer_append_pn(thread, sb, u8"` is not of type string\n\0", sizeof(u8"` is not of type string\n\0") - 1);
        fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_ByteBuffer_append_pn(thread, context->context->targetBuffer, Arcadia_String_getBytes(thread, (Arcadia_String*)object), Arcadia_String_getNumberOfBytes(thread, (Arcadia_String*)object));
    } break;
    case INVOKE: {
      if (Arcadia_String_isEqualTo_pn(thread, ast->name, u8"include", sizeof(u8"include") - 1)) {
        Arcadia_FilePath* filePath = Arcadia_FilePath_parseGeneric(thread, Arcadia_String_getBytes(thread, ast->argument), Arcadia_String_getNumberOfBytes(thread, ast->argument));
        Arcadia_Value value;
        Arcadia_Value_setObjectReferenceValue(&value, filePath);
        Arcadia_Stack_push(thread, context->context->stack, value);
        Context_onRun(thread, context->context);
      } else {
        // unknown procedure
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
}

static Ast*
onExpression
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
  onIdentifier(thread, context);
  Arcadia_Integer32Value type = GETVARIABLE;
  Arcadia_String* name = getLiteral(thread, context);
  Arcadia_String* argument = NULL;
  if (isLeftParenthesis(thread, context)) {
    type = INVOKE;
    Arcadia_Utf8Reader_next(thread, context->source);
    if (is(thread, context, '"')) {
      Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
      onString(thread, context);
      argument = getLiteral(thread, context);
    }
    if (!isRightParenthesis(thread, context)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Utf8Reader_next(thread, context->source);
  }
  Ast* ast = Ast_create(thread, type, name, argument);
  return ast;
}

static Ast*
onIncludeDirective
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!isLeftParenthesis(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);
  Arcadia_ByteBuffer_clear(thread, context->context->temporaryBuffer);
  onString(thread, context);
  Ast* ast = Ast_create(thread, INVOKE, Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"include", sizeof(u8"include") - 1)),
                                        getLiteral(thread, context));
  if (!isRightParenthesis(thread, context)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Utf8Reader_next(thread, context->source);
  return ast;
}

static void
onStatement
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  Ast* ast = onExpression(thread, context);
  evalAst(thread, context, ast);
}

static void
onDirective
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  if (!Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Natural32Value current = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
  switch (current) {
    case '@': {
      Arcadia_Natural32Value targetCodePoint = '@';
      Arcadia_Utf8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
      Arcadia_Utf8Reader_next(thread, context->source);
    } break;
    case '{': {
      Arcadia_Utf8Reader_next(thread, context->source);
      onStatement(thread, context);
      if (!is(thread, context, '}')) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_Utf8Reader_next(thread, context->source);
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  };
}

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  );

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &FileContext_constructImpl,
  .destruct = &FileContext_destruct,
  .visit = &FileContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Tools.TemplateEngine.FileContext", FileContext, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

static void
FileContext_destruct
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{/*Intentionally empty.*/}

static void
FileContext_visit
  (
    Arcadia_Thread* thread,
    FileContext* self
  )
{
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->sourceFilePath);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->source);
  Arcadia_Object_visit(thread, (Arcadia_Object*)self->environment);
}

static void
FileContext_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  FileContext* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _FileContext_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  _self->context = (Context*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[0], _Context_getType(thread));
  _self->sourceFilePath = (Arcadia_FilePath*)Arcadia_ArgumentsValidation_getObjectReferenceValue(thread, &argumentValues[1], _Arcadia_FilePath_getType(thread));
  _self->source = NULL;
  _self->environment = Arcadia_Map_create(thread);
  Arcadia_Value k, v;

  Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"siteAddress", sizeof(u8"siteAddress") - 1)));
  Arcadia_Value_setObjectReferenceValue(&v, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"https://michaelheilmann.com", sizeof(u8"https://michaelheilmann.com") - 1)));
  Arcadia_Map_set(thread, _self->environment, k, v, NULL, NULL);

  Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"generatorName", sizeof(u8"generatorName") - 1)));
  Arcadia_Value_setObjectReferenceValue(&v, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"Michael Heilmann's Arcadia Template Engine", sizeof(u8"Michael Heilmann's Arcadia Template Engine") - 1)));
  Arcadia_Map_set(thread, _self->environment, k, v, NULL, NULL);

  Arcadia_Value_setObjectReferenceValue(&k, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"generatorHome", sizeof(u8"generatorHome") - 1)));
  Arcadia_Value_setObjectReferenceValue(&v, (Arcadia_ObjectReferenceValue)Arcadia_String_create_pn(thread, Arcadia_ImmutableByteArray_create(thread, u8"https://michaelheilmann.com", sizeof(u8"https://michaelheilmann.com") - 1)));
  Arcadia_Map_set(thread, _self->environment, k, v, NULL, NULL);

  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

FileContext*
FileContext_create
  (
    Arcadia_Thread* thread,
    Context* context,
    Arcadia_FilePath* sourceFilePath
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)context),
    Arcadia_Value_makeObjectReferenceValue((Arcadia_ObjectReferenceValue)sourceFilePath),
  };
  FileContext* self = Arcadia_allocateObject(thread, _FileContext_getType(thread), 2, &argumentValues[0]);
  return self;
}

void
FileContext_execute
  (
    Arcadia_Thread* thread,
    FileContext* context
  )
{
  while (Arcadia_Utf8Reader_hasCodePoint(thread, context->source)) {
    Arcadia_Natural32Value sourceCodePoint = Arcadia_Utf8Reader_getCodePoint(thread, context->source);
    if (sourceCodePoint == '@') {
      Arcadia_Utf8Reader_next(thread, context->source);
      onDirective(thread, context);
    } else {
      Arcadia_Natural32Value targetCodePoint = sourceCodePoint;
      Arcadia_Utf8Writer_writeCodePoints(thread, context->context->target, &targetCodePoint, 1);
      Arcadia_Utf8Reader_next(thread, context->source);
    }
  }
}
