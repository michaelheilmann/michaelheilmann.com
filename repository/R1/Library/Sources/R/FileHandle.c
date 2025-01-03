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

// Last modified: 2024-10-07

#include "R/FileHandle.h"

#include "R/FileSystem.h"
#include "R/FilePath.h"
#include "R/JumpTarget.h"
#include "R/Object.h"
#include "R/Status.h"
#include "R/String.h"
#include "R/ArgumentsValidation.h"

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void
R_FileHandle_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  );

static void
R_FileHandle_destruct
  (
    R_FileHandle* self
  );

static void
R_FileHandle_visit
  (
    R_FileHandle* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_FileHandle_constructImpl,
  .destruct = &R_FileHandle_destruct,
  .visit = &R_FileHandle_visit,
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

Rex_defineObjectType("R.FileHandle", R_FileHandle, "R.Object", R_Object, &_typeOperations);

static void
R_FileHandle_constructImpl
  (
    R_Value* self,
    R_SizeValue numberOfArgumentValues,
    R_Value const* argumentValues
  )
{
  R_FileHandle* _self = R_Value_getObjectReferenceValue(self);
  R_Type* _type = _R_FileHandle_getType();
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void} };
    R_Object_constructImpl(self, 0, &argumentValues[0]);
  }
  if (1 != numberOfArgumentValues) {
    R_setStatus(R_Status_NumberOfArgumentsInvalid);
    R_jump();
  }
  _self->fileSystem = R_Argument_getObjectReferenceValue(&argumentValues[0], _R_FileSystem_getType());
  R_Object_lock(_self->fileSystem);
  _self->fd = NULL;
  _self->flags = 0;
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_FileHandle_destruct
  (
    R_FileHandle* self
  )
{
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
  R_Object_unlock(self->fileSystem);
  self->fileSystem = NULL;
}

static void
R_FileHandle_visit
  (
    R_FileHandle* self
  )
{
  R_Object_visit(self->fileSystem);
}

R_FileHandle*
R_FileHandle_create
  (
    R_FileSystem* fileSystem
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = R_VoidValue_Void } };
  if (fileSystem) {
    R_Value_setObjectReferenceValue(&argumentValues[0], fileSystem);
  }
  R_FileHandle* self = R_allocateObject(_R_FileHandle_getType(), 1, &argumentValues[0]);
  return self;
}

void R_FileHandle_close(R_FileHandle* self) {
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
}

R_BooleanValue R_FileHandle_isClosed(R_FileHandle const* self) {
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return 0 == ((Flags_OpenRead | Flags_OpenWrite) & self->flags);
}

R_BooleanValue R_FileHandle_isOpened(R_FileHandle const* self) {
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return 0 != (Flags_OpenWrite & self->flags);
}

R_BooleanValue R_FileHandle_isOpenedForReading(R_FileHandle const* self) {
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return 0 != (Flags_OpenRead & self->flags);
}

R_BooleanValue R_FileHandle_isOpenedForWriting(R_FileHandle const* self) {
  if (!self) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  return Flags_OpenWrite == (Flags_OpenWrite & self->flags);
}

void R_FileHandle_openForReading(R_FileHandle* self, R_FilePath* path) {
  R_FileHandle_close(self);
  R_String* nativePathString = R_FilePath_toNative(path);
  self->fd = fopen(R_String_getBytes(nativePathString), "rb");
  if (!self->fd) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  self->flags |= Flags_OpenRead;
}

void R_FileHandle_openForWriting(R_FileHandle* self, R_FilePath* path) {
  R_FileHandle_close(self);
  R_String* nativePathString = R_FilePath_toNative(path);
  self->fd = fopen(R_String_getBytes(nativePathString), "wb");
  if (!self->fd) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  self->flags |= Flags_OpenWrite;
}

void R_FileHandle_read(R_FileHandle* self, void* bytes, R_SizeValue bytesToRead, R_SizeValue* bytesRead) {
  if (!bytes || !bytesRead) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_FileHandle_isOpenedForReading(self)) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  if (!bytesToRead) {
    *bytesRead = 0;
    return;
  }
  size_t bytesReadNow = fread(bytes, 1, bytesToRead, self->fd);
  if (bytesReadNow < bytesToRead) {
    if (feof(self->fd)) {
      *bytesRead = bytesReadNow;
    } else if (ferror(self->fd)) {
      R_setStatus(R_Status_FileSystemOperationFailed);
      R_jump();
    }
  } else{
    *bytesRead = bytesReadNow;
  }
}

void R_FileHandle_write(R_FileHandle* self, void const* bytes, R_SizeValue bytesToWrite, R_SizeValue* bytesWritten) {
  if (!bytes || !bytesWritten) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  if (!R_FileHandle_isOpenedForWriting(self)) {
    R_setStatus(R_Status_OperationInvalid);
    R_jump();
  }
  size_t bytesWrittenNow = fwrite(bytes, 1, bytesToWrite, self->fd);
  if (ferror(self->fd)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  *bytesWritten = bytesWrittenNow;
}
