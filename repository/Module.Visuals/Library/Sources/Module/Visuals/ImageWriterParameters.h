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

// Last modified: 2024-09-16

#if !defined(MODULE_VISUALS_IMAGEWRITERPARAMETERS_H_INCLUDED)
#define MODULE_VISUALS_IMAGEWRITERPARAMETERS_H_INCLUDED

#include "R/Include.h"

typedef enum ImageWriterFormat {
  ImageWriterFormat_Undefined = 0,
  ImageWriterFormat_Tiff,
  ImageWriterFormat_Png,
  ImageWriterFormat_Bmp,
} ImageWriterFormat;

/// @code
/// class ImageWriterParameters {
///   construct(path:String,format:ImageWriterFormat)
///   construct(byteBuffer:ByteBuffer,format:ImageWriterFormat)
/// }
/// @endcode
Rex_declareObjectType(u8"ImageWriterParameters", ImageWriterParameters, u8"Arcadia.Object");

ImageWriterParameters*
ImageWriterParameters_createFile
  (
    Arcadia_Process* process,
    Arcadia_String* path,
    ImageWriterFormat format
  );

ImageWriterParameters*
ImageWriterParameters_createByteBuffer
  (
    Arcadia_Process* process,
    Arcadia_ByteBuffer* byteBuffer,
    ImageWriterFormat format
  );

Arcadia_BooleanValue
ImageWriterParameters_hasPath
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

Arcadia_String*
ImageWriterParameters_getPath
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

Arcadia_BooleanValue
ImageWriterParameters_hasByteBuffer
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

Arcadia_ByteBuffer*
ImageWriterParameters_getByteBuffer
  (
    Arcadia_Process* process,
    ImageWriterParameters* self
  );

ImageWriterFormat
ImageWriterParameters_getFormat
  (
    ImageWriterParameters* self
  );

#endif // MODULE_VISUALS_IMAGEWRITERPARAMETERS_H_INCLUDED
