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

// Last modified: 2024-09-01

#include "R/FileSystem.h"

#include "R.h" 

#define Flags_OpenRead (1)

#define Flags_OpenWrite (2)

static void R_FileSystem_visit(R_FileSystem* self);

static void R_FileSystem_finalize(R_FileSystem* self);

static void R_FileSystem_visit(R_FileSystem* self)
{/*Intentionally empty.*/}

static void R_FileSystem_finalize(R_FileSystem* self)
{/*Intentionally empty.*/}

void _R_FileSystem_registerType() {
  R_registerObjectType("R.FileSystem", sizeof("R.FileSystem") - 1, sizeof(R_FileSystem), &R_FileSystem_visit, &R_FileSystem_finalize);
}

R_FileSystem*
R_FileSystem_create
  (
  )
{
  R_FileSystem* self = R_allocateObject("R.FileSystem", sizeof("R.FileSystem") - 1, sizeof(R_FileSystem));
  self->dummy = 0;
  return self;
}

R_ByteBuffer*
R_FileSystem_getFileContents
  (
    R_FileSystem* self,
    char const* path
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create();
  R_FileHandle_openForReading(fileHandle, path);
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  char p[5012]; size_t n;
  do {
    R_FileHandle_read(fileHandle, p, 5012, &n);
    if (n > 0) {
      R_ByteBuffer_append_pn(byteBuffer, p, n);
    }
  } while (n > 0);
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
  return byteBuffer;
}

void
R_FileSystem_setFileContents
  (
    R_FileSystem* self,
    char const* path,
    R_ByteBuffer * contents
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create();
  R_FileHandle_openForWriting(fileHandle, path);
  R_SizeValue bytesToWrite = contents->sz,
              bytesWritten = 0;
  while (bytesToWrite > 0) {
    R_SizeValue bytesWrittenNow;
    R_FileHandle_write(fileHandle, contents->p + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
}

#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  #include <sys/stat.h>
#else
  #error("operating system not (yet) supported")
#endif


void
R_FileSystem_createDirectory
  (
    R_FileSystem* self,
    char const* path
  )
{
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  if (FALSE == CreateDirectory(path, NULL)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  if (-1 == mkdir(pathp, 0777)) {
    R_setStatus(R_Status_FileSystemOperationFailed);
    R_jump();
  }
#else
  #error("operating system not (yet) supported")
#endif  
}