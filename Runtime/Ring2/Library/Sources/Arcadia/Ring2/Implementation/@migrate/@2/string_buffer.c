#include "dx/core/string_buffer.h"

Core_Result dx_string_buffer_clone(dx_string_buffer** RETURN, dx_string_buffer const* SELF) {
  dx_string_buffer* clone = NULL;
  if (dx_string_buffer_create(&clone)) {
    return Core_Failure;
  }
  if (dx_string_buffer_append_bytes(clone, SELF->backend.elements, SELF->backend.size)) {
    DX_UNREFERENCE(clone);
    clone = NULL;
    return Core_Failure;
  }
  *RETURN = clone;
  return Core_Success;
}

Core_Result dx_string_buffer_get_bytes(void** RETURN, dx_string_buffer* SELF) {
  return dx_inline_byte_array_get_bytes(RETURN, &SELF->backend);
}

Core_Result dx_string_buffer_get_number_of_bytes(Core_Size* RETURN, dx_string_buffer* SELF) {
  return dx_inline_byte_array_get_size(RETURN, &SELF->backend);
}

Core_Result dx_string_buffer_to_string(Core_String** RETURN, dx_string_buffer* SELF) {
  Core_Size size;
  if (dx_inline_byte_array_get_size(&size, &SELF->backend)) {
    return Core_Failure;
  }
  void* bytes;
  if (dx_inline_byte_array_get_bytes(&bytes, &SELF->backend)) {
    return Core_Failure;
  }
  // @todo Add a constructor dx_string_from_byte_buffer in order to avoid the UTF-8 validity recheck that Core_String_create(char const*, Core_Size) performs.
  return Core_String_create(RETURN, bytes, size);
}

Core_Result dx_string_buffer_create_iterator(dx_string_iterator** RETURN, dx_string_buffer* SELF) {
  return dx_string_buffer_iterator_impl_create((dx_string_buffer_iterator_impl**)RETURN, SELF);
}

Core_Result dx_string_buffer_set_bytes(dx_string_buffer* SELF, char const* p, Core_Size n) {
  if (!dx__is_utf8_sequence(p, n)) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return dx_inline_byte_array_set(&SELF->backend, p, n);
}

Core_Result dx_string_buffer_set_string(dx_string_buffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (dx_string_get_number_of_bytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (dx_string_get_bytes(&bytes, string)) {
    return Core_Failure;
  }
  return dx_inline_byte_array_set(&SELF->backend, bytes, number_of_bytes);
}

Core_Result dx_string_buffer_prepend_bytes(dx_string_buffer* SELF, char const* p, Core_Size n) {
  if (!dx__is_utf8_sequence(p, n)) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return dx_inline_byte_array_prepend(&SELF->backend, p, n);
}

Core_Result dx_string_buffer_prepend_string(dx_string_buffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (dx_string_get_number_of_bytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (dx_string_get_bytes(&bytes, string)) {
    return Core_Failure;
  }
  return dx_inline_byte_array_prepend(&SELF->backend, bytes, number_of_bytes);
}

Core_Result dx_string_buffer_append_bytes(dx_string_buffer* SELF, char const* p, Core_Size n) {
  if (!dx__is_utf8_sequence(p, n)) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return dx_inline_byte_array_append(&SELF->backend, p, n);
}

Core_Result dx_string_buffer_append_string(dx_string_buffer* SELF, Core_String* string) {
  Core_Size number_of_bytes = 0;
  if (dx_string_get_number_of_bytes(&number_of_bytes, string)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (dx_string_get_bytes(&bytes, string)) {
    return Core_Failure;
  }
  return dx_inline_byte_array_append(&SELF->backend, bytes, number_of_bytes);
}

Core_Result dx_string_buffer_append_fv(dx_string_buffer* SELF, Core_String* format, va_list arguments) {
  Core_Size number_of_bytes = 0;
  if (dx_string_get_number_of_bytes(&number_of_bytes, format)) {
    return Core_Failure;
  }
  void const* bytes = NULL;
  if (dx_string_get_bytes(&bytes, format)) {
    return Core_Failure;
  }
  return dx__format_v(&SELF->backend, bytes, ((char const*)bytes) + number_of_bytes, arguments);
}

Core_Result dx_string_buffer_append_f(dx_string_buffer* SELF, Core_String* format, ...) {
  va_list arguments;
  va_start(arguments, format);
  Core_Result result = dx_string_buffer_append_fv(SELF, format, arguments);
  va_end(arguments);
  return result;
}

Core_Result dx_string_buffer_remove_last(dx_string_buffer* SELF) {
  if (!SELF) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  Core_Size size;
  if (dx_inline_byte_array_get_size(&size, &SELF->backend)) {
    return Core_Failure;
  }
  if (!size) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  void* bytes;
  if (dx_inline_byte_array_get_bytes(&bytes, &SELF->backend)) {
    return Core_Failure;
  }
  char const* start = (char const*)bytes;
  char const* end = start + size;
  char const* current = end - 1;
  Core_Size received = 1;
  while (((*current) & 0xC0) == 0x80) {
    if (current == start) {
      Core_setError(Core_Error_ArgumentInvalid);
      return Core_Failure;
    }
    current--;
    received++;
  }
  Core_Size expected = _utf8_classify(*current);
  if (!expected) {
    Core_setError(Core_Error_ArgumentInvalid);
    return Core_Failure;
  }
  return dx_inline_byte_array_remove(&SELF->backend, size - received, received);
}
