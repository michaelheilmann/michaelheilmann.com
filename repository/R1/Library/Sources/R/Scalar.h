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

// Last modified: 2024-10-27

#if !defined(ARCADIA_SCALAR_H_INCLUDED)
#define ARCADIA_SCALAR_H_INCLUDED

typedef void Arcadia_Type;
typedef Arcadia_Type* Arcadia_TypeValue;

#define Rex_declareScalarType(cName) \
  Arcadia_TypeValue \
  _##cName##Value_getType \
    ( \
      Arcadia_Process* process \
    );

#define Rex_defineScalarType(cName, cilName, typeOperations) \
  static Arcadia_Type* g_##cName##_type = NULL; \
\
  static void \
  _##cName##_typeDestructing \
    ( \
      void* context \
    ) \
  { g_##cName##_type = NULL; } \
\
  Arcadia_TypeValue \
  _##cName##Value_getType \
    ( \
      Arcadia_Process* process \
    ) \
  { \
    if (!g_##cName##_type) { \
      g_##cName##_type = R_registerScalarType(process, cilName, sizeof(cilName) - 1, typeOperations, &_##cName##_typeDestructing); \
    } \
    return g_##cName##_type; \
  }

#endif // ARCADIA_SCALAR_H_INCLUDED
