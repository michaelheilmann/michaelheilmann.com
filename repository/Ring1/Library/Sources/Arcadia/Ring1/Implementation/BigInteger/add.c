#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/BigInteger/add.h"

#include "Arcadia/Ring1/Include.h"
#include <assert.h>

void
Arcadia_BigInteger_add3
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* result,
    Arcadia_BigInteger* a,
    Arcadia_BigInteger* b
  )
{
  // Special case: a is zero; result is b.
  if (Arcadia_BigInteger_isZero(thread, a)) {
    Arcadia_BigInteger_copy(thread, result, b);
    return;
  }
  // Special case: b is zero; result is a.
  if (Arcadia_BigInteger_isZero(thread, b)) {
    Arcadia_BigInteger_copy(thread, result, a);
    return;
  }
  // Both a and b are non-zero.
  assert(!Arcadia_BigInteger_isZero(thread, a));
  assert(!Arcadia_BigInteger_isZero(thread, b));

  if (a->sign == b->sign) {
    // a and b have the same sign and are non-zero.
    // Strategy: Add their magnitudes.

    // Determine which operand has the smaller length.
    Arcadia_BigInteger* large = a->numberOfLimps < b->numberOfLimps ? b : a;
    Arcadia_BigInteger* small = a->numberOfLimps < b->numberOfLimps ? a : b;

    Arcadia_SizeValue largeLength = large->numberOfLimps;
    Arcadia_SizeValue smallLength = small->numberOfLimps;

    // The output will be at least as long a the largest input.
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &result->limps, sizeof(Hidden(BigInteger_Limp)) * largeLength);
    result->numberOfLimps = largeLength;

    uint64_t carry = 0;
    Arcadia_SizeValue index = 0;

    // Sum over the blocks that exists in both operands.
    while (index < smallLength) {
      uint64_t sum = carry + large->limps[index] + small->limps[index];
      carry = sum >> 32;
      result->limps[index] = (uint32_t)sum;
      index++;
    }
    // Sum over the limps that only exist in the large operands.
    while (index < largeLength) {
      uint64_t sum = carry + large->limps[index];
      carry = sum >> 32;
      result->limps[index] = (uint32_t)sum;
      index++;
    }

    if (carry) {
      // If there is stil a cary, we must append a limp.
      Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &result->limps, sizeof(Hidden(BigInteger_Limp)) * (result->numberOfLimps + 1));
      result->limps[index] = carry;
      result->numberOfLimps++;
    }
    // Also use the sign of the operands.
    result->sign = a->sign;
  } else {
    // a and b have different signs and are non-zero.
    // Strategy:
    // - Subtract the smaller magnitude from the larger magnitude.
    // - Use the sign of the larger magnitude.
    // - If the difference is 0, then set the sign to 0.
    Arcadia_BigInteger* large = a;
    Arcadia_BigInteger* small = b;
    if (Arcadia_BigInteger_compareByMagnitudeTo(thread, large, small) < 0) {
      Arcadia_swapPointer(thread, &large, &small);
    }

    Arcadia_SizeValue largeLength = large->numberOfLimps;
    Arcadia_SizeValue smallLength = small->numberOfLimps;

    // The output will be at least as long a the largest input.
    Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &result->limps, sizeof(Hidden(BigInteger_Limp)) * largeLength);
    result->numberOfLimps = largeLength;

    // Invariant magnitude(large) >= magnitude(small).
    uint64_t carry = 0;
    Arcadia_SizeValue index = 0;

    // Difference over the blocks that exists in both operands.
    while (index < smallLength) {
      uint64_t x = large->limps[index];
      uint64_t y = small->limps[index] + carry;
      carry = (y < carry);
      carry += (x < y);
      result->limps[index] = x < y ? UINT32_MAX + x - y : x - y;
      index++;
    }
    // Diference over the limps that only exist in the large operands.
    while (index < largeLength) {
      uint64_t x = large->limps[index];
      uint64_t y = carry;
      carry += (x < y);
      result->limps[index] = x < y ? UINT32_MAX + x - y : x - y;
      index++;
    }
    if (carry) {
      // If there is stil a cary, we must append a limp.
      Arcadia_Process_reallocateUnmanaged(Arcadia_Thread_getProcess(thread), &result->limps, sizeof(Hidden(BigInteger_Limp)) * (result->numberOfLimps + 1));
      result->limps[index] = carry;
      result->numberOfLimps++;
    }

    while (result->numberOfLimps > 1 && !result->limps[result->numberOfLimps - 1]) {
      result->numberOfLimps--;
    }

    // Also use the sign of the larger operand.
    result->sign = result->numberOfLimps == 1 && result->limps[0] == UINT32_C(0) ? UINT8_C(0) : large->sign;
  }

}

void
Arcadia_BigInteger_add
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_BigInteger* other
  )
{
  Arcadia_BigInteger_add3(thread, self, self, other);
}

void
Arcadia_BigInteger_addInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger16(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger32(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger64(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Integer8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural16Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural16(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural32Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural32(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural64Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural64(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}

void
Arcadia_BigInteger_addNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_BigInteger* self,
    Arcadia_Natural8Value other
  )
{
  Arcadia_BigInteger* otherBigInteger = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setNatural8(thread, otherBigInteger, other);
  Arcadia_BigInteger_add(thread, self, otherBigInteger);
}
