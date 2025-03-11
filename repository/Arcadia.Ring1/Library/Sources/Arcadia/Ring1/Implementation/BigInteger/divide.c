#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/divide.h"

#include "Arcadia/Ring1/Include.h"
#include <assert.h>

// "goes into"
void
Arcadia_BigInteger_divide3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  // Special case: a is zero; result is zero.
  if (Arcadia_BigInteger_isZero(thread, a)) {
    Arcadia_BigInteger_setZero(thread, result);
    return;
  }
  // Special case: b is zero; raise a "division by zero" error.
  if (Arcadia_BigInteger_isZero(thread, b)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
    Arcadia_Thread_jump(thread);
  }
  // Both a and b are non-zero.
  assert(!Arcadia_BigInteger_isZero(thread, a));
  assert(!Arcadia_BigInteger_isZero(thread, b));

  // This will be zero under integer division.
  if (a->numberOfLimps < b->numberOfLimps) {
    Arcadia_BigInteger_setZero(thread, result);
    return;
  }
}

void
Arcadia_BigInteger_divide
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  Arcadia_BigInteger_divide3(thread, self, self, other);
}

void
Arcadia_BigInteger_divideInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger16(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger32(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural16(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural64(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_divideNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, otherBigInteger, other);
  Arcadia_BigInteger_divide(thread, self, otherBigInteger);
}
