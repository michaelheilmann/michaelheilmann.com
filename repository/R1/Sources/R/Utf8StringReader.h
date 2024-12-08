#if !defined(R_UTF8STRINGREADER_H_INCLUDED)
#define R_UTF8STRINGREADER_H_INCLUDED

#include "R/Utf8Reader.h"
#include "R/Size.h"
typedef struct R_String R_String;

#define R_UTF8STRINGREADER(x) ((R_Utf8StringReader*)(x))
Rex_declareObjectType("R.Utf8StringReader", R_Utf8StringReader, "R.Utf8Reader");

struct R_Utf8StringReader {
  R_Utf8Reader parent;
  R_String* source;
  R_SizeValue byteIndex;
  R_Natural32Value codePoint;
};

R_Utf8StringReader*
R_Utf8StringReader_create
  (
    R_String* source
  );

#endif // R_UTF8STRINGREADER_H_INCLUDED
