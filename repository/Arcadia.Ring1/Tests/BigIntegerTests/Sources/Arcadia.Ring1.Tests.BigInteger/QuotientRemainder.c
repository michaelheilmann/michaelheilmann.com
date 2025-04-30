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

// Last modified: 2024-09-28

#include "Arcadia.Ring1.Tests.BigInteger/QuotientRemainder.h"

#include <stdio.h>

typedef struct Context {
  Arcadia_BigInteger* divisor;
  Arcadia_BigInteger* dividend;
  Arcadia_BigInteger* quotient;
  Arcadia_BigInteger* remainder;
  Arcadia_BigInteger* receivedQuotient;
  Arcadia_BigInteger* receivedRemainder;
} Context;

static inline void
Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64
  (
    Arcadia_Thread* thread,
    Context* context,
    Arcadia_Natural64Value quotient,
    Arcadia_Natural64Value remainder,
    Arcadia_Natural64Value dividend,
    Arcadia_Natural64Value divisor
  )
{
  fprintf(stdout, "dividend = %"PRIu64", divisor = %"PRIu64", quotient = %"PRIu64", remainder = %"PRIu64"\n", dividend, divisor, quotient, remainder);

  Arcadia_BigInteger_setNatural64(thread, context->dividend, dividend); 
  Arcadia_BigInteger_setNatural64(thread, context->divisor, divisor);
  Arcadia_Tests_assertTrue(thread, dividend == Arcadia_BigInteger_toNatural64(thread, context->dividend));
  Arcadia_Tests_assertTrue(thread, divisor == Arcadia_BigInteger_toNatural64(thread, context->divisor));

  Arcadia_BigInteger_setNatural64(thread, context->quotient, quotient);
  Arcadia_BigInteger_setNatural64(thread, context->remainder, remainder);
  Arcadia_Tests_assertTrue(thread, quotient == Arcadia_BigInteger_toNatural64(thread, context->quotient));
  Arcadia_Tests_assertTrue(thread, remainder == Arcadia_BigInteger_toNatural64(thread, context->remainder));

  Arcadia_BigInteger_divide3(thread, context->dividend, context->divisor, context->receivedQuotient, context->receivedRemainder);
  Arcadia_Tests_assertTrue(thread, quotient == Arcadia_BigInteger_toNatural64(thread, context->receivedQuotient));
  Arcadia_Tests_assertTrue(thread, remainder == Arcadia_BigInteger_toNatural64(thread, context->receivedRemainder));

  Arcadia_Tests_assertTrue(thread, Arcadia_Integer8Value_Literal(0) == Arcadia_BigInteger_compareTo(thread, context->receivedQuotient, context->quotient));
  Arcadia_Tests_assertTrue(thread, Arcadia_Integer8Value_Literal(0) == Arcadia_BigInteger_compareTo(thread, context->receivedRemainder, context->remainder));
};

typedef struct Range {
  Arcadia_Natural64Value start;
  Arcadia_Natural64Value end;
  Arcadia_Natural64Value step;
  Arcadia_Natural64Value current;
  Arcadia_BooleanValue done;
} Range;

void Range_init(Arcadia_Thread* thread, Range* range, Arcadia_Natural64Value start, Arcadia_Natural64Value end, Arcadia_Natural64Value step) {
  range->start = start;
  range->end = end;
  range->current = start;
  range->step = step;
  range->done = false;
  if (range->start != range->end && step == 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (range->start > range->end && step > 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (range->start > range->end) {
    if (range->current == range->start) {
      range->done = true;
    }
  } else /*if (range->start > range->end)*/ {
    if (range->current == range->end) {
      range->done = true;
    }
  }
}

Arcadia_Natural64Value Range_get(Arcadia_Thread* thread, Range* range) {
  if (range->done) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  return range->current;
}

void Range_next(Arcadia_Thread* thread, Range* range) {
  if (range->done) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_OperationInvalid);
    Arcadia_Thread_jump(thread);
  }
  if (range->start > range->end) {
    // decrease
    if (range->current == range->start) {
      range->done = true;
    }
    else if (range->current - range->end < range->step) {
      range->current = range->start;
    } else {
      range->current -= range->step;
    }
  } else /*if (range->start > range->end)*/ {
    // increase
    if (range->current == range->end) {
      range->done = true;
    }
    else if (range->end - range->current < range->step) {
      range->current = range->end;
    } else {
      range->current += range->step;
    }
  }
}

static void
Arcadia_Test_BigInteger_quotientRemainderFull
  (
    Arcadia_Thread* thread
  )
{
  Context context;
  context.dividend = Arcadia_BigInteger_create(thread);
  context.divisor = Arcadia_BigInteger_create(thread);
  context.quotient = Arcadia_BigInteger_create(thread);
  context.remainder = Arcadia_BigInteger_create(thread);
  context.receivedQuotient = Arcadia_BigInteger_create(thread);
  context.receivedRemainder = Arcadia_BigInteger_create(thread);

  Range dividendRange;
  Range_init(thread, &dividendRange, Arcadia_Natural64Value_Minimum, Arcadia_Natural64Value_Maximum, Arcadia_Natural64Value_Maximum >> 8);
  while (!dividendRange.done) {
    Arcadia_Natural64Value dividend = Range_get(thread, &dividendRange);
    Range divisorRange;
    Range_init(thread, &divisorRange, Arcadia_Natural64Value_Minimum + 1, Arcadia_Natural64Value_Maximum, Arcadia_Natural64Value_Maximum >> 8);
    while (!divisorRange.done) {
      Arcadia_Natural64Value divisor = Range_get(thread, &divisorRange);
      Arcadia_Natural64Value quotient = dividend / divisor;
      Arcadia_Natural64Value remainder = dividend % divisor;
      Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, quotient, remainder, dividend, divisor);
      Range_next(thread, &divisorRange);
    }
    Range_next(thread, &dividendRange);
  }
}

static void
Arcadia_Test_BigInteger_quotientRemainderRegression
  (
    Arcadia_Thread* thread
  )
{
  Context context;
  context.dividend = Arcadia_BigInteger_create(thread);
  context.divisor = Arcadia_BigInteger_create(thread);
  context.quotient = Arcadia_BigInteger_create(thread);
  context.remainder = Arcadia_BigInteger_create(thread);
  context.receivedQuotient = Arcadia_BigInteger_create(thread);
  context.receivedRemainder = Arcadia_BigInteger_create(thread);
  Arcadia_Natural64Value dividend, divisor;
  dividend = UINT32_MAX;
  divisor = UINT32_MAX * 0.3;
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
  dividend = UINT64_MAX;
  divisor = UINT64_MAX * 0.3;
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
  dividend = 72057594037927935;
  divisor = 1;
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
  dividend = Arcadia_Natural64Value_Literal(72057594037927935);
  divisor = Arcadia_Natural64Value_Literal(72057594037927936);
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
  dividend = Arcadia_Natural64Value_Literal(144115188075855870);
  divisor = Arcadia_Natural64Value_Literal(72057594037927936);
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
  dividend = Arcadia_Natural64Value_Literal(18446744073709551615);
  divisor = Arcadia_Natural64Value_Literal(18446744073709551615);
  Arcadia_Test_BigInteger_quotientRemainderTestFixtureNatural64(thread, &context, dividend / divisor, dividend % divisor, dividend, divisor);
}

void
Arcadia_Ring1_Tests_BigInteger_quotientRemainderOperations
  (
    Arcadia_Thread* thread
  )
{ 
  Arcadia_Test_BigInteger_quotientRemainderRegression(thread);
  Arcadia_Test_BigInteger_quotientRemainderFull(thread);
}
