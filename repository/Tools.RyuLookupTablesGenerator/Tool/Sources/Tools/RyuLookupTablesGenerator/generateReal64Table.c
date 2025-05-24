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

#include "Tools/RyuLookupTablesGenerator/generateReal64Table.h"

#include "Arcadia/Ring2/Include.h"

#define PRINT_LARGE_TABLES (true)

#define FLOAT64_POS_TABLE_SIZE 326
// The C version has two code paths, one of which requires an additional entry here.
#define FLOAT64_NEG_TABLE_SIZE 342

// We intentionally choose these to be larger than or equal to the float equivalent + 64.
// This is B1 + 1
#define FLOAT64_POW5_BITCOUNT 125 // max 127
// This is B0 + 1
#define FLOAT64_POW5_INV_BITCOUNT 125 // max 127

static Arcadia_BigInteger* ONE = NULL;
static Arcadia_BigInteger* MASK64 = NULL;
static Arcadia_BigInteger* TWO = NULL;

static void
onNotifyDestroy
  (
    Arms_NotifyDestroyContext* context,
    void* object
  )
{
  Arcadia_BigInteger** variable = (Arcadia_BigInteger**)context;
  *variable = NULL;
}

static Arcadia_Integer32Value
pow5Bits
  (
    Arcadia_Integer32Value e
  )
{ return ((e * 1217359) >> 19) + 1; }

static Arcadia_BigInteger *
multiplier
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value i
  )
{
  // 5^i
  Arcadia_BigInteger* pow = Arcadia_BigInteger_create(thread);
  if (i < 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BigInteger_setPowerOfFiveNatural32(thread, pow, i);
  // length of 5^i in binary = ceil(log_2(5^i))
  Arcadia_Integer32Value pow5len = (Arcadia_Integer32Value)Arcadia_BigInteger_getBitLength(thread, pow);
  // [5^i / 2^j] = [5^i / 2^(ceil(log_2(5^i)) - FLOAT64_POW5_BITCOUNT)]
  // By construction, this will have exactly FLOAT64_POW5_BITCOUNT bits. Note that this can shift left if j is negative!
  Arcadia_BigInteger* pow5DivPow2 = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_shiftRightInteger64(thread, pow5DivPow2, pow5len - FLOAT64_POW5_BITCOUNT);
  if (Arcadia_BigInteger_getBitLength(thread, pow5DivPow2) != FLOAT64_POW5_BITCOUNT) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return pow5DivPow2;
}


// precondition: i >= 0
// Compute floor(2^k / 5^q) + 1 where
// - q = i as described in section 3.4
// - B0 = POV5_INV_BITCOUNT - 1 
static Arcadia_BigInteger*
invMultiplier
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value i
  )
{
  Arcadia_BigInteger* a = NULL;
  // 5^i
  Arcadia_BigInteger* pow = Arcadia_BigInteger_create(thread);
  if (i < 0) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_BigInteger_setPowerOfFiveNatural32(thread, pow, i);
  // length of 5^i in binary = ceil(log_2(5^i))
  Arcadia_Integer32Value pow5len = (Arcadia_Integer32Value)Arcadia_BigInteger_getBitLength(thread, pow);
  // We want floor(log_2(5^i)) here, which is ceil(log_2(5^i)) - 1 (no power of 5 is a power of 2).
  Arcadia_Integer32Value j = pow5len - 1 + FLOAT64_POW5_INV_BITCOUNT;
  // [2^j / 5^i] + 1 = [2^(floor(log_2(5^i)) + POW5_INV_BITCOUNT) / 5^i] + 1
  // By construction, this will have approximately POW5_INV_BITCOUNT + 1 bits.
  Arcadia_BigInteger_setPowerOfTwoNatural32(thread, a, j);
  Arcadia_BigInteger* inv = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, inv, ONE);
  Arcadia_BigInteger_multiply(thread, inv, a);
  Arcadia_BigInteger_divide(thread, inv, pow);
  Arcadia_BigInteger_add(thread, inv, ONE);
  // bits > B0
  // bits > 
  if (Arcadia_BigInteger_getBitLength(thread, inv) > FLOAT64_POW5_INV_BITCOUNT + 1) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
    Arcadia_Thread_jump(thread);
  }
  return inv;
}

static void
printTable
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* stringBuffer,
    Arcadia_ImmutableUtf8String* name,
    Arcadia_List* table,
    Arcadia_SizeValue entriesPerLine
  )
{
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"static const Arcadia_Natural64Value ", sizeof(u8""));
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(name));
  for (Arcadia_SizeValue i = 0, n = Arcadia_List_getSize(thread, table); i < n; ++i) {
    Arcadia_BigInteger *pow5 = Arcadia_List_getBigIntegerValueAt(thread, table, i);
    Arcadia_BigInteger* pow5High = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, pow5High, pow5);
    Arcadia_BigInteger_shiftRightInteger32(thread, pow5High, 64);
    Arcadia_BigInteger* pow5Low = Arcadia_List_getBigIntegerValueAt(thread, table, i);
    Arcadia_BigInteger_and(thread, pow5Low, MASK64);
    if (i % entriesPerLine == 0) {
      Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"  ", sizeof(u8"  ") - 1);
    } else {
      Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8" ", sizeof(u8" ") - 1);
    }
#if 0
    Arcadia_String* string = NULL;
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"{", sizeof(u8"{") - 1);
    string = Arcadia_BigInteger_toDecimalString(thread, pow5Low);
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8", ", sizeof(u8", ") - 1);
    string = Arcadia_BigInteger_toDecimalString(thread, pow5High);
    Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"}", sizeof(u8"}") - 1);
#else
    //System.out.printf("{ %20su, %18su }", pow5Low, pow5High);
#endif
    if (i != n - 1) {
      Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8",", sizeof(u8",") - 1);
    }
    if (i % entriesPerLine == entriesPerLine - 1) {
      Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);
    }
  }
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"};\n", sizeof(u8";\n") - 1);
}

static void
printOffsets
  (
    Arcadia_Thread* thread,
    Arcadia_StringBuffer* stringBuffer,
    Arcadia_ImmutableUtf8String* name,
    Arcadia_List* table,
    Arcadia_SizeValue entriesPerLine
  )
{}

void
Arcadia_Tools_RyuLookupTableGenerator_generateReal64Table
  (
    Arcadia_Thread* thread
  )
{
  Arcadia_BigInteger* a = NULL;

  // 1
  a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, a, 1);
  if (Arms_addNotifyDestroy(a, &ONE, &onNotifyDestroy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  ONE = a;
  a = NULL;

  // 2
  a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_setInteger8(thread, a, 1);
  if (Arms_addNotifyDestroy(a, &TWO, &onNotifyDestroy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  TWO = a;
  a = NULL;

  // (1 * 2^64) - 1
  a = Arcadia_BigInteger_create(thread);
  Arcadia_BigInteger_copy(thread, a, ONE);
  Arcadia_BigInteger_shiftLeftNatural8(thread, a, 64);
  Arcadia_BigInteger_subtract(thread, a, ONE);
  if (Arms_addNotifyDestroy(a, &MASK64, &onNotifyDestroy)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_EnvironmentFailed);
    Arcadia_Thread_jump(thread);
  }
  MASK64 = a;


  // TABLE_LT[-e2 - q] = floor(5^(-e2 - q) / 2^(q - k))
  // let i = -e2 - q to obtain
  // TABLE_LT[i] = floor(5^i / 2^(q - k))
  Arcadia_List* largeInvTable = Arcadia_List_create(thread);
  for (int i = 0; i < FLOAT64_NEG_TABLE_SIZE; i++) {
    Arcadia_List_insertBackBigIntegerValue(thread, largeInvTable, invMultiplier(thread, i));
  }

  //
  int mulTableSize = 26;
  Arcadia_List* smallInvTable = Arcadia_List_create(thread);
  for (int i = 0; i < (FLOAT64_NEG_TABLE_SIZE + mulTableSize - 1) / mulTableSize + 1; i++) {
    Arcadia_List_insertBackBigIntegerValue(thread, smallInvTable, invMultiplier(thread, mulTableSize * i));
  }

  //
  Arcadia_List* invErrorTable = Arcadia_List_create(thread);
  for (Arcadia_Natural32Value i = 0; i < FLOAT64_NEG_TABLE_SIZE; i++) {
    Arcadia_Natural32Value base = (i + mulTableSize - 1) / mulTableSize;
    Arcadia_Natural32Value base2 = base * mulTableSize;
    Arcadia_Natural32Value offset = base2 - i;
    Arcadia_BigInteger* mul = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_setPowerOfFiveNatural32(thread, mul, offset);

    Arcadia_BigInteger* result = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, result, Arcadia_List_getBigIntegerValueAt(thread, smallInvTable, base));
    Arcadia_BigInteger_subtract(thread, result, ONE);
    Arcadia_BigInteger_multiply(thread, result, mul);
    Arcadia_BigInteger_shiftRightInteger32(thread, result, pow5Bits(base2) - pow5Bits(i));
    Arcadia_BigInteger_add(thread, result, ONE);

    Arcadia_BigInteger_subtract3(thread, result, invMultiplier(thread, i), result);

    if (Arcadia_BigInteger_isNegative(thread, result) || Arcadia_BigInteger_compareTo(thread, result, TWO) > 0) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }

    Arcadia_List_insertBack(thread, invErrorTable, Arcadia_Value_makeInteger32Value(Arcadia_BigInteger_toInteger32(thread, result)));
  }

  //
  Arcadia_List* largeTable = Arcadia_List_create(thread);
  for (Arcadia_Natural32Value i = 0; i < FLOAT64_POS_TABLE_SIZE; ++i) {
    Arcadia_List_insertBackBigIntegerValue(thread, largeTable, multiplier(thread, i));
  }

  //
  Arcadia_List* smallTable = Arcadia_List_create(thread);
  for (Arcadia_Natural32Value i = 0; i < (FLOAT64_POS_TABLE_SIZE + mulTableSize - 1) / mulTableSize; ++i) {
    Arcadia_List_insertBackBigIntegerValue(thread, smallTable, multiplier(thread, mulTableSize * i));
  }

  //
  Arcadia_List* errorTable = Arcadia_List_create(thread);
  for (Arcadia_Natural32Value i = 0; i < FLOAT64_POS_TABLE_SIZE; ++i) {
    Arcadia_Natural32Value base = i / mulTableSize;
    Arcadia_Natural32Value base2 = base * mulTableSize;
    Arcadia_Natural32Value offset = base2 - i;
    Arcadia_BigInteger* mul = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_setPowerOfFiveNatural32(thread, mul, offset);

    Arcadia_BigInteger* result = Arcadia_BigInteger_create(thread);
    Arcadia_BigInteger_copy(thread, result, Arcadia_List_getBigIntegerValueAt(thread, smallTable, base));
    Arcadia_BigInteger_multiply(thread, result, mul);
    Arcadia_BigInteger_shiftRightInteger32(thread, result, pow5Bits(i) - pow5Bits(base2));
    Arcadia_BigInteger_subtract3(thread, result, multiplier(thread, i), result);

    if (Arcadia_BigInteger_isNegative(thread, result) || Arcadia_BigInteger_compareTo(thread, result, TWO) > 0) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentValueInvalid);
      Arcadia_Thread_jump(thread);
    }

    Arcadia_List_insertBackBigIntegerValue(thread, errorTable, result);
  }

  Arcadia_StringBuffer* stringBuffer = Arcadia_StringBuffer_create(thread);

  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"#define REAL64_POW5_INV_BITCOUNT ", sizeof(u8"#define REAL64_POW5_INV_BITCOUNT ") - 1);
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger32(thread, FLOAT64_POW5_INV_BITCOUNT)));
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"#define REAL64_POW5_BITCOUNT ", sizeof(u8"#define REAL64_POW5_BITCOUNT ") - 1);
  Arcadia_StringBuffer_insertBack(thread, stringBuffer, Arcadia_Value_makeImmutableUtf8StringValue(Arcadia_ImmutableUtf8String_createFromInteger32(thread, FLOAT64_POW5_BITCOUNT)));
  Arcadia_StringBuffer_append_pn(thread, stringBuffer, u8"\n", sizeof(u8"\n") - 1);

  if (PRINT_LARGE_TABLES) {
    printTable(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_INV_SPLIT", sizeof(u8"REAL64_POW5_INV_SPLIT") - 1), largeInvTable, 2);
    printTable(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_SPLIT", sizeof(u8"REAL64_POW5_SPLIT") - 1), largeTable, 2);
  } else {
    printTable(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_INV_SPLIT2", sizeof(u8"REAL64_POW5_INV_SPLIT2") - 1), smallInvTable, 1);
    printOffsets(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_OFFSETS", sizeof(u8"REAL64_POW5_OFFSETS") - 1), invErrorTable, 6);

    printTable(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_SPLIT2", sizeof(u8"REAL64_POW5_SPLIT2") - 1), smallTable, 1);
    printOffsets(thread, stringBuffer, Arcadia_ImmutableUtf8String_create(thread, u8"REAL64_POW5_OFFSETS", sizeof(u8"REAL64_POW5_OFFSETS") - 1), errorTable, 6);
    
  }

}
