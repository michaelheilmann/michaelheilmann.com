#if !defined(R_UTF8BYTEBUFFERREADER_H_INCLUDED)
#define R_UTF8BYTEBUFFERREADER_H_INCLUDED

#include "R/Utf8Reader.h"
#include "R/Size.h"
typedef struct R_ByteBuffer R_ByteBuffer;

Rex_declareObjectType("R.Utf8ByteBufferReader", R_Utf8ByteBufferReader, "R.Utf8Reader");

struct R_Utf8ByteBufferReader {
  R_Utf8Reader parent;
  R_ByteBuffer* source;
  R_SizeValue byteIndex;
  R_Natural32Value codePoint;
};

R_Utf8ByteBufferReader*
R_Utf8ByteBufferReader_create
  (
    R_ByteBuffer* source
  );

#endif // R_UTF8BYTEBUFFERREADER_H_INCLUDED
