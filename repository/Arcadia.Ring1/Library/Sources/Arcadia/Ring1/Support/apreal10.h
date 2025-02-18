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

// Last modified: 2025-01-01

#if !defined(ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED)
#define ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include "Arcadia/Ring1/Support/apint10.h"
#include "Arcadia/Ring1/Support/ieee754.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef uint8_t digit_t;
#define DIGIT_MIN UINT8_C(0)
#define DIGIT_MAX (DIGIT_BASE-1)
#define DIGIT_BASE 10

#define BIG_DECIMAL_MAX_CP (UINT32_MAX / sizeof(digit_t))

typedef uint16_t double_digit_t;

typedef struct apreal10 {
  // the integer
  apint10 integer;
  // the base 10 exponent
  // epx = 0 means the value of this apdec is integer
  // exp > 0 means the value of this apfloat10 is integer * 10^|exp|
  // exp < 0 means the value of this apfloat10 is integer / 10^|exp| 
  int32_t exp;

} apreal10;

// initialize to 0
int
apreal10_initialize
  (
    apreal10* this
  );

int
apreal10_uninitialize
  (
    apreal10* this
  );

int
apreal10_copy
  (
    apreal10* this,
    apreal10* other
  );

// negative = true if x is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_i16
  (
    apreal10* this,
    int16_t x
  );

// negative = true if x is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_i32
  (
    apreal10* this,
    int32_t x
  );

// negative = true if x is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_i64
  (
    apreal10* this,
    int64_t x
  );

// negative = true if x is negative, false otherwise
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_i8
  (
    apreal10* this,
    int8_t x
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_u16
  (
    apreal10* this,
    uint16_t x
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_u32
  (
    apreal10* this,
    uint32_t x
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_u64
  (
    apreal10* this,
    uint64_t x
  );

// negative = false
// numberOfDigits = n
// exp = n
// where n is the number of digits
int
apreal10_from_u8
  (
    apreal10* this,
    uint8_t x
  );

// parse this apreal10 from an UTF8 decimal real literal string
int
apreal10_from_literal
  (
    apreal10* this,
    const uint8_t* p,
    uint32_t n
  );

int
apreal10_compare_magnitudes
  (
    int* result,
    apreal10* this,
    apreal10* other
  );

int
apreal10_compare
  (
    int* result,
    apreal10* this,
    apreal10* other
  );

// d = d * 10^e, e >= 0
int
apreal10_multiply_p10
  (
    apreal10* this,
    uint64_t e
  );

// d = d / 10^e, e >= 0
int
apreal10_divide_p10
  (
    apreal10* this,
    uint64_t e
  );

#endif // ARCADIA_RING1_SUPPORT_APREAL10_H_INCLUDED
