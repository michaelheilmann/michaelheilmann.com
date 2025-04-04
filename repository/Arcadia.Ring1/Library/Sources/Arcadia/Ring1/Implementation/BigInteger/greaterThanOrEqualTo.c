#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/greaterThan.h"

#include "Arcadia/Ring1/Include.h"

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{ return Arcadia_BigInteger_compareTo(thread, self, other) >= Arcadia_Integer8Value_Literal(0); }

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger16(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger32(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural16(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural64(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}

Arcadia_BooleanValue
Arcadia_BigInteger_greaterThanOrEqualToNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, otherBigInteger, other);
  return Arcadia_BigInteger_greaterThanOrEqualTo(thread, self, otherBigInteger);
}
