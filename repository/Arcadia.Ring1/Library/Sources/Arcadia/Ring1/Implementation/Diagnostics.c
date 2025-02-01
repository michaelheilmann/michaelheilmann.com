
#define ARCADIA_RING1_PRIVATE (1)
#include "Arcadia/Ring1/Implementation/Diagnostics.h"

#include <stdio.h>

void
Arcadia_logf
  (
    Arcadia_LogFlags flags,
    const char* format,
    ...
  )
{
  va_list arguments;
  va_start(arguments, format);
  Arcadia_logfv(flags, format, arguments);
  va_end(arguments);
}

void
Arcadia_logfv
  (
    Arcadia_LogFlags flags,
    const char* format,
    va_list arguments
  )
{
  if (Arcadia_LogFlags_Error == (flags & Arcadia_LogFlags_Error)) {
    va_list argumentsCopy;
    va_copy(argumentsCopy, arguments);
    fprintf(stderr, format, argumentsCopy);
    va_end(argumentsCopy);
  }
  if (Arcadia_LogFlags_Info == (flags & Arcadia_LogFlags_Info)) {
    va_list argumentsCopy;
    va_copy(argumentsCopy, arguments);
    fprintf(stdout, format, argumentsCopy);
    va_end(argumentsCopy);
  }
  if (Arcadia_LogFlags_Trace == (flags & Arcadia_LogFlags_Trace)) {
    va_list argumentsCopy;
    va_copy(argumentsCopy, arguments);
    fprintf(stdout, format, argumentsCopy);
    va_end(argumentsCopy);
  }
}
