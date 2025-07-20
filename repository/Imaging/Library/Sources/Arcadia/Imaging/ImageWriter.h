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

#if !defined(ARCADIA_IMAGING_IMAGEWRITER_H_INCLUDED)
#define ARCADIA_IMAGING_IMAGEWRITER_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Imaging/PixelBuffer.h"

Arcadia_declareObjectType(u8"ImageWriter", ImageWriter, u8"Arcadia.Object");

struct ImageWriter {
  Arcadia_Object _parent;
  
  Arcadia_ImmutableList* (*getSupportedTypes)(Arcadia_Thread* thread, ImageWriter* self);

  void (*writeToPath)(Arcadia_Thread* thread, ImageWriter* self, Arcadia_String* extension, Arcadia_List *sourcePixelBuffers, Arcadia_String* targetPath);
  void (*writeToByteBuffer)(Arcadia_Thread* thread, ImageWriter* self, Arcadia_String* extension, Arcadia_List* sourcePixelBuffers, Arcadia_ByteBuffer* targetByteBuffer);
};

/// @brief A set of strings denoting the extensions supported by this image writer.
/// @param thread A pointer to this thread.
/// @param self A pointer to this image writer.
/// @return A set of strings denoting the extensions supported by this image writer.
/// @remarks Canonical strings are "bmp", "ico", and "png".
Arcadia_ImmutableList*
ImageWriter_getSupportedTypes
  (
    Arcadia_Thread* thread,
    ImageWriter* self
  );

void
ImageWriter_writeToPath
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List *sourcePixelBuffers,
    Arcadia_String* targetPath
  );

void
ImageWriter_writeToByteBuffer
  (
    Arcadia_Thread* thread,
    ImageWriter* self,
    Arcadia_String* extension,
    Arcadia_List* sourcePixelBuffers,
    Arcadia_ByteBuffer* targetByteBuffer
  );

#endif // ARCADIA_IMAGING_IMAGEWRITER_H_INCLUDED
