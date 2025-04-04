# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 - 2025 Michael Heilmann (contact@michaelheilmann.com).
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

# Last modified: 2024-09-26

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

set(MyDemoName ${MyProjectName}.Engine.Demo)

if (NOT TARGET ${MyDemoName})
  BeginProduct(${MyDemoName} executable)

  if (${${MyDemoName}.OperatingSystem} STREQUAL ${${MyDemoName}.OperatingSystem.Windows})

    FetchProduct(${MyDemoName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Library" "path to the ARMS1 library directory")
    FetchProduct(${MyDemoName}.Mil "${REPOSITORY_SOURCE_DIR}/R1/Library" "path to the MIL library directory")
    FetchProduct(${MyDemoName}.Audials "${REPOSITORY_SOURCE_DIR}/Module.Audials/Library" "path to the Audials module source directory")
    FetchProduct(${MyDemoName}.Visuals "${REPOSITORY_SOURCE_DIR}/Module.Visuals/Library" "path to the Visuals module source directory")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Engine.Demo/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Engine.Demo/Configure.h @ONLY)

    list(APPEND ${MyDemoName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Engine.Demo/Main.c)
    list(APPEND ${MyDemoName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Engine.Demo/Configure.h)

    list(APPEND ${MyDemoName}.PrivateLibraries Module.Audials Module.Visuals ${MyProjectName}.Mil ${MyProjectName}.Arms)

  else()
    set(${MyDemoName}.Enabled FALSE)
  endif()

  EndProduct(${MyDemoName})

endif()
