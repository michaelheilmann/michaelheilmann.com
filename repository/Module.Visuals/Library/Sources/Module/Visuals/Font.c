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

// Last modified: 2024-11-11

#include "Module/Visuals/Font.h"

static void
TextureFontWindows_destruct
  (
    TextureFontWindows* self
  )
{
  if (NULL != self->hFont) {
    DeleteObject(self->hFont);
    self->hFont = NULL;
  }
}

static const R_ObjectType_Operations _objectTypeOperations = {
  .constructor = NULL,
  .destruct = &TextureFontWindows_destruct,
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

Rex_defineObjectType("TextureFontWindows", TextureFontWindows, "R.Object", R_Object, &_typeOperations);

void
TextureFontWindows_construct
  (
    TextureFontWindows* self
  )
{
  R_Type* _type = _TextureFontWindows_getType();
  R_Object_construct((R_Object*)self);
  //
  HDC hScreenDeviceContext = GetDC(NULL);
  if (!hScreenDeviceContext) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
  if (!hDeviceContext) {
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  ReleaseDC(NULL, hScreenDeviceContext);
  hScreenDeviceContext = NULL;
  // Get the size of the symbol.
  self->codePoint = 'A';
  R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
  R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(byteBuffer);
  R_Utf8Writer_writeCodePoints(utf8ByteBufferWriter, &self->codePoint, 1);
  RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
  DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
  int32_t width = textRect.right - textRect.left;
  int32_t height = textRect.bottom - textRect.top;
  DeleteDC(hDeviceContext);
  hDeviceContext = NULL;
  // Create a bitmap of that size. Draw the symbol to the bitmap.
  self->bitmap = NativeWindowsBitmap_create(width, height);
  DrawTextA(self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  //
  R_Object_setType(self, _type);
}

TextureFontWindows*
TextureFontWindows_create
  (
  )
{
  TextureFontWindows* self = R_allocateObject(_TextureFontWindows_getType());
  TextureFontWindows_construct(self);
  return self;
}

void
TextureFontWindows_setCodePoint
  (
    TextureFontWindows* self,
    R_Natural32Value codePoint
  )
{
  if (self->codePoint != codePoint) {
    HDC hScreenDeviceContext = GetDC(NULL);
    if (!hScreenDeviceContext) {
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    HDC hDeviceContext = CreateCompatibleDC(hScreenDeviceContext);
    if (!hDeviceContext) {
      ReleaseDC(NULL, hScreenDeviceContext);
      hScreenDeviceContext = NULL;
      R_setStatus(R_Status_EnvironmentFailed);
      R_jump();
    }
    ReleaseDC(NULL, hScreenDeviceContext);
    hScreenDeviceContext = NULL;
    // Get the size of the symbol.
    self->codePoint = codePoint;
    R_ByteBuffer* byteBuffer = R_ByteBuffer_create();
    R_Utf8Writer* utf8ByteBufferWriter = (R_Utf8Writer*)R_Utf8ByteBufferWriter_create(byteBuffer);
    R_Utf8Writer_writeCodePoints(utf8ByteBufferWriter, &self->codePoint, 1);
    RECT textRect = { .left = 0, .top = 0, .right = 0, .bottom = 0 };
    DrawTextA(hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX | DT_CALCRECT);
    int32_t width = textRect.right - textRect.left;
    int32_t height = textRect.bottom - textRect.top;
    DeleteDC(hDeviceContext);
    hDeviceContext = NULL;
    // Create a bitmap of that size. Draw the symbol to the bitmap.
    self->bitmap = NativeWindowsBitmap_create(width, height);
    DrawTextA(self->bitmap->hDeviceContext, R_ByteBuffer_getBytes(byteBuffer), R_ByteBuffer_getNumberOfBytes(byteBuffer), &textRect, DT_LEFT | DT_NOCLIP | DT_NOPREFIX);
  }
}

PixelBuffer*
TextureFontWindows_getPixelBuffer
  (
    TextureFontWindows* self
  )
{
  return NativeWindowsBitmap_toPixelBuffer(self->bitmap);
}