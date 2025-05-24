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

#include "Tools/RyuLookupTablesGenerator/generateReal32Table.h"

static const Arcadia_SizeValue PositionsTableSize = 47;
static const Arcadia_SizeValue InverseTableSize = 55;

static const Arcadia_SizeValue Pow5BitCount = 61; // max 63
static const Arcadia_SizeValue Pow5InverseBitCount = 59; // max 63

#include <stdio.h>

void
Arcadia_Tools_RyuLookupTableGenerator_generateReal32Table
  (
    Arcadia_Thread* thread
  )
{
  fprintf(stdout, "#define Pow5BitCount %zu\n", Pow5BitCount);
  fprintf(stdout, "#define Pow5BitCount %zu\n", Pow5InverseBitCount);
}
