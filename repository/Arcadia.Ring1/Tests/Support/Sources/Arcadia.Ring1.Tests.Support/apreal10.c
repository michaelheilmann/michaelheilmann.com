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

// Last modified: 2024-09-28

#include "Arcadia.Ring1.Tests.Support/apreal10.h"

// test
// - from literal
static void
testFromLiteral
  (
    Arcadia_Process* process
  )
{
  apreal10 a;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  apreal10_uninitialize(&a);
}

// test
// - initialize and
// - set i64
static void
testFromI64
  (
    Arcadia_Process* process
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }

  for (size_t i = 0; i < 63; ++i) {
    int64_t v = INT64_C(1) << i;
    if (apreal10_from_u64(&a, v)) {
      apreal10_uninitialize(&b);
      apreal10_uninitialize(&a);
      Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
      Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
    }
    if (apreal10_from_i64(&b, i)) {
      apreal10_uninitialize(&b);
      apreal10_uninitialize(&a);
      Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
      Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
    }
  }

  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}


// test
// - initialize and
// - set u64
static void
testFromU64
  (
    Arcadia_Process* process
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }

  for (size_t i = 0; i < 63; ++i) {
    uint64_t v = UINT64_C(1) << i;
    if (apreal10_from_u64(&a, v)) {
      apreal10_uninitialize(&b);
      apreal10_uninitialize(&a);
      Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
      Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
    }
    if (apreal10_from_u64(&b, i)) {
      apreal10_uninitialize(&b);
      apreal10_uninitialize(&a);
      Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
      Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
    }
  }

  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}

// test
// - 0 << 3 = 0
// - 0 >> 3 = 0
static void
testShift
  (
    Arcadia_Process* process
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_from_i64(&a, 0)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_from_i64(&b, 0)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }

  int result;

  // 0 << 3 = 0
  if (apreal10_multiply_p10(&a, 3)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_compare(&result, &a, &b)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (result) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }

  // 0 >> 3 = 0
  if (apreal10_divide_p10(&a, 3)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_compare(&result, &a, &b)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (result) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }

  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}

// test
// - set i64 and
// - copy
static void
testCopy
  (
    Arcadia_Process* process
  )
{
  apreal10 a, b;
  if (apreal10_initialize(&a)) {
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_initialize(&b)) {
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_from_i64(&a, INT64_MAX)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (apreal10_copy(&b, &a)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  int result;
  if (apreal10_compare(&result, &a, &b)) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  if (result) {
    apreal10_uninitialize(&b);
    apreal10_uninitialize(&a);
    Arcadia_Thread1_setStatus(Arcadia_Process_getThread(process), Arcadia_Status_TestFailed);
    Arcadia_Thread1_jump(Arcadia_Process_getThread(process));
  }
  apreal10_uninitialize(&b);
  apreal10_uninitialize(&a);
}

void
Arcadia_Ring1_Tests_Support_apreal10
  (
    Arcadia_Process* process
  )
{
  testFromU64(process);
  testFromI64(process);
  testCopy(process);
  testShift(process);
}
