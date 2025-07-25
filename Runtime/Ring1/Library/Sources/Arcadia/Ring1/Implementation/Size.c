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

#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Size.h"

#include "Arcadia/Ring1/Implementation/_defineScalarType.h"
#include "Arcadia/Ring1/Include.h"

static void
add
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
divide
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isGreaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isGreaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
identical
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isLowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isLowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
multiply
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
negate
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static void
subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  );

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .add = &add,
  .divide = &divide,
  .equalTo = &isEqualTo,
  .greaterThan = &isGreaterThan,
  .greaterThanOrEqualTo = &isGreaterThanOrEqualTo,
  .hash = &hash,
  .identical = &identical,
  .lowerThan = &isLowerThan,
  .lowerThanOrEqualTo = &isLowerThanOrEqualTo,
  .multiply = &multiply,
  .negate = &negate,
  .notEqualTo = &isNotEqualTo,
  .subtract = &subtract,
};

static void
add
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_StaticAssert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) + Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) + (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) + (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) + (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setNatural64Value(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) + Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) + (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
divide
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_StaticAssert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_SizeValue x = Arcadia_Value_getSizeValue(A2);
    if (Arcadia_SizeValue_Literal(0) == x) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) / x);
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural8Value x = Arcadia_Value_getNatural8Value(A2);
    if (Arcadia_Natural8Value_Literal(0) == x) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) / (Arcadia_SizeValue)x);
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural16Value x = Arcadia_Value_getNatural16Value(A2);
    if (Arcadia_Natural16Value_Literal(0) == x) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) / (Arcadia_SizeValue)x);
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Natural32Value x = Arcadia_Value_getNatural32Value(A2);
    if (Arcadia_Natural32Value_Literal(0) == x) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) / (Arcadia_SizeValue)x);
  } else if (Arcadia_Value_isNatural64Value(A2)) {
    Arcadia_Natural64Value x = Arcadia_Value_getNatural64Value(A2);
    if (Arcadia_Natural64Value_Literal(0) == x) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_DivisionByZero);
      Arcadia_Thread_jump(thread);
    }
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setNatural64Value(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) / x);
  #else
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) / (Arcadia_SizeValue)x);
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
isEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) == Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
isGreaterThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) > Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) > (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) > (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) > (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) > Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) > (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
isGreaterThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) >= Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) >= (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) >= (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) >= (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) >= Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) >= (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
hash
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A1));
#undef A1
}

static void
identical
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) == Arcadia_Value_getSizeValue(A2));
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_False);
  }
#undef A2
#undef A1
}

static void
isLowerThan
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) < Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) < (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) < (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) < (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) < Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) < (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
isLowerThanOrEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) <= Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) <= (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) <= (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) <= (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) <= Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) <= (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
multiply
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_StaticAssert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) * Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) * (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) * (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) * (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setNatural64Value(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) * Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) * (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

static void
negate
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
  Arcadia_Value_setSizeValue(target, -Arcadia_Value_getSizeValue(A1));
#undef A1
}

static void
isNotEqualTo
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) != Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) != (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) != (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) != (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setBooleanValue(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) != Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setBooleanValue(target, Arcadia_Value_getSizeValue(A1) != (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Value_setBooleanValue(target, Arcadia_BooleanValue_True);
  }
#undef A2
#undef A1
}

static void
subtract
  (
    Arcadia_Thread* thread,
    Arcadia_Value* target,
    Arcadia_SizeValue numberOfArguments,
    Arcadia_Value* arguments
  )
{
#define A1 &(arguments[0])
#define A2 &(arguments[1])
  Arcadia_StaticAssert(Arcadia_SizeValue_Minimum >= Arcadia_SizeValue_Literal(0), "environment not (yet) supported");
  if (Arcadia_Value_isSizeValue(A2)) {
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) - Arcadia_Value_getSizeValue(A2));
  } else if (Arcadia_Value_isNatural8Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural8Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) - (Arcadia_SizeValue)Arcadia_Value_getNatural8Value(A2));
  } else if (Arcadia_Value_isNatural16Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural16Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setNatural64Value(target, Arcadia_Value_getSizeValue(A1) - (Arcadia_SizeValue)Arcadia_Value_getNatural16Value(A2));
  } else if (Arcadia_Value_isNatural32Value(A2)) {
    Arcadia_StaticAssert(Arcadia_SizeValue_Maximum >= Arcadia_Natural32Value_Maximum, "environment not (yet) supported");
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) - (Arcadia_SizeValue)Arcadia_Value_getNatural32Value(A2));
  } else if (Arcadia_Value_isNatural64Value(A2)) {
  #if Arcadia_SizeValue_Maximum < Arcadia_Natural64Value_Maximum
    Arcadia_Value_setNatural64Value(target, (Arcadia_Natural64Value)Arcadia_Value_getSizeValue(A1) * Arcadia_Value_getNatural64Value(A2));
  #else
    Arcadia_Value_setSizeValue(target, Arcadia_Value_getSizeValue(A1) - (Arcadia_SizeValue)Arcadia_Value_getNatural64Value(A2));
  #endif
  } else {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }
#undef A2
#undef A1
}

Arcadia_defineScalarType(Arcadia_Size, u8"Arcadia.Size", &_typeOperations);
