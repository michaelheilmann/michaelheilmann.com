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

#if !defined(ARCADIA_RING2_IMPLEMENTATION_STRING_H_INCLUDED)
#define ARCADIA_RING2_IMPLEMENTATION_STRING_H_INCLUDED

#if !defined(ARCADIA_RING2_PRIVATE)
  #error("do not include directly, include `Arcadia/Ring2/Include.h` instead")
#endif

#include "Arcadia/Ring1/Include.h"

Arcadia_declareObjectType("Arcadia.String", Arcadia_String, "Arcadia.Object");

struct Arcadia_String {
  Arcadia_Object _parent;
  Arcadia_ImmutableUtf8String* immutableUtf8String;
};

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_create_pn
Arcadia_String*
Arcadia_String_create_pn
  (
    Arcadia_Thread* thread,
    Arcadia_ImmutableByteArray* immutableByteArray
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_create
Arcadia_String*
Arcadia_String_create
  (
    Arcadia_Thread* thread,
    Arcadia_Value value
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_endsWith_pn
Arcadia_BooleanValue
Arcadia_String_endsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_startsWith-pn
Arcadia_BooleanValue
Arcadia_String_startsWith_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_string_getNumberOfBytes
Arcadia_SizeValue
Arcadia_String_getNumberOfBytes
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

Arcadia_Natural8Value const*
Arcadia_String_getBytes
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_getByteAt
Arcadia_Natural8Value
Arcadia_String_getByteAt
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    Arcadia_SizeValue index
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_getNumberOfCodePoints
Arcadia_SizeValue
Arcadia_String_getNumberOfCodePoints
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

#if 0
// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_getSubString
Arcadia_String*
Arcadia_String_getSubString
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    Arcadia_SizeValue index,
    Arcadia_SizeValue length
  );
#endif

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_isEqualTo_pn
Arcadia_BooleanValue
Arcadia_String_isEqualTo_pn
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self,
    void const* bytes,
    Arcadia_SizeValue numberOfBytes
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toBoolean
Arcadia_BooleanValue
Arcadia_String_toBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toInteger16
Arcadia_Integer16Value
Arcadia_String_toInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toInteger32
Arcadia_Integer32Value
Arcadia_String_toInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toInteger64
Arcadia_Integer64Value
Arcadia_String_toInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toInteger8
Arcadia_Integer8Value
Arcadia_String_toInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toNatural16
Arcadia_Natural16Value
Arcadia_String_toNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toNatural32
Arcadia_Natural32Value
Arcadia_String_toNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toNatural64
Arcadia_Natural64Value
Arcadia_String_toNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia_String_toNatural8
Arcadia_Natural8Value
Arcadia_String_toNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#Arcadia-string-toreal32
Arcadia_Real32Value
Arcadia_String_toReal32
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#arcadia-string-toreal64
Arcadia_Real64Value
Arcadia_String_toReal64
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

// https://michaelheilmann.com/Arcadia/Ring2/#arcadia-string-void
Arcadia_VoidValue
Arcadia_String_toVoid
  (
    Arcadia_Thread* thread,
    Arcadia_String const* self
  );

Arcadia_String*
Arcadia_String_createFromBoolean
  (
    Arcadia_Thread* thread,
    Arcadia_BooleanValue booleanValue
  );

Arcadia_String*
Arcadia_String_createFromInteger16
  (
    Arcadia_Thread* thread,
    Arcadia_Integer16Value integer16Value
  );

Arcadia_String*
Arcadia_String_createFromInteger32
  (
    Arcadia_Thread* thread,
    Arcadia_Integer32Value integer32Value
  );

Arcadia_String*
Arcadia_String_createFromInteger64
  (
    Arcadia_Thread* thread,
    Arcadia_Integer64Value integer64Value
  );

Arcadia_String*
Arcadia_String_createFromInteger8
  (
    Arcadia_Thread* thread,
    Arcadia_Integer8Value integer8Value
  );

Arcadia_String*
Arcadia_String_createFromNatural16
  (
    Arcadia_Thread* thread,
    Arcadia_Natural16Value natural16Value
  );

Arcadia_String*
Arcadia_String_createFromNatural32
  (
    Arcadia_Thread* thread,
    Arcadia_Natural32Value natural32Value
  );

Arcadia_String*
Arcadia_String_createFromNatural64
  (
    Arcadia_Thread* thread,
    Arcadia_Natural64Value natural64Value
  );

Arcadia_String*
Arcadia_String_createFromNatural8
  (
    Arcadia_Thread* thread,
    Arcadia_Natural8Value natural8Value
  );

Arcadia_String*
Arcadia_String_createFromReal32
  (
    Arcadia_Thread* thread,
    Arcadia_Real32Value real32Value
  );

Arcadia_String*
Arcadia_String_createFromReal64
  (
    Arcadia_Thread* thread,
    Arcadia_Real64Value real64Value
  );

Arcadia_String*
Arcadia_String_createFromSize
  (
    Arcadia_Thread* thread,
    Arcadia_SizeValue sizeValue
  );

Arcadia_String*
Arcadia_String_createFromVoid
  (
    Arcadia_Thread* thread,
    Arcadia_VoidValue voidValue
  );

#endif // ARCADIA_RING2_IMPLEMENTATION_STRING_H_INCLUDED
