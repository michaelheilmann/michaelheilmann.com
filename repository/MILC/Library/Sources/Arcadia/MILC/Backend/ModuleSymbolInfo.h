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

#if !defined(ARCADIA_MILC_BACKEND_MODULESYMBOLINFO_H_INCLUDED)
#define ARCADIA_MILC_BACKEND_MODULESYMBOLINFO_H_INCLUDED

#include "Arcadia/MILC/Backend/SymbolInfo.h"

/// @brief Additional information for a module symbol.
/// Used by the C backend.
Arcadia_declareObjectType(u8"Arcadia.MILC.Backend.ModuleSymbolInfo", Arcadia_MILC_Backend_ModuleSymbolInfo,
                          u8"Arcadia.MILC.Backend.SymbolInfo");

struct Arcadia_MILC_Backend_ModuleSymbolInfoDispatch {
  Arcadia_MILC_Backend_SymbolInfoDispatch _parent;
};

struct Arcadia_MILC_Backend_ModuleSymbolInfo {
  Arcadia_MILC_Backend_SymbolInfo _parent;
  /// @brief The symbol.
  Arcadia_MILC_Symbol* symbol;
  /// @brief The Cxx name. For example, `Arcadia_Languages` or `Arcadia_Engine`.
  Arcadia_String* cxxName;
  /// @brief The uppercase Cxx name. For example, `ARCADIA_LANGUAGES` or `ARCADIA_ENGINE`.
  Arcadia_String* cxxNameUpperCase;
  /// @brief The absolute path to the directory of the module.
  Arcadia_FilePath* moduleDirectoryPath;
  /// @brief The absolute path to the source files.
  /// This is usually `<module directory path>'/Library/Sources'`.
  Arcadia_FilePath* cxxFilesPath;

  /// @brief The path to the Cxx source file.
  /// This is usually `<module name as path>/Include.c`.
  Arcadia_FilePath* cxxSourceFilePath;
  /// @brief The absolute path to the Cxx source file.
  /// This is `<module directory>/Library/Sources/<cxx source file path>`.
  Arcadia_FilePath* cxxSourceFileAbsolutePath;

  /// @brief The path to the Cxx header file.
  /// This is usually `<module name as path>/Include.g`.
  Arcadia_FilePath* cxxHeaderFilePath;
  /// @brief The absolute path to the Cxx header file.
  /// This is `<module directory>/Library/Sources/<cxx header file path>`.
  Arcadia_FilePath* cxxHeaderFileAbsolutePath;
};

Arcadia_MILC_Backend_ModuleSymbolInfo*
Arcadia_MILC_Backend_ModuleSymbolInfo_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  );

#endif // ARCADIA_MILC_BACKEND_MODULESYMBOLINFO_H_INCLUDED
