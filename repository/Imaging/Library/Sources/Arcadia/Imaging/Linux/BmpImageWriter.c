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

#include "Arcadia/Imaging/Linux/BmpImageWriter.h"

#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/Linux/Include.h"

#include "Arcadia/Imaging/PixelBuffer.h"

#define STB_IMAGE_WRITE_STATIC static
#define STBIWDEF
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Arcadia/Imaging/Linux/_stb_image_write.h"

typedef struct WriteContext {
  Arcadia_Process* process;
  Arcadia_ByteBuffer* byteBuffer;
  Arcadia_Status status;
} WriteContext;

static void
writeCallback
  (
    WriteContext* writeContext,
    void* data,
    int size
  );

static void
writeCallback
  (
    WriteContext* context,
    void* data,
    int size
  )
{
  Arcadia_Process* process = context->process;
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    Arcadia_ByteBuffer_append_pn(thread, context->byteBuffer, data, size);
  }
  Arcadia_Thread_popJumpTarget(thread);
}

static void
BmpImageWriter_constructImpl
  ( 
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
BmpImageWriter_visit
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self
  );

static Arcadia_ImmutableList*
BmpImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self
  );

static void
BmpImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
BmpImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static void
BmpImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  );

static void
BmpImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static Arcadia_ImmutableList*
BmpImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self
  )
{ return self->supportedTypes; }

static void
BmpImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{ 
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bmp", sizeof(u8"bmp") - 1)))),
  };
  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, 0);
    if (Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Visuals_PixelBuffer_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    BmpImageWriter_writeBmpToPathImpl(thread, self, (Arcadia_Visuals_PixelBuffer*)sourceObject, targetPath);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
BmpImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bmp", sizeof(u8"bmp") - 1)))),
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)))),
  };
  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (1 != Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_ObjectReferenceValue sourceObject = Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, 0);
    if (!Arcadia_Type_isSubType(thread, Arcadia_Object_getType(thread, sourceObject), _Arcadia_Visuals_PixelBuffer_getType(thread))) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    BmpImageWriter_writeBmpToByteBufferImpl(thread, self, (Arcadia_Visuals_PixelBuffer*)sourceObject, targetByteBuffer);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
BmpImageWriter_writeBmpToPathImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  BmpImageWriter_writeBmpToByteBufferImpl(thread, (ImageWriter*)self, sourcePixelBuffer, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread),
                                     Arcadia_FilePath_parseUnix(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static void
BmpImageWriter_writeBmpToByteBufferImpl
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self,
    Arcadia_Visuals_PixelBuffer* sourcePixelBuffer,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Process* process = Arcadia_Thread_getProcess(thread);
  WriteContext context;
  context.process = process;
  context.byteBuffer = targetByteBuffer;

  int components;
  switch (sourcePixelBuffer->pixelFormat) {
    case Arcadia_Visuals_PixelFormat_Rn8Gn8Bn8: {
      sourcePixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 3;
    } break;
    case Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8: {
      sourcePixelBuffer = Arcadia_Visuals_PixelBuffer_createClone(thread, sourcePixelBuffer);
      Arcadia_Visuals_PixelBuffer_setPixelFormat(thread, sourcePixelBuffer, Arcadia_Visuals_PixelFormat_Bn8Gn8Rn8An8);
      Arcadia_Visuals_PixelBuffer_setLinePadding(thread, sourcePixelBuffer, 0);
      components = 4;
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
      Arcadia_Thread_jump(thread);
    } break;
  };

  if (!stbi_write_bmp_to_func((stbi_write_func*)&writeCallback, &context,
                              Arcadia_Visuals_PixelBuffer_getWidth(thread, sourcePixelBuffer),
                              Arcadia_Visuals_PixelBuffer_getHeight(thread, sourcePixelBuffer),
                              components,
                              sourcePixelBuffer->bytes)) {
    context.status = Arcadia_Status_EnvironmentFailed;
  }
  if (context.status) {
    Arcadia_Thread_setStatus(thread, context.status);
    Arcadia_Thread_jump(thread);
  }
}

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &BmpImageWriter_constructImpl,
  .destruct = NULL,
  .visit = &BmpImageWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"BmpImageWriter", BmpImageWriter, u8"ImageWriter", ImageWriter, &_typeOperations);

static void
BmpImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  BmpImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _BmpImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->supportedTypes = NULL;
  Arcadia_List* supportedTypes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"bmp", sizeof(u8"bmp") - 1))));
  _self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  ((ImageWriter*)_self)->getSupportedTypes = (Arcadia_ImmutableList*(*)(Arcadia_Thread*,ImageWriter*))&BmpImageWriter_getSupportedTypesImpl;
  ((ImageWriter*)_self)->writeToPath = (void (*)(Arcadia_Thread*,ImageWriter*,Arcadia_String*,Arcadia_List*,Arcadia_String*))&BmpImageWriter_writeToPathImpl;
  ((ImageWriter*)_self)->writeToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_String*, Arcadia_List*, Arcadia_ByteBuffer*)) & BmpImageWriter_writeToByteBufferImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
BmpImageWriter_visit
  (
    Arcadia_Thread* thread,
    BmpImageWriter* self
  )
{
  if (self->supportedTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->supportedTypes);
  }
}

BmpImageWriter*
BmpImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  BmpImageWriter* self = Arcadia_allocateObject(thread, _BmpImageWriter_getType(thread), 0, &argumentValues[0]);
  return self;
}
