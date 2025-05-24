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
#include <string.h>
#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Tools/RyuLookupTablesGenerator/generateReal32Table.h"
#include "Tools/RyuLookupTablesGenerator/generateReal64Table.h"
#include "Tools/RyuLookupTablesGenerator/Configure.h"

// `floor(2^k /5^q) + 1` and `floor(5^(?e2?q) /2k)` 

#define FLOAT64_POS_TABLE_SIZE 326
// The C version has two code paths, one of which requires an additional entry here.
#define FLOAT64_NEG_TABLE_SIZE 342

// We intentionally choose these to be larger than or equal to the float equivalent + 64.
#define FLOAT64_POW5_BITCOUNT 125 // max 127
#define FLOAT64_POW5_INV_BITCOUNT 125 // max 127

// number of bits required for 5^k
#define FLOAT32_POW5_BITCOUNT 61 // max 63
// number of bits required for 1  / 5^k
#define FLOAT32_POW5_INV_BITBOUND 59 // max 63

static Arcadia_BigInteger* g_one = NULL;
static Arcadia_BigInteger* g_t1 = NULL;

static Arcadia_BigInteger* invMultiplier(Arcadia_Thread* thread, Arcadia_Integer32Value i) {
  // 5^i
  Arcadia_BigInteger* pow = Arcadia_BigInteger_create(thread);
  if (i < 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BigInteger_setPowerOfFiveNatural32(thread, pow, i);
  // length of 5^i in binary = ceil(log_2(5^i))
  Arcadia_Integer32Value pow5len = (Arcadia_Integer32Value)Arcadia_BigInteger_getBitLength(thread, pow);
  // We want floor(log_2(5^i)) here, which is ceil(log_2(5^i)) - 1 (no power of 5 is a power of 2).
  Arcadia_Integer32Value j = pow5len - 1 + FLOAT64_POW5_INV_BITCOUNT;
  // [2^j / 5^i] + 1 = [2^(floor(log_2(5^i)) + POW5_INV_BITCOUNT) / 5^i] + 1
  // By construction, this will have approximately POW5_INV_BITCOUNT + 1 bits.
  Arcadia_BigInteger_setPowerOfTwoNatural32(thread, g_t1, j);
  Arcadia_BigInteger* inv = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, inv, g_one);
  Arcadia_BigInteger_multiply(thread, inv, g_t1);
  Arcadia_BigInteger_divide(thread, inv, pow);
  Arcadia_BigInteger_add(thread, inv, g_one);
  if (Arcadia_BigInteger_getBitLength(thread, inv) > FLOAT64_POW5_INV_BITCOUNT + 1) {
    fprintf(stderr, "result is longer than expected\n");
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return inv;
}

static void onNotifyDestroy() {

}

void
main1
  (
    Arcadia_Thread* thread,
    int argc,
    char** argv
  )
{
  g_t1 = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfTwoNatural8(thread, g_t1, 64);
  g_one = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, g_one, 1);

  Arcadia_BigInteger* MASK64 = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_multiply3(thread, MASK64, g_one, g_t1);
  Arcadia_BigInteger_subtract(thread, MASK64, g_one);

  //
  Arcadia_List* largeInvTable = Arcadia_List_create(thread);
  for (int i = 0; i < FLOAT64_NEG_TABLE_SIZE; i++) {
    Arcadia_List_insertBackBigIntegerValue(thread, largeInvTable, invMultiplier(thread, i));
  }

  //
  int mulTableSize = 26;
  Arcadia_List* smallInvTable = Arcadia_List_create(thread);
  for (int i = 0; i < (FLOAT64_NEG_TABLE_SIZE + mulTableSize - 1) / mulTableSize + 1; i++) {
    Arcadia_List_insertBackBigIntegerValue(thread, smallInvTable, invMultiplier(thread, ((FLOAT64_NEG_TABLE_SIZE + mulTableSize - 1) / mulTableSize + 1) * i));
  }

  //
  g_one = NULL;
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_Thread* thread = Arcadia_Process_getThread(process);
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(thread, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(thread);
  Arcadia_Status status = Arcadia_Thread_getStatus(thread);
  thread = NULL;
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
