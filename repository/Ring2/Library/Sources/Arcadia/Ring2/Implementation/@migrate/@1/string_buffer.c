#include "dx/core/string_buffer.h"

Core_defineObjectType("Core.StringBuffer",
                      Core_StringBuffer,
                      Core_Object);

static void Core_StringBuffer_destruct(Core_StringBuffer* SELF) {
  Core_InlineArrayListN8_uninitialize(&SELF->backend);
}

static void Core_StringBuffer_constructDispatch(Core_StringBuffer_Dispatch* SELF)
{/*Intentionally emtpy.*/}

Core_Result Core_StringBuffer_construct(Core_StringBuffer* SELF) {
  Core_BeginConstructor(Core_StringBuffer);
  Core_InlineArrayListN8_Configuration configuration = {
    .addedCallback = NULL,
    .removedCallback = NULL,
  };
  if (Core_InlineArrayListN8_initialize(&SELF->backend, 0, &configuration)) {
    return Core_Failure;
  }
  Core_EndConstructor(Core_StringBuffer);
}

Core_Result Core_StringBuffer_create(Core_StringBuffer** RETURN) {
  DX_CREATE_PREFIX(Core_StringBuffer);
  if (Core_StringBuffer_construct(SELF)) {
    CORE_UNREFERENCE(SELF);
    SELF = NULL;
    return Core_Failure;
  }
  *RETURN = SELF;
  return Core_Success;
}

Core_Result Core_StringBuffer_clone(Core_StringBuffer** RETURN, Core_StringBuffer const* SELF) {
  Core_StringBuffer* clone = NULL;
  if (Core_StringBuffer_create(&clone)) {
    return Core_Failure;
  }
  if (Core_StringBuffer_appendBytes(clone, SELF->backend.elements, SELF->backend.size)) {
    CORE_UNREFERENCE(clone);
    clone = NULL;
    return Core_Failure;
  }
  *RETURN = clone;
  return Core_Success;
}

Core_Result Core_StringBuffer_getByte(Core_Natural8* RETURN, Core_StringBuffer* SELF, Core_Size index) {
  return Core_InlineArrayListN8_get(RETURN, &SELF->backend, index);
}

Core_Result Core_StringBuffer_getBytes(void** RETURN, Core_StringBuffer* SELF) {
  return Core_InlineArrayListN8_getElements(RETURN, &SELF->backend);
}

Core_Result Core_StringBuffer_createIterator(Core_StringIterator** RETURN, Core_StringBuffer* SELF) {
  return Core_StringBufferIterator_create((Core_StringBufferIterator**)RETURN, SELF);
}

Core_Result Core_StringBuffer_appendBytes(Core_StringBuffer* SELF, char const* p, Core_Size n) {
  Core_Boolean t;
  if (_utf8_is_utf8_byte_sequence(&t, p, n, NULL)) {
    return Core_Failure;
  }
  if (!t) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return Core_InlineArrayListN8_appendMany(&SELF->backend, p, n);
}

Core_Result Core_StringBuffer_appendString(Core_StringBuffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, string)) {
    return Core_Failure;
  }
  return Core_InlineArrayListN8_appendMany(&SELF->backend, bytes, number_of_bytes);
}

Core_Result Core_StringBuffer_clear(Core_StringBuffer* SELF) {
  if (!SELF) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return Core_InlineArrayListN8_clear(&SELF->backend);
}

Core_Result Core_StringBuffer_getNumberOfBytes(Core_Size* RETURN, Core_StringBuffer* SELF) {
  return Core_InlineArrayListN8_getSize(RETURN, &SELF->backend);
}

Core_Result Core_StringBuffer_getNumberOfSymbols(Core_Size* RETURN, Core_StringBuffer* SELF) {
  return Core_InlineArrayListN8_getSize(RETURN, &SELF->backend);
}

Core_Result Core_StringBuffer_getString(Core_String** RETURN, Core_StringBuffer* SELF) {
  return Core_String_createFromArray(RETURN, &SELF->backend);
}

Core_Result Core_StringBuffer_getSubstring(Core_String** RETURN, Core_StringBuffer* SELF, Core_Size start, Core_Size length) {
  _utf8_symbol_range source = { .start = start, .length = length };
  _utf8_byte_range target = { .start = 0, .length = 0 };
  if (_utf8_symbol_range_to_byte_range(SELF->backend.elements, SELF->backend.size, &source, &target)) {
    return Core_Failure;
  }
  return Core_String_createFromSubArray(RETURN, &SELF->backend, target.start, target.length);
}

Core_Result Core_StringBuffer_prependBytes(Core_StringBuffer* SELF, Core_Natural8 const* p, Core_Size n) {
  Core_Boolean t;
  if (_utf8_is_utf8_byte_sequence(&t, p, n, NULL)) {
    return Core_Failure;
  }
  if (!t) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return Core_InlineArrayListN8_prependMany(&SELF->backend, p, n);
}

Core_Result Core_StringBuffer_prependString(Core_StringBuffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, string)) {
    return Core_Failure;
  }
  return Core_InlineArrayListN8_prependMany(&SELF->backend, bytes, number_of_bytes);
}

Core_Result Core_StringBuffer_setBytes(Core_StringBuffer* SELF, Core_Natural8 const* p, Core_Size n) {
  Core_Boolean t;
  if (_utf8_is_utf8_byte_sequence(&t, p, n, NULL)) {
    return Core_Failure;
  }
  if (!t) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return Core_InlineArrayListN8_set(&SELF->backend, p, n);
}

Core_Result Core_StringBuffer_setString(Core_StringBuffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, string)) {
    return Core_Failure;
  }
  return Core_InlineArrayListN8_set(&SELF->backend, bytes, number_of_bytes);
}

Core_Result Core_StringBuffer_appendFV(Core_StringBuffer* SELF, Core_String* format, va_list arguments) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, format)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, format)) {
    return Core_Failure;
  }
  return Core_appendFormatV(&SELF->backend, bytes, ((char const*)bytes) + number_of_bytes, arguments);
}

Core_Result Core_StringBuffer_appendF(Core_StringBuffer* SELF, Core_String* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  Core_Result result = Core_StringBuffer_appendFV(SELF, format, arguments);
  va_end(arguments);
  return result;
}

Core_Result Core_StringBuffer_prependFv(Core_StringBuffer* SELF, Core_String* format, va_list arguments) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, format)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, format)) {
    return Core_Failure;
  }
  return Core_prependFormatV(&SELF->backend, bytes, ((char const*)bytes) + number_of_bytes, arguments);
}

Core_Result Core_StringBuffer_insertF(Core_StringBuffer* SELF, Core_Size index, Core_String* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  Core_Result result = Core_StringBuffer_insertFv(SELF, index, format, arguments);
  va_end(arguments);
  return result;
}

Core_Result Core_StringBuffer_insertFv(Core_StringBuffer* SELF, Core_Size index, Core_String* format, va_list arguments) {
  Core_Size number_of_bytes = 0;
  if (Core_String_getNumberOfBytes(&number_of_bytes, format)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (Core_String_getBytes(&bytes, format)) {
    return Core_Failure;
  }
  return Core_insertFormatV(&SELF->backend, index, bytes, ((char const*)bytes) + number_of_bytes, arguments);
}

Core_Result Core_StringBuffer_prependF(Core_StringBuffer* SELF, Core_String* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  Core_Result result = Core_StringBuffer_prependFv(SELF, format, arguments);
  va_end(arguments);
  return result;
}

Core_Result Core_StringBuffer_removeLast(Core_StringBuffer* SELF) {
  if (!SELF) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  Core_Size size;
  if (Core_InlineArrayListN8_getSize(&size, &SELF->backend)) {
    return Core_Failure;
  }
  if (!size) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  Core_Natural8 value;
  Core_Size received = 1;
  Core_Size index = size - 1;
  Core_InlineArrayListN8_get(&value, &SELF->backend, index);
  while ((value & 0xC0) == 0x80) {
    if (index == 0) {
      Core_setError(Core_Error_ArgumentInvalid);
      return Core_Failure;
    }
    index--;
    received++;
  }
  Core_Size expected;
  if (_utf8_classify(&expected, value)) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return Core_InlineArrayListN8_removeMany(&SELF->backend, size - received, received);
}
