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

// Last modified: 2024-09-20

#include "Arcadia/Ring1/Support/apreal10.h"

#include <stdbool.h>
#include <malloc.h>
#include <string.h>

int
apreal10_initialize
  (
    apreal10* this
  )
{
  if (apint10_initialize(&this->integer)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
apreal10_uninitialize
  (
    apreal10* this
  )
{
  apint10_uninitialize(&this->integer);
  return 0;
}

int
apreal10_copy
  (
    apreal10* this,
    apreal10* other
  )
{
  if (!this || !other) {
    return 1;
  }
  if (this == other) {
    return 0;
  }
  if (apint10_copy(&this->integer, &other->integer)) {
    return 1;
  }
  this->exp = other->exp;
  return 0;
}

int
apreal10_from_i16
  (
    apreal10* this,
    int16_t x
  )
{ return apreal10_from_i64(this, x); }

int
apreal10_from_i32
  (
    apreal10* this,
    int32_t x
  )
{ return apreal10_from_i64(this, x); }

int
apreal10_from_i64
  (
    apreal10* this,
    int64_t x
  )
{
  if (apint10_from_int64(&this->integer, x)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
apreal10_from_i8
  (
    apreal10* this,
    int8_t x
  )
{ return apreal10_from_i64(this, x); }

int
apreal10_from_u16
  (
    apreal10* this,
    uint16_t x
  )
{ return apreal10_from_u64(this, x); }

int
apreal10_from_u32
  (
    apreal10* this,
    uint32_t x
  )
{ return apreal10_from_u64(this, x); }

int
apreal10_from_u64
  (
    apreal10* this,
    uint64_t x
  )
{
  if (apint10_from_uint64(&this->integer, x)) {
    return 1;
  }
  this->exp = 0;
  return 0;
}

int
apreal10_from_u8
  (
    apreal10* this,
    uint8_t x
  )
{ return apreal10_from_u64(this, x); }

int
apreal10_from_literal
  (
    apreal10* this,
    const uint8_t* p,
    uint32_t n
  )
{
  apint10 mantissa, exponent, shiftExponent;
  if (apint10_initialize(&mantissa)) {
    return 1;
  }
  if (apint10_initialize(&exponent)) {
    apint10_uninitialize(&mantissa);
    return 1;
  }
  if (apint10_initialize(&shiftExponent)) {
    apint10_uninitialize(&exponent);
    apint10_uninitialize(&mantissa);
    return 1;
  }
  
#define START (253)

#define END (254)

#define ERROR (255)

#define NEXT() \
    if (s.symbol != END && s.symbol != ERROR) { \
      if (s.current == s.end) { \
        s.symbol = END; \
      } else { \
        s.symbol = *s.current; \
        s.current++; \
      } \
    }

#define IS(X) ((X) == s.symbol)
#define ISRANGE(X, Y) ((X) <= s.symbol && s.symbol <= (Y))

  struct STATE {
    const uint8_t* start;
    const uint8_t* end;
    const uint8_t* current;
    uint32_t symbol;
  };

  struct STATE s = { .start = p, .end = p + n, .current = p, .symbol = START };

  bool exponentNegative = false;
  bool mantissaNegative = false;
  if (IS('+')) {
    NEXT();
  } else if (IS('-')) {
    mantissaNegative = true;
    NEXT();
  }
  if (IS('.')) {
    NEXT();
    if (!ISRANGE('0', '9')) {
      goto SyntaxError;
    }
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10(&mantissa, 1)) {
        goto AllocationError;
      }
      if (apint10_add_u8(&mantissa, digit)) {
        goto AllocationError;
      }
      if (apint10_subtract_u8(&shiftExponent, 1)) {
        goto AllocationError;
      }
    } while (ISRANGE('0', '9'));
  } else if (ISRANGE('0', '9')) {
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10(&mantissa, 1)) {
        goto AllocationError;
      }
      if (apint10_add_u8(&mantissa, digit)) {
        goto AllocationError;
      }
    } while (ISRANGE('0', '9'));
    if (IS('.')) {
      NEXT();
      while (ISRANGE('0', '9')) {
        uint8_t digit = s.symbol - '0';
        if (apint10_multiply_p10(&mantissa, 1)) {
          goto AllocationError;
        }
        if (apint10_add_u8(&mantissa, digit)) {
          goto AllocationError;
        }
        if (apint10_subtract_u8(&shiftExponent, 1)) {
          goto AllocationError;
        }
      }
    }
  } else {
    goto SyntaxError;
  }
  if (apint10_negate(&mantissa)) {
    goto AllocationError;
  }
  if (IS('e') || IS('E')) {
    NEXT();
    if (IS('+')) {
      NEXT();
    } else if (IS('-')) {
      exponentNegative = true;
      NEXT();
    }
    if (!ISRANGE('0', '9')) {
      goto SyntaxError;
    }
    do {
      uint8_t digit = s.symbol - '0';
      if (apint10_multiply_p10(&exponent, 1)) {
        goto AllocationError;
      }
      if (apint10_add_u8(&exponent, digit)) {
        goto AllocationError;
      }
    } while (ISRANGE('0', '9'));
    if (apint10_negate(&exponent)) {
      goto AllocationError;
    }
  }

  if (apint10_add(&exponent, &shiftExponent)) {
    goto AllocationError;
  }

#undef IS
#undef NEXT
#undef ERROR
#undef END
#undef START

  apint10_uninitialize(&shiftExponent);
  apint10_uninitialize(&exponent);
  apint10_uninitialize(&mantissa);

  return 0;
AllocationError:
SyntaxError:
  apint10_uninitialize(&shiftExponent);
  apint10_uninitialize(&exponent);
  apint10_uninitialize(&mantissa);
  return 1;
}

int
apreal10_compare_magnitudes
  (
    int* result,
    apreal10* this,
    apreal10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare_magnitudes(result, &this->integer, &other->integer);
}

int
apreal10_compare
  (
    int* result,
    apreal10* this,
    apreal10* other
  )
{
  if (!result || !this || !other) {
    return 1;
  }
  /// TODO: Do not forget to take the exponents into account!
  return apint10_compare(result, &this->integer, &other->integer);
}

int
apreal10_multiply_p10
  (
    apreal10* this,
    uint64_t e
  )
{
  return apint10_multiply_p10(&this->integer, e);
}

int
apreal10_divide_p10
  (
    apreal10* this,
    uint64_t e
  )
{
  return apint10_divide_p10(&this->integer, e);
}
