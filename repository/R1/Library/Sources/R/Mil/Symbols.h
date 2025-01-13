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

// Last modified: 2024-12-08

#if !defined(R_MIL_SYMBOLS_H_INCLUDED)
#define R_MIL_SYMBOLS_H_INCLUDED

#include "Arcadia/Ring1/Include.h"
#include "R/String.h"
typedef struct R_Mil_Symbol R_Mil_Symbol;
typedef struct R_Mil_Scope R_Mil_Scope;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType(u8"R.Mil.Symbol", R_Mil_Symbol, u8"Arcadia.Object");

struct R_Mil_Symbol {
  Arcadia_Object _parent;
  // The name of the symbol.
  Arcadia_String* name;
  // The symbol shadwoed by this symbol.
  R_Mil_Symbol* shadowed;
  // The sibling of this symbol in this scope.
  R_Mil_Symbol* sibling;
  // The scope to which this symbol belongs.
  R_Mil_Scope* scope;
};

R_Mil_Symbol*
R_Mil_Symbol_create
  (
    Arcadia_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType(u8"R.Mil.SymbolTable", R_Mil_SymbolTable, u8"Arcadia.Object");

struct R_Mil_SymbolTable {
  Arcadia_Object _parent;
  R_Mil_Symbol** elements;
  Arcadia_SizeValue size;
  Arcadia_SizeValue capacity;
};

R_Mil_SymbolTable*
R_Mil_SymbolTable_create
  (
    Arcadia_Process* process
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Rex_declareObjectType(u8"R.Mil.Scope", R_Mil_Scope, u8"Arcadia.Object");

struct R_Mil_Scope {
  Arcadia_Object _parent;
  
  // The enclosing scope.
  R_Mil_Scope* enclosing;
  
  // A singly-linked list of symbols in this scope (linking pointer is Symbol.sibling).
  // Symbols that are added later are further on the front.
  R_Mil_Symbol* entries;
  
  /// The table shared between the scopes.
  R_Mil_SymbolTable* table;
};

R_Mil_Scope*
R_Mil_Scope_create
  (
    Arcadia_Process* process
  );

#endif // R_MIL_SYMBOLS_H_INCLUDED
