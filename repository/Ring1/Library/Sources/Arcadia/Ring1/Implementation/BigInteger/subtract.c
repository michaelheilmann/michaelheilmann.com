#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/subtract.h"

#include "Arcadia/Ring1/Include.h"

void
Arcadia_BigInteger_negate
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self
  )
{
  if (self->sign) {
    self->sign = -self->sign;
  }
}

void
Arcadia_BigInteger_subtract3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  Arcadia_BigInteger* c = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, c, b);
  Arcadia_BigInteger_negate(thread, c);
  Arcadia_BigInteger_add3(thread, result, a, c);
}

void
Arcadia_BigInteger_subtract
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  Arcadia_BigInteger_subtract3(thread, self, self, other);
}

void
Arcadia_BigInteger_subtractInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger16(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger32(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural16(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural64(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_subtractNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, otherBigInteger, other);
  Arcadia_BigInteger_subtract(thread, self, otherBigInteger);
}
