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

// Last modified: 2024-09-16

#if !defined(MODULE_VISUALS_PIXELBUFFER_H_INCLUDED)
#define MODULE_VISUALS_PIXELBUFFER_H_INCLUDED

#include "R.h"

#define PixelFormat_An8Rn8Gn8Bn8 (1)
#define PixelFormat_An8Bn8Gn8Rn8 (2)
#define PixelFormat_Bn8Gn8Rn8 (3)
#define PixelFormat_Bn8Gn8Rn8An8 (4)
#define PixelFormat_Rn8Gn8Bn8 (5)
#define PixelFormat_Rn8Gn8Bn8An8 (6)

/// - number of columns: The number of columns of the image.
///   A column is adressed by zero-based consecutive integral ascending indices (0,1,2,...)
/// - number of rows: The number of rows of the image.
///   A row is adressed by zero-based consecutive integral ascending indices (0,1,2,...)
/// - pixel format: The pixel format of the image.
/// - line padding: The number of Bytes after the last Byte of a line.
/// - line stride: The number of Bytes between the first Bytes of two consecutive lines.
///                number of columns * bytesPerPixel + line padding
/// - cell: A cell is uniquely adressed by its column index and its row index.
///         Each cell accomodates one pixel.
Rex_declareObjectType("PixelBuffer", PixelBuffer, "R.Object");

struct PixelBuffer {
  R_Object _parent;
  R_Natural8Value* bytes;
  R_Natural8Value pixelFormat;
  R_Integer32Value numberOfRows;
  R_Integer32Value numberOfColumns;
  R_Integer32Value linePadding;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the pixel format of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The pixel format of this pixel buffer.
R_Natural8Value
PixelBuffer_getPixelFormat
  (
    PixelBuffer* self
  );

/// @brief Get the pixel format of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param format The format.
/// @remarks
/// When converting from BGR or RGB to ABGR, ARGB, BGRA, or RGBA,
/// an alpha component with value 255 is added.
/// When converting from ABGR, ARGB, BGRA, or RGBA to BGR or RGB,
/// the alpha component is removed.
void
PixelBuffer_setPixelFormat
  (
    PixelBuffer* self,
    R_Natural8Value pixelFormat
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the line padding of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line padding of this pixel buffer. Always non-negative.
R_Integer32Value
PixelBuffer_getLinePadding
  (
    PixelBuffer* self
  );

/// @brief Set the line padding of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param linePadding The line padding. Must be non-negative.
/// @warning Can result in reallocation.
/// @warning The contents of the padding Bytes are unspecified.
void
PixelBuffer_setLinePadding
  (
    PixelBuffer* self,
    R_Integer32Value linePadding
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get component values of a pixel at the specified position in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param column The column index of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of columns.
/// @param row The row of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of rows.
/// @param r A pointer to a <code>R_Natural8Value</code> variable.
/// @param g A pointer to a <code>R_Natural8Value</code> variable.
/// @param b A pointer to a <code>R_Natural8Value</code> variable.
/// @param a A pointer to a <code>R_Natural8Value</code> variable.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>*r</code> is assigned the red component of the pixel.
/// <code>*g</code> is assigned the green component of the pixel.
/// <code>*b</code> is assigned the blue component of the pixel.
/// <code>*a</code> is assigned the alpha component of the pixel
/// if the pixel has an alpha component.
/// Otherwise it is assigned 255.
void
PixelBuffer_getPixelRgba
  (
    PixelBuffer* self,
    R_Integer32Value column,
    R_Integer32Value row,
    R_Natural8Value* r,
    R_Natural8Value* g,
    R_Natural8Value* b,
    R_Natural8Value* a
  );

/// @brief Set component values of a pixel at the specified position in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param column The column index of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of columns.
/// @param row The row of the pixel.
/// Must be non-negative. Must be smaller than or equal to the number of rows.
/// @param r The red component value.
/// @param g The green component value.
/// @param b The blue component value.
/// @param a The alpha component value.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>r</code> is assigned to the red component of the pixel.
/// <code>g</code> is assigned to the green component of the pixel.
/// <code>a</code> is assigned to the blue component of the pixel.
/// <code>a</code> is assigned to the alpha component of the pixel
/// if the pixel has an alpha component.
void
PixelBuffer_setPixelRgba
  (
    PixelBuffer* self,
    R_Integer32Value column,
    R_Integer32Value row,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b,
    R_Natural8Value a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set component values of the pixels in this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @param r The red component value.
/// @param g The green component value.
/// @param b The blue component value.
/// @param a The alpha component value.
/// @pre The pixel buffer must of a format ABGR, ARGB, BGR, BGRA, RGB, or RGBA.
/// The component values of the format must be an integer within the range of of [0,255].
/// @post
/// On success:
/// <code>r</code> is assigned to the red component of the pixel.
/// <code>g</code> is assigned to the green component of the pixel.
/// <code>a</code> is assigned to the blue component of the pixel.
/// <code>a</code> is assigned to the alpha component of the pixel
/// if the pixel has an alpha component.
void
PixelBuffer_fill
  (
    PixelBuffer* self,
    R_Natural8Value r,
    R_Natural8Value g,
    R_Natural8Value b,
    R_Natural8Value a
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Swap columns.
/// @param self A pointer to this pixel buffer.
/// @param column1 The first column.
/// @param column2 The second colum.
void
PixelBuffer_swapColumns
  (
    PixelBuffer* self,
    R_Integer32Value column1,
    R_Integer32Value column2
  );

/// @brief Swap row.
/// @param self A pointer to this pixel buffer.
/// @param row1 The first row.
/// @param row2 The second row.
void
PixelBuffer_swapRows
  (
    PixelBuffer* self,
    R_Integer32Value row1,
    R_Integer32Value row2
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Mirror this pixel buffer vertically.
/// @param self A pointer to this pixel buffer.
/// @post The pixel buffer was reflected horizontally.
/// That is, it was reflected by the axis starting at (width / 2, -infinity) to (width / 2, +infinity).
/// such that the pixel at position (column, row) is now at position (width - 1 - column, row).
void
PixelBuffer_reflectVertically
  (
    PixelBuffer* self
  );

/// @brief Reflect this pixel buffer horizontally.
/// @param self A pointer to this pixel buffer.
/// @post The pixel buffer was reflected horizontally.
/// That is, it was reflected by the axis starting at (-infinity, height / 2) to (+infinity, height / 2).
/// such that the pixel at position (column, row) is now at position (column, height - 1 - row).
void
PixelBuffer_reflectHorizontally
  (
    PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the number of columns of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The number of columns of this pixel buffer.
R_Integer32Value
PixelBuffer_getNumberOfColumns
  (
    PixelBuffer* self
  );

/// @brief Get the number of rows of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The number of rows of this pixel buffer.
R_Integer32Value
PixelBuffer_getNumberOfRows
  (
    PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the line stride of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
R_Integer32Value
PixelBuffer_getLineStride
  (
    PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the Bytes per pixel of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The line stride of this pixel buffer.
R_Integer32Value
PixelBuffer_getBytesPerPixel
  (
    PixelBuffer* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// Create a pixel buffer of the specified width, height, and pixel format.
/// Its default color is opaque black.
PixelBuffer*
PixelBuffer_create
  (
    R_Integer32Value linePadding,
    R_Integer32Value width,
    R_Integer32Value height,
    R_Natural8Value pixelFormat
  );

PixelBuffer*
PixelBuffer_createClone
  (
    PixelBuffer* other
  );


#if 0
/// @brief Get the width of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The width of this pixel buffer.
R_Integer32Value
PixelBuffer_getWidth
  (
    PixelBuffer* self
  );
#endif

#if 0
/// @brief Get the height of this pixel buffer.
/// @param self A pointer to this pixel buffer.
/// @return The height of this pixel buffer.
R_Integer32Value
PixelBuffer_getHeight
  (
    PixelBuffer* self
  );
#endif

#endif // MODULE_VISUALS_PIXELBUFFER_H_INCLUDED