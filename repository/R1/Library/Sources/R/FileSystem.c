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

// Last modified: 2024-10-07

#include "R/FileSystem.h"

#include "R/FileHandle.h"
#include "R/FilePath.h"
#include "R/Object.h"
#include "R/String.h"

#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  #define WIN32_LEAN_AND_MEAN
  #include <Windows.h> // GetFileAttributes
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  #include <sys/stat.h> // stat
  #include <errno.h> // errno
  #include <unistd.h> // getcwd
  #include <linux/limits.h> // PATH_MAX
#else
  #error("operating system not (yet) supported")
#endif

#include "Arms.h"

static void
R_FileSystem_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  );

static void
R_FileSystem_visit
  (
    Arcadia_Process* process,
    R_FileSystem* self
  );

static void
R_FileSystem_destruct
  (
    Arcadia_Process* process,
    R_FileSystem* self
  );

static const R_ObjectType_Operations _objectTypeOperations = {
  .construct = &R_FileSystem_constructImpl,
  .destruct = &R_FileSystem_destruct,
  .visit = &R_FileSystem_visit,
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

Rex_defineObjectType(u8"R.FileSystem", R_FileSystem, u8"R.Object", R_Object, &_typeOperations);

static void
R_FileSystem_constructImpl
  (
    Arcadia_Process* process,
    R_Value* self,
    Arcadia_SizeValue numberOfArgumentValues,
    R_Value* argumentValues
  )
{
  R_FileSystem* _self = R_Value_getObjectReferenceValue(self);
  Arcadia_TypeValue _type = _R_FileSystem_getType(process);
  {
    R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void} };
    Rex_superTypeConstructor(process, _type, self, 0, &argumentValues[0]);
  }
  R_Object_setType((R_Object*)_self, _type);
}

static void
R_FileSystem_visit
  (
    Arcadia_Process* process,
    R_FileSystem* self
  )
{/*Intentionally empty.*/}

static void
R_FileSystem_destruct
  (
    Arcadia_Process* process,
    R_FileSystem* self
  )
{/*Intentionally empty.*/}

R_FileSystem*
R_FileSystem_create
  (
    Arcadia_Process* process
  )
{
  R_Value argumentValues[] = { {.tag = R_ValueTag_Void, .voidValue = Arcadia_VoidValue_Void } };
  R_FileSystem* self = R_allocateObject(process, _R_FileSystem_getType(process), 0, &argumentValues[0]);
  return self;
}

R_ByteBuffer*
R_FileSystem_getFileContents
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create(process, self);
  R_FileHandle_openForReading(process, fileHandle, path);
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create(process);
  char p[5012]; size_t n;
  do {
    R_FileHandle_read(process, fileHandle, p, 5012, &n);
    if (n > 0) {
      R_ByteBuffer_append_pn(process, byteBuffer, p, n);
    }
  } while (n > 0);
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
  return byteBuffer;
}

void
R_FileSystem_setFileContents
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path,
    R_ByteBuffer * contents
  )
{
  R_FileHandle* fileHandle = R_FileHandle_create(process, self);
  R_FileHandle_openForWriting(process, fileHandle, path);
  Arcadia_SizeValue bytesToWrite = contents->sz,
              bytesWritten = 0;
  while (bytesToWrite > 0) {
    Arcadia_SizeValue bytesWrittenNow;
    R_FileHandle_write(process, fileHandle, contents->p + bytesWritten, bytesToWrite, &bytesWrittenNow);
    bytesWritten += bytesWrittenNow;
    bytesToWrite -= bytesWrittenNow;
  }
  R_FileHandle_close(fileHandle);
  fileHandle = NULL;
}

Arcadia_BooleanValue
R_FileSystem_regularFileExists
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_String* nativePathString = R_FilePath_toNative(process, path);
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(R_String_getBytes(nativePathString));

  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
         !(dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(R_String_getBytes(nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
      } break;
    };
    return Arcadia_BooleanValue_False;
  }
  return S_IFREG == (stat.st_mode & S_IFMT) || S_IFLNK == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

Arcadia_BooleanValue
R_FileSystem_directoryFileExists
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_String* nativePathString = R_FilePath_toNative(process, path);
#if R_Configuration_OperatingSystem_Windows == R_Configuration_OperatingSystem
  DWORD dwFileAttributes = GetFileAttributes(R_String_getBytes(nativePathString));
  return (dwFileAttributes != INVALID_FILE_ATTRIBUTES);
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  struct stat stat;
  if(-1 == lstat(R_String_getBytes(nativePathString), &stat)) {
    switch (errno) {
      case EOVERFLOW:
      case ENOMEM: {
        Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
        Arcadia_Process_jump(process);
      } break;
    };
    return Arcadia_BooleanValue_False;
  }
  return S_IFDIR == (stat.st_mode & S_IFMT);
#else
  #error("environment not (yet) supported")
#endif
}

void
R_FileSystem_createDirectory
  (
    Arcadia_Process* process,
    R_FileSystem* self,
    R_FilePath* path
  )
{
  R_String* nativePath = R_FilePath_toNative(process, path);
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  if (FALSE == CreateDirectory(R_String_getBytes(nativePath), NULL)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
#elif R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Linux
  if (-1 == mkdir(R_String_getBytes(nativePath), 0777)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_FileSystemOperationFailed);
    Arcadia_Process_jump(process);
  }
#else
  #error("operating system not (yet) supported")
#endif
}

R_FilePath*
R_FileSystem_getWorkingDirectory
  (
    Arcadia_Process* process,
    R_FileSystem* self
  )
{
#if R_Configuration_OperatingSystem == R_Configuration_OperatingSystem_Windows
  DWORD dwBufferSize = GetCurrentDirectory(0, NULL);
  if (0 == dwBufferSize) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  char* pBuffer = NULL;
  if (Arms_MemoryManager_allocate(Arms_getSlabMemoryManager(), &pBuffer, dwBufferSize)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_AllocationFailed);
    Arcadia_Process_jump(process);
  }
  if (!GetCurrentDirectory(dwBufferSize, pBuffer)) {
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  R_JumpTarget jumpTarget;
  Arcadia_Process_pushJumpTarget(process, &jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    R_FilePath* filePath = R_FilePath_parseWindows(process, pBuffer, dwBufferSize - 1);
    Arcadia_Process_popJumpTarget(process);
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    return filePath;
  } else {
    Arcadia_Process_popJumpTarget(process);
    Arms_MemoryManager_deallocate(Arms_getSlabMemoryManager(), pBuffer);
    pBuffer = NULL;
    Arcadia_Process_jump(process);
  }
#elif R_Configuration_OperatingSystem_Linux == R_Configuration_OperatingSystem
  c_static_assert(PATH_MAX < Arcadia_SizeValue_Maximum, "environment not (yet) supported");
  #define CWD_CAPACITY (PATH_MAX+1)
  char cwd[CWD_CAPACITY];
  if (!getcwd(cwd, CWD_CAPACITY)) {
    Arcadia_Process_setStatus(process, Arcadia_Status_EnvironmentFailed);
    Arcadia_Process_jump(process);
  }
  R_FilePath* filePath = R_FilePath_parseUnix(cwd, c_strlen(cwd));
  return filePath;
#else
  #error("environment not (yet) supported")
#endif
}
