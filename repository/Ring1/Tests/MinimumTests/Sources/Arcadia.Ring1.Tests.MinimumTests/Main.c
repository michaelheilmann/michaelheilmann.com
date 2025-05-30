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

#include <stdlib.h>

#include "Arcadia/Ring1/Include.h"

static void
minimumTests
  (
    Arcadia_Thread* thread
  )
{
#define Do(Type, Suffix) \
  Arcadia_Tests_assertTrue(thread, Type##Value_Minimum == Arcadia_minimum##Suffix##Value((thread), Type##Value_Minimum, Type##Value_Maximum)); \
  Arcadia_Tests_assertTrue(thread, Type##Value_Minimum == Arcadia_minimum##Suffix##Value((thread), Type##Value_Maximum, Type##Value_Minimum)); \
  Arcadia_Tests_assertTrue(thread, Type##Value_Minimum == Arcadia_minimum##Suffix##Value((thread), Type##Value_Literal(0), Type##Value_Minimum)); \
  Arcadia_Tests_assertTrue(thread, Type##Value_Minimum == Arcadia_minimum##Suffix##Value((thread), Type##Value_Minimum, Type##Value_Literal(0)));

  Do(Arcadia_Integer8, Integer8);
  Do(Arcadia_Integer16, Integer16);
  Do(Arcadia_Integer32, Integer32);
  Do(Arcadia_Integer64, Integer64);

  Do(Arcadia_Natural8, Natural8);
  Do(Arcadia_Natural16, Natural16);
  Do(Arcadia_Natural32, Natural32);
  Do(Arcadia_Natural64, Natural64);

  Do(Arcadia_Size, Size);

#undef Do
}

int
main
  (
    int argc,
    char **argv
  )
{
  if (!Arcadia_Tests_safeExecute(&minimumTests)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
