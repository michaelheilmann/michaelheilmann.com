// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#if !defined(ARCADIA_MILC_SYMBOLS_SYMBOLS_H_INCLUDED)
#define ARCADIA_MILC_SYMBOLS_SYMBOLS_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
typedef struct Arcadia_MILC_Context Arcadia_MILC_Context;
typedef struct Arcadia_MILC_Symbol Arcadia_MILC_Symbol;
typedef struct Arcadia_MILC_Environment Arcadia_MILC_Environment;

/// @brief Singleton for predefined symbols - in particular, primitive type symbols.
Arcadia_declareObjectType(u8"Arcadia.MILC.Symbols", Arcadia_MILC_Symbols,
                          u8"Arcadia.Object");

struct Arcadia_MILC_SymbolsDispatch {
  Arcadia_ObjectDispatch _parent;
};

struct Arcadia_MILC_Symbols {
  Arcadia_Object _parent;

  /// @brief The context.
  Arcadia_MILC_Context* context;
  

  /// @code
  /// Arcadia.Integer16
  /// @endcode
  Arcadia_MILC_Symbol* integer16Symbol;
  /// @code
  /// Arcadia.Integer32
  /// @endcode
  Arcadia_MILC_Symbol* integer32Symbol;
  /// @code
  /// Arcadia.Integer64
  /// @endcode
  Arcadia_MILC_Symbol* integer64Symbol;
  /// @code
  /// Arcadia.Integer8
  /// @endcode
  Arcadia_MILC_Symbol* integer8Symbol;
  

  /// @code
  /// Arcadia.Natural16
  /// @endcode
  Arcadia_MILC_Symbol* natural16Symbol;
  /// @code
  /// Arcadia.Natural32
  /// @endcode
  Arcadia_MILC_Symbol* natural32Symbol;
  /// @code
  /// Arcadia.Natural64
  /// @endcode
  Arcadia_MILC_Symbol* natural64Symbol;
  /// @code
  /// Arcadia.Natural8
  /// @endcode
  Arcadia_MILC_Symbol* natural8Symbol;

  /// @code
  /// Arcadia.Boolean
  /// @endcode
  Arcadia_MILC_Symbol* booleanSymbol;


  /// @code
  /// Arcadia.Object
  /// @endcode
  Arcadia_MILC_Symbol* objectSymbol;

  /// @code
  /// Arcadia.Void
  /// @endcode
  Arcadia_MILC_Symbol* voidSymbol;
};

Arcadia_MILC_Symbols*
Arcadia_MILC_Symbols_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

Arcadia_MILC_Symbols*
Arcadia_MILC_Symbols_getInstance
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context
  );

Arcadia_MILC_Environment*
Arcadia_MILC_Symbols_getEnvironment
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self,
    Arcadia_MILC_Symbol* symbol
  );

/// @brief Get if a symbol is a built-in symbol.
/// @param thread A pointer to this thread.
/// @param self A pointer to this symbols.
/// @return #Arcadia_BooleanValue_True if this symbol is a built-in symbol. #Arcadia_BooleanValue_False otherwise.
/// @remarks Built-in symbols do not have a module.
Arcadia_BooleanValue
Arcadia_MILC_Symbols_isBuiltIn
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Symbols* self,
    Arcadia_MILC_Symbol* symbol
  );

#endif // ARCADIA_MILC_SYMBOLS_SYMBOLS_H_INCLUDED
