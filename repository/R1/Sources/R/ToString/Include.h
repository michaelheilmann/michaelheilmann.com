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

// Last modified: 2024-09-26

#if !defined(R_NUMBERTOSTRING_INCLUDE_H_INCLUDED)
#define R_NUMBERTOSTRING_INCLUDE_H_INCLUDED

#include "Arms.h"

#include "R/Boolean.h"
#include "R/Integer16.h"
#include "R/Integer32.h"
#include "R/Integer64.h"
#include "R/Integer8.h"
#include "R/Natural16.h"
#include "R/Natural32.h"
#include "R/Natural64.h"
#include "R/Natural8.h"
#include "R/Real32.h"
#include "R/Real64.h"
#include "R/Void.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Integer16_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Integer16Value value,
    char** buffer,
    size_t* bufferLength
  );

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Integer32_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Integer32Value value,
    char** buffer,
    size_t* bufferLength
  );

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Integer64_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Integer64Value value,
    char** buffer,
    size_t* bufferLength
  );  

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Integer8_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Integer8Value value,
    char** buffer,
    size_t* bufferLength
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Natural16_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Natural16Value value,
    char** buffer,
    size_t* bufferCapacity
  );

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Natural32_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Natural32Value value,
    char** buffer,
    size_t* bufferCapacity
  );

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Natural64_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Natural64Value value,
    char** buffer,
    size_t* bufferLength
  );

// On success:
// <code>*buffer</code> is assigned an array of Bytes that is an UTF-8 string with a textual representation of the numeric value.
// <code>*bufferLength</code> is assigned the length, in Bytes, of that string.
// The array of Bytes must was allocated by the specified memory manager and must be deallocated using that memory manager when no longer required.
void
R_Natural8_toString
  (
    Arms_MemoryManager* memoryManager,
    R_Natural8Value value,
    char** buffer,
    size_t* bufferCapacity
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // R_NUMBERTOSTRING_INCLUDE_H_INCLUDED