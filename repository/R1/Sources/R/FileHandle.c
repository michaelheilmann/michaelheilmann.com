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

// Last modified: 2024-08-29

#include "R/FileHandle.h"

#include "R.h" 

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void R_FileHandle_finalize(R_FileHandle* self);

static void R_FileHandle_finalize(R_FileHandle* self) {
  if (self->fd) {
    if (self->fd != stdin && self->fd != stderr && self->fd != stdout) {
      fclose(self->fd);
    }
    self->fd = NULL;
    self->flags = 0;
  }
}

void _R_FileHandle_registerType() {
  R_registerObjectType("R.FileHandle", sizeof("R.FileHandle") - 1, sizeof(R_FileHandle), NULL, &R_FileHandle_finalize);
}

R_FileHandle* R_FileHandle_create() {
  R_FileHandle* self = R_allocateObject("R.FileHandle", sizeof("R.FileHandle") - 1, sizeof(R_FileHandle));
  self->fd = NULL;
  self->flags = 0;
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

void R_FileHandle_openForReading(R_FileHandle* self, char const* path) {
  R_FileHandle_close(self);
  self->fd = fopen(path, "rb");
  if (!self->fd) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
  self->flags |= Flags_OpenRead;
}

void R_FileHandle_openForWriting(R_FileHandle* self, char const* path) {
  R_FileHandle_close(self);
  self->fd = fopen(path, "wb");
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