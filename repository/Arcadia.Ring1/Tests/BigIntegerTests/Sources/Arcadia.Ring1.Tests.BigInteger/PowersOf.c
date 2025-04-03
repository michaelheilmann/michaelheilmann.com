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

#include "Arcadia.Ring1.Tests.BigInteger/PowersOf.h"

static inline Arcadia_Value
Arcadia_Value_fromBigIntegerValue
  (
    Arcadia_BigIntegerValue v
  )
{
  Arcadia_Value w = Arcadia_Value_Initializer();
  Arcadia_Value_setBigIntegerValue(&w, v);
  return w;
}

#define Test_Op_multiply (1)

static inline void
Arcadia_Test_BigInteger_assertPowersOf
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value operation,
    Arcadia_Integer64Value power
  )
{
  Arcadia_BigInteger* leftOperandBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfFiveNatural64(thread, leftOperandBigInteger, power);
  Arcadia_Value leftOperandValue = Arcadia_Value_fromBigIntegerValue(leftOperandBigInteger);
  
  Arcadia_BigInteger* rightOperandBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfTwoNatural64(thread, rightOperandBigInteger, power);
  Arcadia_Value rightOperandValue = Arcadia_Value_fromBigIntegerValue(rightOperandBigInteger);
  
  Arcadia_BigInteger* expectedResultBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setPowerOfTenNatural64(thread, expectedResultBigInteger, power);
  Arcadia_Value expectedResultValue = Arcadia_Value_fromBigIntegerValue(expectedResultBigInteger);

  switch (operation) {
    case Test_Op_multiply: {
      Arcadia_BigInteger* receivedResultBigInteger = Arcadia_BigInteger_create(thread);
      Arcadia_BigInteger_multiply3(thread, receivedResultBigInteger, leftOperandBigInteger, rightOperandBigInteger);
      Arcadia_Tests_assertTrue(thread, Arcadia_Integer8Value_Literal(0) == Arcadia_BigInteger_compareTo(thread, receivedResultBigInteger, expectedResultBigInteger));
    } break;
    default: {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    } break;
  }
};

void
Arcadia_Ring1_Tests_BigInteger_powersOfOperations
  (
    Arcadia_Thread* thread
  )
{
  typedef struct Test {
    int operation;
    Arcadia_Natural64Value a;
  } Test;
  static const Test tests[] = {
    { Test_Op_multiply, 0 },
    { Test_Op_multiply, 1 },
    { Test_Op_multiply, 7 },
    { Test_Op_multiply, 24 },
    { Test_Op_multiply, 40 },
    { Test_Op_multiply, 1024 },
    { Test_Op_multiply, 5012 },
    { Test_Op_multiply, 5012*8 },
  };
  static const Arcadia_SizeValue numberOfTests = sizeof(tests) / sizeof(Test);
  for (Arcadia_SizeValue i = 0, n = numberOfTests; i < n; ++i) {
    const Test* test = &(tests[i]);
    Arcadia_Test_BigInteger_assertPowersOf(thread, test->operation, test->a);
  }
}
