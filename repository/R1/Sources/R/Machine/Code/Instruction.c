// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-10-28

#include "R/Machine/Code/Instruction.h"

#include "R/JumpTarget.h"
#include "R/Status.h"
#include "R/Types.h"
#include "R/UnmanagedMemory.h"
#include <string.h>
#include <assert.h>

#include "R/Machine/Code/Include.h"

static void
decodeIndex
(
  uint8_t** current,
  uint8_t const* start,
  uint8_t const* end,
  R_Machine_Code_IndexKind* indexKind,
  R_Natural32Value* indexValue
) {
  uint8_t* p = *current;
  switch ((*p) & 0b11000000) {
    case R_Machine_Code_ConstantIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Constant;
    } break;
    case R_Machine_Code_InvalidIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Invalid;
    } break;
    case R_Machine_Code_RegisterIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Register;
    } break;
    case R_Machine_Code_ReservedIndexFlag: {
      *indexKind = R_Machine_Code_IndexKind_Reserved;
    } break;
    default: {
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };
  uint8_t a = (*p) & (~0b11000000);
  if ((a & 0x20/*0b00100000*/) == 0x00/*0b00000000*/) {
    // 5 bits in total, fit into an uint8_t.
    uint8_t x0 = a & ~0x20;
    p++;
    uint32_t v = x0;
    *indexValue = v;
  } else if ((a & 0x38/*0b00111000*/) == 0x30/*0b00110000*/) {
    uint8_t x0 = a & ~0x38;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 6
      | x1 << 0
      ;
    *indexValue = v;
  } else if ((a & 0x3C/*0b00111100*/) == 0x38/*0b00111000*/) {
    uint8_t x0 = a & ~0x3C;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint8_t x2 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 12
               | x1 << 6
               | x2 << 0;
  } else if (a & 0x3E/*0b00111110*/ == 0x3C/*00111100*/) {
    uint8_t x0 = a & ~0x3E;
    p++;
    uint8_t x1 = (*p) & ~0xC0;
    p++;
    uint8_t x2 = (*p) & ~0xC0;
    p++;
    uint8_t x3 = (*p) & ~0xC0;
    p++;
    uint32_t v = x0 << 18
               | x1 << 12
               | x2 << 6
               | x3 << 0;
    *indexValue = v;
  } else {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  *current = p;
}

void
R_Instructions_add
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Add == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->add) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->add(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_and
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_And == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->and) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->and(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_concatenate
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Concatenate == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->concatenate) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->concatenate(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_divide
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Divide == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->divide) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->divide(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_equalTo
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_EqualTo == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->equalTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->equalTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThan
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_GreaterThan == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->greaterThan) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->greaterThan(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_greaterThanOrEqualTo
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_GreaterThanOrEqualTo == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->greaterThanOrEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->greaterThanOrEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_idle
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Idle == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
}

void
R_Instructions_lowerThan
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_LowerThan == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->lowerThan) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->lowerThan(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_lowerThanOrEqualTo
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_LowerThanOrEqualTo == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->lowerThanOrEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->lowerThanOrEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_multiply
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Multiply == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->multiply) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->multiply(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_negate
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Negate == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind operandIndexKind;
  R_Natural32Value operandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &operandIndexKind, &operandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* operandValue = operandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                &(interpreterState->constants[operandIndex]) : &(interpreterState->registers[operandIndex]);
  R_Type* operandType = R_Value_getType(operandValue);
  R_Type_Operations const* operations = R_Type_getOperations(operandType);
  if (!operations->negate) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->negate(targetValue, operandValue);
}

void
R_Instructions_not
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Not == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind operandIndexKind;
  R_Natural32Value operandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &operandIndexKind, &operandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const*operandValue = operandIndexKind == R_Machine_Code_IndexKind_Constant ?
                               &(interpreterState->constants[operandIndex]) : &(interpreterState->registers[operandIndex]);
  R_Type* operandType = R_Value_getType(operandValue);
  R_Type_Operations const* operations = R_Type_getOperations(operandType);
  if (!operations->not) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->not(targetValue, operandValue);
}

void
R_Instructions_notEqualTo
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_NotEqualTo == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->notEqualTo) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->notEqualTo(targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_or
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Or == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations-> or ) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations-> or (targetValue, firstOperandValue, secondOperandValue);
}

void
R_Instructions_subtract
  (
    R_InterpreterStateArgument* interpreterState
  )
{
  assert(R_Machine_Code_Opcode_Subtract == *interpreterState->ipCurrent);
  interpreterState->ipCurrent++;
  R_Machine_Code_IndexKind targetIndexKind;
  R_Natural32Value targetIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &targetIndexKind, &targetIndex);
  R_Machine_Code_IndexKind firstOperandIndexKind;
  R_Natural32Value firstOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &firstOperandIndexKind, &firstOperandIndex);
  R_Machine_Code_IndexKind secondOperandIndexKind;
  R_Natural32Value secondOperandIndex;
  decodeIndex(&interpreterState->ipCurrent, interpreterState->ipStart, interpreterState->ipEnd, &secondOperandIndexKind, &secondOperandIndex);
  R_Value* targetValue = &(interpreterState->registers[targetIndex]);
  R_Value const* firstOperandValue = firstOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                     &(interpreterState->constants[firstOperandIndex]) : &(interpreterState->registers[firstOperandIndex]);
  R_Value const* secondOperandValue = secondOperandIndexKind == R_Machine_Code_IndexKind_Constant ?
                                      &(interpreterState->constants[secondOperandIndex]) : &(interpreterState->registers[secondOperandIndex]);
  R_Type* firstOperandType = R_Value_getType(firstOperandValue);
  R_Type_Operations const* operations = R_Type_getOperations(firstOperandType);
  if (!operations->subtract) {
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
  operations->subtract(targetValue, firstOperandValue, secondOperandValue);
}

static void
R_Machine_Code_destruct
  (
    R_Machine_Code* self
  );

static void
R_Machine_Code_destruct
  (
    R_Machine_Code* self
  )
{
  if (self->p) {
    R_deallocateUnmanaged_nojump(self->p);
    self->p = NULL;
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &R_Machine_Code_destruct,
  .visit = NULL,
};

static const R_Type_Operations _typeOperations = {
  .objectTypeOperations = &_objectTypeOperations,
  .add = NULL,
  .and = NULL,
  .concatenate = NULL,
  .divide = NULL,
  .equalTo = NULL,
  .greaterThan = NULL,
  .greaterThanOrEqualTo = NULL,
  .hash = NULL,
  .lowerThan = NULL,
  .lowerThanOrEqualTo = NULL,
  .multiply = NULL,
  .negate = NULL,
  .not = NULL,
  .notEqualTo = NULL,
  .or = NULL,
  .subtract = NULL,
};

Rex_defineObjectType("R.Machine.Code", R_Machine_Code, "R.Object", R_Object, &_typeOperations);

void
R_Machine_Code_construct
  (
    R_Machine_Code* self
  )
{
  R_Type* _type = _R_Machine_Code_getType();
  R_Object_construct((R_Object*)self);
  self->p = NULL;
  self->sz = 0;
  self->cp = 0;
  if (!R_allocateUnmanaged_nojump(&self->p, 0)) {
    R_jump();
  }
  R_Object_setType((R_Object*)self, _type);
}

R_Machine_Code*
R_Machine_Code_create
  (
  )
{
  R_Machine_Code* self = R_allocateObject(_R_Machine_Code_getType());
  R_Machine_Code_construct(self);
  return self;
}

// Compute the new capacity
// - <new capacity> = 2 * <n> * <capacity> if <capacit> > 0
// - <new capacity> = 2 * <n> * 1 otherwise
// such that <n> is minimal and <new capacity> - <size> >= <required free capacity>
// If <new capacity> exists, return true and assign it to *new_cp.
// Otherwise return false.
static bool growCapacity1(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue *newCapacity) {
  static const R_SizeValue maximalCapacity = SIZE_MAX / sizeof(uint8_t);
  R_SizeValue currentNewCapacity = capacity ? capacity : 1;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  while (availableFreeCapacity < requiredFreeCapacity && currentNewCapacity <= maximalCapacity / 2) {
    currentNewCapacity *= 2;
    availableFreeCapacity = currentNewCapacity - size;
  }
  if (availableFreeCapacity < requiredFreeCapacity) {
    return false;
  }
  *newCapacity = currentNewCapacity;
  return true;
}

// Compute the new capacity
// <new capacity> = <maximal capacity>
// such that <new capacity> - <size> >= <required free capacity>.
// If such a new capacity exists, return true and assign it to *new_cp.
// Otherwise return false.*
static bool growCapacity2(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue *newCapacity) {
  static const R_SizeValue maximalCapacity = SIZE_MAX / sizeof(uint8_t);
  R_SizeValue currentNewCapacity = maximalCapacity;
  R_SizeValue availableFreeCapacity = currentNewCapacity - size;
  if (requiredFreeCapacity > availableFreeCapacity) {
    return false;
  }
  *newCapacity = currentNewCapacity;
  return true;
}

static bool growCapacity(R_SizeValue size, R_SizeValue capacity, R_SizeValue requiredFreeCapacity, R_SizeValue* newCapacity) {
  if (growCapacity1(size, capacity, requiredFreeCapacity, newCapacity)) {
    return true;
  }
  if (growCapacity2(size, capacity, requiredFreeCapacity, newCapacity)) {
    return true;
  }
  return false;
}

static void ensureFreeCapacity(R_Machine_Code* self, R_SizeValue requiredFreeCapacity) {
  R_SizeValue actualFreeCapacity = self->cp - self->sz;
  if (actualFreeCapacity < requiredFreeCapacity) {
    R_SizeValue newCapacity;
    if (!growCapacity(self->sz, self->cp, requiredFreeCapacity, &newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    if (!R_reallocateUnmanaged_nojump(&self->p, newCapacity)) {
      R_setStatus(R_Status_AllocationFailed);
      R_jump();
    }
    self->cp = newCapacity;
  }
}

void
R_Machine_Code_append
  (
    R_Machine_Code* self,
    R_Natural8Value const* bytes,
    R_SizeValue numberOfBytes
  )
{
  ensureFreeCapacity(self, numberOfBytes);
  memcpy(self->p + self->sz, bytes, numberOfBytes);
  self->sz += numberOfBytes;
}

void
R_Machine_Code_appendIndexNatural8
  (
    R_Machine_Code* self,
    R_Machine_Code_IndexKind indexKind,
    R_Natural8Value indexValue
  )
{
  R_Machine_Code_appendIndexNatural32(self, indexKind, indexValue);
}

void
R_Machine_Code_appendIndexNatural16
  (
    R_Machine_Code* self,
    R_Machine_Code_IndexKind indexKind,
    R_Natural16Value indexValue
  )
{
  R_Machine_Code_appendIndexNatural32(self, indexKind, indexValue);
}

void
R_Machine_Code_appendIndexNatural32
  (
    R_Machine_Code* self,
    R_Machine_Code_IndexKind indexKind,
    R_Natural16Value index
  )
{
  R_Natural8Value a = 0;
  switch (indexKind) {
    case R_Machine_Code_IndexKind_Constant: {
      a |= R_Machine_Code_ConstantIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Register: {
      a |= R_Machine_Code_RegisterIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Invalid: {
      a |= R_Machine_Code_InvalidIndexFlag;
    } break;
    case R_Machine_Code_IndexKind_Reserved: {
      a |= R_Machine_Code_ReservedIndexFlag;
    } break;
    default: {
      // Cannot be encoded.
      R_setStatus(R_Status_ArgumentValueInvalid);
      R_jump();
    } break;
  };
  if (index <= 31) {
    // We must encode 5 Bits in one Byte.
    // The Byte stores 5 Bits.
    uint8_t x = index;
    x |= a;
    R_Machine_Code_append(self, &x, 1);
  } else if (index <= 511) {
    // We must encode 9 Bits in two Bytes.
    // The first Byte stores 3 Bits, the 2nd Byte stores 6 Bits.
    uint8_t x = (index & 0b111000000) >> 6;
    x |= a;
    x |= 0b00110000;
    uint8_t y = (index & 0b000111111) >> 0;
    y |= 128/*0b10000000*/;
    R_Machine_Code_append(self, &x, 1);
    R_Machine_Code_append(self, &y, 1);
  } else if (index <= 16383) {
    // We must encode 14 Bits in three Bytes.
    // The first Byte uses 2 Bits, the 2nd to the 3rd Byte each use 6 Bits.
    uint8_t x = (index & 0b11000000000000) >> 12;
    x |= a;
    x |= 0b00111000;
    uint8_t y = (index & 0b00111111000000) >> 6;
    y |= 128;
    uint8_t z = (index & 0b00000000111111) >> 0;
    z |= 128;
    R_Machine_Code_append(self, &x, 1);
    R_Machine_Code_append(self, &y, 1);
    R_Machine_Code_append(self, &z, 1);
  } else if (index <= 524287) {
    // We must encode 19 Bits in four Bytes.
    // The first Byte uses 1 Byte, the 2nd to the 4th Byte each use 6 Bits.
    uint8_t x = (index & 0b1000000000000000000) >> 18;
    x |= a;
    x |= 0b00111100;
    uint8_t y = (index & 0b0111111000000000000) >> 12;
    y |= 128;
    uint8_t z = (index & 0b0000000111111000000) >> 6;
    z |= 128;
    uint8_t w = (index & 0b0000000000000111111) >> 0;
    w |= 128;
    R_Machine_Code_append(self, &x, 1);
    R_Machine_Code_append(self, &y, 1);
    R_Machine_Code_append(self, &z, 1);
    R_Machine_Code_append(self, &w, 1);
  } else {
    // Cannot be encoded.
    R_setStatus(R_Status_ArgumentValueInvalid);
    R_jump();
  }
}
