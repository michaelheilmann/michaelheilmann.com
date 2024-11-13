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

// Last modified: 2024-11-04

#if !defined(R_THREADSTATE_PRIVATE_H_INCLUDED)
#define R_THREADSTATE_PRIVATE_H_INCLUDED

#include "R/Size.h"
#include "R/Value.h"
#include "R/ThreadState.h"

typedef struct R_Value R_Value;

typedef struct _RegisterStack _RegisterStack;

struct _RegisterStack {
  R_Value* elements;
  R_SizeValue size, capacity;
};

void
_RegisterStack_initialize
  (
    _RegisterStack* self
  );

void
_RegisterStack_uninitialize
  (
    _RegisterStack* self
  );

typedef struct _RegisterFrame _RegisterFrame;

struct _RegisterFrame {
  _RegisterFrame* previous;
  // The stack index (0 -> top of the stack, n - 1 -> bottom of the stack, n is the size of the stack) where registers backed up on the register stack by this register frame start at.
  R_SizeValue start;
  // The number of registers backed up on the registers by this register frame.
  // start + length not be greater than the size of the stack.
  R_SizeValue length;
};

struct R_ThreadState {
  struct {
    R_CallState* elements;
    R_SizeValue size;
    R_SizeValue capacity; 
  } calls;
#if 0
  _RegisterStack  registerStack;
  // List of unused register frame objects for being re-used.
  _RegisterFrame* unusedRegisterFrames;
  // Stack fo register frames.
  _RegisterFrame* registerFrameStack;
#endif
  R_Value* registers;
  R_SizeValue numberOfRegisters;
};

#endif // R_THREADSTATE_PRIVATE_H_INCLUDED
