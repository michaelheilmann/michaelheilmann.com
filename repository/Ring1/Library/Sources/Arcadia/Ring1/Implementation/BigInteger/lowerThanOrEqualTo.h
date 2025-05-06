#if !defined(ARCADIA_RING1_BIGINTEGER_LOWERTHANOREQUALTO_H_INCLUDED)
#define ARCADIA_RING1_BIGINTEGER_LOWERTHANOREQUALTO_H_INCLUDED

#if !defined(ARCADIA_RING1_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring1/Include.h` instead")
#endif

#include "Arcadia/Ring1/Implementation/Boolean.h"
#include "Arcadia/Ring1/Implementation/Integer16.h"
#include "Arcadia/Ring1/Implementation/Integer32.h"
#include "Arcadia/Ring1/Implementation/Integer64.h"
#include "Arcadia/Ring1/Implementation/Integer8.h"
#include "Arcadia/Ring1/Implementation/Natural16.h"
#include "Arcadia/Ring1/Implementation/Natural32.h"
#include "Arcadia/Ring1/Implementation/Natural64.h"
#include "Arcadia/Ring1/Implementation/Natural8.h"

typedef struct Arcadia_BigInteger Arcadia_BigInteger;
typedef Arcadia_BigInteger* Arcadia_BigIntegerValue;

// Get if this BigInteger is lower than or equal to another BigInteger.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  );

// Get if this BigInteger is lower than or equal to an Integer16.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  );

// Get if this BigInteger is lower than or equal to an Integer32.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  );

// Get if this BigInteger is lower than or equal to an Integer64.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  );

// Get if this BigInteger is lower than or equal to an Integer8.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToOrEqualToInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  );

// Get if this BigInteger is lower than a Natural16.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToOrEqualToNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  );

// Get if this BigInteger is lower than a Natural32.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToOrEqualToNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  );

// Get if this BigInteger is lower than a Natural64.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToOrEqualToNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  );

// Get if this BigInteger is lower than or equal to a Natural8.
Arcadia_BooleanValue
Arcadia_BigInteger_lowerThanOrEqualToOrEqualToNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  );

#endif // ARCADIA_RING1_BIGINTEGER_LOWERTHANOREQUALTO_H_INCLUDED
