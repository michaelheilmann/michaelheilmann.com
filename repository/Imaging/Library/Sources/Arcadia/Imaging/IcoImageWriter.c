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

#include "Arcadia/Imaging/IcoImageWriter.h"

#include "Arcadia/Imaging/ImageWriterParameters.h"
#include "Arcadia/Imaging/ImageManager.h"

static void
IcoImageWriter_constructImpl
  ( 
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  );

static void
IcoImageWriter_visit
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static Arcadia_ImmutableList*
IcoImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static void
IcoImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
IcoImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static ImageWriter*
IcoImageWriter_getPngImageWriter
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  );

static void
IcoImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  );

static void
IcoImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

static Arcadia_ImmutableList*
IcoImageWriter_getSupportedTypesImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{ return self->supportedTypes; }

static void
IcoImageWriter_writeToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{ 
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1)))),
  };

  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) < 1) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    IcoImageWriter_writeIcoToPathImpl(thread, self, sourcePixelBuffers, targetPath);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static void
IcoImageWriter_writeToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  Arcadia_Value a = Arcadia_Value_makeObjectReferenceValue(extension);
  Arcadia_Value b[] = {
    Arcadia_Value_makeObjectReferenceValue(Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1)))),
  };
  if (Arcadia_Value_isEqualTo(thread, &a, &b[0])) {
    if (Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) < 1) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    IcoImageWriter_writeIcoToByteBufferImpl(thread, self, sourcePixelBuffers, targetByteBuffer);
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
}

static ImageWriter*
IcoImageWriter_getPngImageWriter
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{
  Arcadia_Visuals_ImageManager* imageManager = Arcadia_Visuals_ImageManager_getOrCreate(thread);
  Arcadia_String* extension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)));
  Arcadia_List* writers = Arcadia_Visuals_ImageManager_getWriters(thread, imageManager, extension);
  if (!Arcadia_Collection_getSize(thread, (Arcadia_Collection*)writers)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NotExists);
    Arcadia_Thread_popJumpTarget(thread);
  }
  ImageWriter* writer = (ImageWriter*)Arcadia_List_getObjectReferenceValueAt(thread, writers, 0);
  return writer;
}

static void
IcoImageWriter_writeIcoToPathImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_String* targetPath
  )
{
  Arcadia_ByteBuffer* targetByteBuffer = Arcadia_ByteBuffer_create(thread);
  Arcadia_String* extension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1)));
  ImageWriter_writeToByteBuffer(thread, (ImageWriter*)self, extension, sourcePixelBuffers, targetByteBuffer);
  Arcadia_FileSystem_setFileContents(thread, Arcadia_FileSystem_create(thread), Arcadia_FilePath_parseUnix(thread, Arcadia_String_getBytes(thread, targetPath), Arcadia_String_getNumberOfBytes(thread, targetPath)), targetByteBuffer);
}

static void
IcoImageWriter_writeIcoToByteBufferImpl
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  )
{
  typedef struct ICONDIR {
    uint16_t reserved1;
    uint16_t type;
    uint16_t numberOfImages;
  } ICONDIR;

  typedef struct ICONDIRENTRY {
    uint8_t width;
    uint8_t height;
    uint8_t numberOfColors;
    uint8_t reserved1;
    uint16_t numberOfColorPlanes;
    uint16_t numberOfBitsPerPixel;
    uint32_t imageSize;
    uint32_t offset;
  } ICONDIRENTRY;

  ICONDIR iconDir = {
    .reserved1 = 0,
    .type = 1,
    .numberOfImages = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers)
  };
  Arcadia_List* pixelBuffers = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDir, sizeof(ICONDIR));
  
  ImageWriter* pngImageWriter =  IcoImageWriter_getPngImageWriter(thread, self);
  Arcadia_String* pngExtension = Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"png", sizeof(u8"png") - 1)));

  Arcadia_ByteBuffer* temporary = Arcadia_ByteBuffer_create(thread);
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers); i < n; ++i) {
    Arcadia_Visuals_PixelBuffer* pixelBuffer = (Arcadia_Visuals_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBuffers);
    Arcadia_List_insertBackObjectReferenceValue(thread, pixelBuffers, pixelBuffer);
    ImageWriter_writeToByteBuffer(thread, pngImageWriter, pngExtension, pixelBuffers, temporary);
    if (Arcadia_Visuals_PixelFormat_An8Rn8Gn8Bn8 != Arcadia_Visuals_PixelBuffer_getPixelFormat(thread, pixelBuffer)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    size_t width = Arcadia_Visuals_PixelBuffer_getNumberOfColumns(thread, pixelBuffer),
           height = Arcadia_Visuals_PixelBuffer_getNumberOfRows(thread, pixelBuffer);
    if (width > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (height > 256) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }
    if (width == 256) {
      width = 0;
    }
    if (height == 256) {
      height = 256;
    }

    ICONDIRENTRY iconDirEntry = { .width = width,
                                  .height = height,
                                  .numberOfColors = 0,
                                  .reserved1 = 0,
                                  .numberOfColorPlanes = 1,
                                  .numberOfBitsPerPixel = 32,
                                  .imageSize = Arcadia_ByteBuffer_getSize(thread, temporary),
                                  .offset = sizeof(ICONDIR) + Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers) * sizeof(ICONDIRENTRY) + offset };
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, &iconDirEntry, sizeof(ICONDIRENTRY));
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
  for (Arcadia_SizeValue i = 0, offset = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)sourcePixelBuffers); i < n; ++i) {
    Arcadia_Visuals_PixelBuffer* pixelBuffer = (Arcadia_Visuals_PixelBuffer*)Arcadia_List_getObjectReferenceValueAt(thread, sourcePixelBuffers, i);
    Arcadia_ByteBuffer_clear(thread, temporary);
    Arcadia_Collection_clear(thread, (Arcadia_Collection*)pixelBuffers);
    Arcadia_List_insertBackObjectReferenceValue(thread, pixelBuffers, pixelBuffer);
    ImageWriter_writeToByteBuffer(thread, pngImageWriter, pngExtension, pixelBuffers, temporary);
    Arcadia_ByteBuffer_append_pn(thread, targetByteBuffer, temporary->p, temporary->sz);
    offset += Arcadia_ByteBuffer_getSize(thread, temporary);
  }
}

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  .construct = &IcoImageWriter_constructImpl,
  .destruct = NULL,
  .visit = &IcoImageWriter_visit,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Imaging.IcoImageWriter", IcoImageWriter, u8"ImageWriter", ImageWriter, &_typeOperations);

static void
IcoImageWriter_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    Arcadia_Value* argumentValues
  )
{
  IcoImageWriter* _self = Arcadia_Value_getObjectReferenceValue(self);
  Arcadia_Type* _type = _IcoImageWriter_getType(thread);
  {
    Arcadia_Value argumentValues[] = {
      Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
    };
    Arcadia_superTypeConstructor(thread, _type, self, 0, &argumentValues[0]);
  }
  _self->supportedTypes = NULL;
  Arcadia_List* supportedTypes = (Arcadia_List*)Arcadia_ArrayList_create(thread);
  Arcadia_List_insertBackObjectReferenceValue(thread, supportedTypes, Arcadia_String_create(thread, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_create(thread, u8"ico", sizeof(u8"ico") - 1))));
  _self->supportedTypes = Arcadia_ImmutableList_create(thread, Arcadia_Value_makeObjectReferenceValue(supportedTypes));
  ((ImageWriter*)_self)->getSupportedTypes = (Arcadia_ImmutableList*(*)(Arcadia_Thread*,ImageWriter*))&IcoImageWriter_getSupportedTypesImpl;
  ((ImageWriter*)_self)->writeToPath = (void (*)(Arcadia_Thread*,ImageWriter*,Arcadia_String*,Arcadia_List*,Arcadia_String*))&IcoImageWriter_writeToPathImpl;
  ((ImageWriter*)_self)->writeToByteBuffer = (void (*)(Arcadia_Thread*, ImageWriter*, Arcadia_String*, Arcadia_List*, Arcadia_ByteBuffer*))&IcoImageWriter_writeToByteBufferImpl;
  Arcadia_Object_setType(thread, (Arcadia_Object*)_self, _type);
}

static void
IcoImageWriter_visit
  (
    Arcadia_Thread* thread,
    IcoImageWriter* self
  )
{
  if (self->supportedTypes) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->supportedTypes);
  }
}

IcoImageWriter*
IcoImageWriter_create
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_Value argumentValues[] = {
    Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void),
  };
  IcoImageWriter* self = Arcadia_allocateObject(thread, _IcoImageWriter_getType(thread), 0, &argumentValues[0]);
  return self;
}
