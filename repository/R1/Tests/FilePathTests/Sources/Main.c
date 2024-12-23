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

#include <stdlib.h>

#include "R.h"
#include <string.h>

/// @todo Add to R's test utilities.
#define R_Test_assert(result) \
  if (!(result)) { \
    R_setStatus(R_Status_TestFailed); \
    R_jump(); \
  }

static void checkNormalized(char const* p, char const* q) {
  R_FilePath* filePath = R_FilePath_parseNative(p, strlen(p));
  R_String* filePathString = R_FilePath_toNative(filePath);
  if (R_String_getNumberOfBytes(filePathString) != strlen(q) + 1) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
  if (memcmp(R_String_getBytes(filePathString), q, strlen(q))) {
    R_setStatus(R_Status_TestFailed);
    R_jump();
  }
}

static void normalizationTests() {
  checkNormalized("Hello/..", ".");
  checkNormalized(".", ".");
  checkNormalized("./", ".");
}

static bool safeExecute(void (*f)()) {
  bool result = true;
  R_Status status = R_startup();
  if (status) {
    result = false;
    return result;
  }
  R_JumpTarget jumpTarget;
  R_pushJumpTarget(&jumpTarget);
  if (R_JumpTarget_save(&jumpTarget)) {
    (*f)();
  } else {
    result = false;
  }
  R_popJumpTarget();
  status = R_shutdown();
  if (status) {
    result = false;
  }
  return result;
}

int main(int argc, char **argv) {
  if (!safeExecute(&normalizationTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
