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

#include "Tools/TemplateEngine/Context.h"

#include "Tools/TemplateEngine/FileContext.h"

static void
Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );  

static void
Context_destruct
  (
    Arcadia_Thread* thread,
    Context* self
  );

static void
Context_visit
  (
    Arcadia_Thread* thread,
    Context* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &Context_constructImpl,
  .destruct = &Context_destruct,
  .visit = &Context_visit,
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

Rex_defineObjectType(u8"Tools.TemplateEngine.Context", Context, u8"Arcadia.Object", Arcadia_Object, &_typeOperations);

void
Context_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  Context* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _Context_getType(thread);
  {
    Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->targetBuffer = NULL;
  _self->target = NULL;
  _self->temporaryBuffer = NULL;
  _self->temporary = NULL;
  _self->stack = NULL;
  _self->files = Arcadia_List_create(thread);
  Arcadia_Object_setType(thread, _self, _type);
}

static void
Context_destruct
  (
    Arcadia_Thread* thread,
    Context* self
  )
{/*Intentionally empty.*/}

static void
Context_visit
  (
    Arcadia_Thread* thread,
    Context* self
  )
{
  Arcadia_Object_visit(thread, self->targetBuffer);
  Arcadia_Object_visit(thread, self->target);

  Arcadia_Object_visit(thread, self->temporaryBuffer);
  Arcadia_Object_visit(thread, self->temporary);

  Arcadia_Object_visit(thread, self->stack);
  Arcadia_Object_visit(thread, self->files);
}

Context*
Context_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = { {.tag = Arcadia_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  Context* self = Arcadia_allocateObject(thread, _Context_getType(thread), 0, &argumentValues[0]);
  return self;
}

static void
recursionGuard
  (
    Arcadia_Thread* thread,
    Context* context,
    Arcadia_FilePath* path
  )
{
  path = Arcadia_FilePath_getFullPath(thread, path);
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, context->files); i < n; ++i) {
    Arcadia_FilePath* p = (Arcadia_FilePath*)Arcadia_List_getObjectReferenceValueAt(thread, context->files, i);
    if (Arcadia_FilePath_isEqualTo(thread, p, path)) {
      Arcadia_String* ps = Arcadia_FilePath_toGeneric(thread, p);
      Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
      Arcadia_Value v = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)ps };
      Arcadia_StringBuffer_append_pn(thread, sb, u8"recursive include of file `", sizeof(u8"recursive include of file `") - 1);
      Arcadia_StringBuffer_append(thread, sb, v);
      Arcadia_StringBuffer_append_pn(thread, sb, u8"`\0", sizeof(u8"`\0") - 1);
      fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
  }
  Arcadia_List_appendObjectReferenceValue(thread, context->files, path);
}

void
Context_onRun
  (
    Arcadia_Thread* thread,
    Context* context
  )
{
  Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_create(thread);
  while (!Arcadia_Stack_isEmpty(thread, context->stack)) {
    Arcadia_Value elementValue = Arcadia_Stack_peek(thread, context->stack);
    Arcadia_Stack_pop(thread, context->stack);
    Arcadia_FilePath* filePath = (Arcadia_FilePath*)Arcadia_Value_getObjectReferenceValue(&elementValue);
    FileContext* fileContext = FileContext_create(thread, context, filePath);
    Arcadia_ByteBuffer* sourceByteBuffer = NULL;
    Arcadia_JumpTarget jumpTarget;
    Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
    if (Arcadia_JumpTarget_save(&jumpTarget)) {
      sourceByteBuffer = Arcadia_FileSystem_getFileContents(thread, fileSystem, fileContext->sourceFilePath);
      Arcadia_Thread_popJumpTarget(thread);
    } else {
      Arcadia_Thread_popJumpTarget(thread);
      Arcadia_String* ps = Arcadia_FilePath_toGeneric(thread, filePath);
      Arcadia_StringBuffer* sb = Arcadia_StringBuffer_create(thread);
      Arcadia_Value v = { .tag = Arcadia_ValueTag_ObjectReference, .objectReferenceValue = (Arcadia_ObjectReferenceValue)ps };
      Arcadia_StringBuffer_append_pn(thread, sb, u8"failed to read file `", sizeof(u8"failed to read file `") - 1);
      Arcadia_StringBuffer_append(thread, sb, v);
      Arcadia_StringBuffer_append_pn(thread, sb, u8"`\0", sizeof(u8"`\0") - 1);
      fwrite(Arcadia_StringBuffer_getBytes(thread, sb), 1, Arcadia_StringBuffer_getNumberOfBytes(thread, sb), stderr);
      Arcadia_Thread_jump(thread);
    }
    fileContext->source = (Arcadia_Utf8Reader*)Arcadia_Utf8ByteBufferReader_create(thread, sourceByteBuffer);
    recursionGuard(thread, context, filePath);
    FileContext_execute(thread, fileContext);
    Arcadia_List_remove(thread, context->files, Arcadia_List_getSize(thread, context->files) - 1, 1);
  }
}
