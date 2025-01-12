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

// Last modified: 2024-09-09

#include "Tools/TemplateEngine/FileContext.h"

static Arcadia_BooleanValue
is
  (
    Arcadia_Process* process,
    FileContext* context,
    uint32_t expectedCodePoint
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value currentCodePoint = R_Utf8Reader_getCodePoint(process, context->source);
  return expectedCodePoint == currentCodePoint;
}

static Arcadia_BooleanValue
isSign
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  return is(process, context, '+') || is(process, context, '-');
}

static Arcadia_BooleanValue
isLetter
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = R_Utf8Reader_getCodePoint(process, context->source);
  return ('A' <= current && current <= 'Z')
      || ('a' <= current && current <= 'z');
}

static Arcadia_BooleanValue
isDigit
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, context->source)) {
    return Arcadia_BooleanValue_False;
  }
  Arcadia_Natural32Value current = R_Utf8Reader_getCodePoint(process, context->source);
  return ('0' <= current && current <= '9');
}

static Arcadia_BooleanValue
isUnderscore
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  return is(process, context, '_');
}

static Arcadia_BooleanValue
isLeftParenthesis
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  return is(process, context, '(');
}

static Arcadia_BooleanValue
isRightParenthesis
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  return is(process, context, ')');
}

static void
onIdentifier
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!isUnderscore(process, context) && !isLetter(process, context)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  do {
    Arcadia_Natural32Value targetCodePoint = R_Utf8Reader_getCodePoint(process, context->source);
    R_Utf8Writer_writeCodePoints(process, context->context->temporary, &targetCodePoint, 1);
    R_Utf8Reader_next(process, context->source);
  } while (isUnderscore(process, context) || isLetter(process, context) || isDigit(process, context));
}

static void
onString
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!is(process, context, '"')) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  R_Utf8Reader_next(process, context->source);

  Arcadia_BooleanValue lastWasSlash = Arcadia_BooleanValue_False;
  while (true) {
    if (!R_Utf8Reader_hasCodePoint(process, context->source)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    }
    Arcadia_Natural32Value current = R_Utf8Reader_getCodePoint(process, context->source);
    if (lastWasSlash) {
      switch (current) {
        case '\\': {
          Arcadia_Natural32Value targetCodePoint = '\\';
          R_Utf8Writer_writeCodePoints(process, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        case '"': {
          Arcadia_Natural32Value targetCodePoint = '"';
          R_Utf8Writer_writeCodePoints(process, context->context->temporary, &targetCodePoint, 1);
          lastWasSlash = Arcadia_BooleanValue_False;
        } break;
        default: {
          Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
          Arcadia_Process_jump(process);
        } break;
      };
    } else {
      if (current == '"') {
        R_Utf8Reader_next(process, context->source);
        return;
      } else if (current == '\\') {
        lastWasSlash = Arcadia_BooleanValue_True;
        R_Utf8Reader_next(process, context->source);
      } else {
        R_Utf8Writer_writeCodePoints(process, context->context->temporary, &current, 1);
        R_Utf8Reader_next(process, context->source);
      }
    }
  }
  Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
  Arcadia_Process_jump(process);
}

static void
onIncludeDirective
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!isLeftParenthesis(process, context)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  R_Utf8Reader_next(process, context->source);
  R_ByteBuffer_clear(context->context->temporaryBuffer);
  onString(process, context);
  R_FilePath* filePath = R_FilePath_parseWindows(process, context->context->temporaryBuffer->p, context->context->temporaryBuffer->sz);
  R_Value value;
  R_Value_setObjectReferenceValue(&value, filePath);
  R_Stack_push(process, context->context->stack, value);
  if (!isRightParenthesis(process, context)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  R_Utf8Reader_next(process, context->source);
}

static void
onStatement
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  R_ByteBuffer_clear(context->context->temporaryBuffer);
  onIdentifier(process, context);
  if (R_ByteBuffer_isEqualTo_pn(process, context->context->temporaryBuffer, "include", sizeof("include") - 1)) {
    onIncludeDirective(process, context);
    Context_onRun(process, context->context);
  } else {
    R_Value t;
    R_Value_setObjectReferenceValue(&t, (R_ObjectReferenceValue)context->context->temporaryBuffer);
    R_Value_setObjectReferenceValue(&t, (R_ObjectReferenceValue)R_String_create(process, t));
    t = R_Map_get(process, context->environment, t);
    if (!R_Value_isObjectReferenceValue(&t)) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
    R_Object* object = R_Value_getObjectReferenceValue(&t);
    if (!Arcadia_Type_isSubType(R_Object_getType(object), _R_String_getType(process))) {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
      Arcadia_Process_jump(process);
    }
    R_ByteBuffer_append_pn(process, context->context->targetBuffer, R_String_getBytes((R_String*)object), R_String_getNumberOfBytes((R_String*)object));
  }
}

static void
onDirective
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  if (!R_Utf8Reader_hasCodePoint(process, context->source)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Process_jump(process);
  }
  Arcadia_Natural32Value current = R_Utf8Reader_getCodePoint(process, context->source);
  switch (current) {
    case '@': {
      Arcadia_Natural32Value targetCodePoint = '@';
      R_Utf8Writer_writeCodePoints(process, context->context->target, &targetCodePoint, 1);
      R_Utf8Reader_next(process, context->source);
    } break;
    case '{': {
      R_Utf8Reader_next(process, context->source);
      onStatement(process, context);
      if (!is(process, context, '}')) {
        Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
        Arcadia_Process_jump(process);
      }
      R_Utf8Reader_next(process, context->source);
    } break;
    default: {
      Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Process_jump(process);
    } break;
  };
}

static void
FileContext_destruct
  (
    Arcadia_Process* process,
    FileContext* self
  );

static void
FileContext_visit
  (
    Arcadia_Process* process,
    FileContext* self
  );

static void
FileContext_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &FileContext_constructImpl,
  .destruct = &FileContext_destruct,
  .visit = &FileContext_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
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

Rex_defineObjectType(u8"Tools.TemplateEngine.FileContext", FileContext, u8"R.Object", R_Object, &_typeOperations);

static void
FileContext_destruct
  (
    Arcadia_Process* process,
    FileContext* self
  )
{/*Intentionally empty.*/}

static void
FileContext_visit
  (
    Arcadia_Process* process,
    FileContext* self
  )
{
  R_Object_visit(self->context);
  R_Object_visit(self->sourceFilePath);
  R_Object_visit(self->source);
  R_Object_visit(self->environment);
}

static void
FileContext_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  FileContext* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _FileContext_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  if (2 != numberOfArgumentValues) {
    Arcadia_Process_setStatus(process, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[0]), _Context_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  if (!Arcadia_Type_isSubType(R_Value_getType(process, &argumentValues[1]), _R_FilePath_getType(process))) {
    Arcadia_Process_setStatus(process, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Process_jump(process);
  }
  _self->context = R_Value_getObjectReferenceValue(&argumentValues[0]);
  _self->sourceFilePath = R_Value_getObjectReferenceValue(&argumentValues[1]);
  _self->source = NULL;
  _self->environment = R_Map_create(process);
  R_Value k, v;
  R_Value_setObjectReferenceValue(&k, (R_ObjectReferenceValue)R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"siteAddress", sizeof(u8"siteAddress") - 1)));
  R_Value_setObjectReferenceValue(&v, (R_ObjectReferenceValue)R_String_create_pn(process, Arcadia_ImmutableByteArray_create(process, u8"https://michaelheilmann.com", sizeof(u8"https://michaelheilmann.com") - 1)));
  R_Map_set(process, _self->environment, k, v);
  R_Object_setType((R_Object*)_self, _type);
}

FileContext*
FileContext_create
  (
    Arcadia_Process* process,
    Context* context,
    R_FilePath* sourceFilePath
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)context },
                               {.tag = R_ValueTag_ObjectReference, .objectReferenceValue = (R_ObjectReferenceValue)sourceFilePath }, };
  FileContext* self = R_allocateObject(process, _FileContext_getType(process), 2, &argumentValues[0]);
  return self;
}

void
FileContext_execute
  (
    Arcadia_Process* process,
    FileContext* context
  )
{
  while (R_Utf8Reader_hasCodePoint(process, context->source)) {
    Arcadia_Natural32Value sourceCodePoint = R_Utf8Reader_getCodePoint(process, context->source);
    if (sourceCodePoint == '@') {
      R_Utf8Reader_next(process, context->source);
      onDirective(process, context);
    } else {
      Arcadia_Natural32Value targetCodePoint = sourceCodePoint;
      R_Utf8Writer_writeCodePoints(process, context->context->target, &targetCodePoint, 1);
      R_Utf8Reader_next(process, context->source);
    }
  }
}
