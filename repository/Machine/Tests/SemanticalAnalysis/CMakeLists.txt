# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
#
# Permission to use, copy, modify, and distribute this software for any
# purpose without fee is hereby granted, provided that this entire notice
# is included in all copies of any software which is or includes a copy
# or modification of this software and in all copies of the supporting
# documentation for such software.
#
# THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTY.IN PARTICULAR, NEITHER THE AUTHOR NOR LUCENT MAKES ANY
# REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING THE MERCHANTABILITY
# OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.20)

set(MyTestFolder Mil/Frontend)
set(MyTestName ${MyProjectName}.Mil.Frontend.Tests.SemanticalAnalysis)

if (NOT TARGET ${MyTestName})
  BeginProduct(${MyTestName} test)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Configure.h @ONLY)
  list(APPEND ${MyTestName}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Configure.h.i)
  list(APPEND ${MyTestName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Configure.h)

  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Main.c)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/EnterPass.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/EnterPass.h)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/StatementsContext.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/StatementsContext.h)
  list(APPEND ${MyTestName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Pass.c)
  list(APPEND ${MyTestName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Arcadia/Mil/Frontend/Tests/SemanticalAnalysis/Pass.h)

  list(APPEND ${MyTestName}.PrivateLibraries ${MyProjectName}.Machine ${MyProjectName}.Arms)

  EndProduct(${MyTestName})
  target_include_directories(${MyTestName} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  set_target_properties(${MyTestName} PROPERTIES FOLDER ${MyTestFolder})

  CopyProductAssets(${MyTestName}.CopyAssets ${MyTestFolder} ${CMAKE_CURRENT_SOURCE_DIR}/Assets ${CMAKE_CURRENT_BINARY_DIR}/Assets)
  add_dependencies(${MyTestName} ${MyTestName}.CopyAssets)
endif()
