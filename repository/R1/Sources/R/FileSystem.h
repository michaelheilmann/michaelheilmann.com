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

#if !defined(R_FILESYSTEM_H_INCLUDED)
#define R_FILESYSTEM_H_INCLUDED

#include "R/Configure.h"
#include "R/Boolean.h"
#include "R/ByteBuffer.h"
#include "R/Natural8.h"
#include "R/Size.h"

#include <stdio.h>

typedef struct R_FileSystem R_FileSystem;

void _R_FileSystem_registerType();

struct R_FileSystem {
  int dummy;
};

// https://michaelheilmann.com/repository/R1/#r-filesystem-create
R_FileSystem*
R_FileSystem_create
  (
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-getfilecontents
R_ByteBuffer*
R_FileSystem_getFileContents
  (
    R_FileSystem* self,
    char const* path
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-setfilecontents
void
R_FileSystem_setFileContents
  (
    R_FileSystem* self,
    char const* path,
    R_ByteBuffer * contents
  );

// https://michaelheilmann.com/repository/R1/#r-filesystem-createdirectory
void
R_FileSystem_createDirectory
  (
    R_FileSystem* self,
    char const* path
  );

#endif // R_FILESYSTEM_H_INCLUDED