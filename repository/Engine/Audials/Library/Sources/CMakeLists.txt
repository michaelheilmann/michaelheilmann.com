# The author of this software is Michael Heilmann (contact@michaelheilmann.com).
#
# Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

cmake_minimum_required(VERSION 3.29)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

include(${REPOSITORY_SOURCE_DIR}/cmake/openal.cmake)
FetchOpenAl()

set(MyLibraryName ${MyProjectName}.Audials)



FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Sources" "path to the R1 source directory")

if (NOT TARGET ${MyLibraryName})
    add_library(${MyLibraryName})
    BeginProduct(${MyLibraryName})

    set(${MyLibraryName}.Backend.Unknown 0)
    set(${MyLibraryName}.Backend.OpenAl 1)
    set(${MyLibraryName}.Backend ${${MyLibraryName}.Backend.Unknown})
    if (${External.OpenAl.Available})
        set(${MyLibraryName}.Backend ${${MyLibraryName}.Backend.OpenAl})
    endif()
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Audials/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Audials/Configure.h @ONLY)

    list(APPEND ${MyLibraryName}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Audials/Include.c)
    list(APPEND ${MyLibraryName}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Audials/Include.h)
    list(APPEND ${MyLibraryName}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Audials/Configure.h)
    
    set(${MyLibraryName}.Libraries "")
    list(APPEND ${MyLibraryName}.Libraries Arcadia.R Arcadia.Arms)
    if (${External.OpenAl.Available})
      list(APPEND ${MyLibraryName}.Libraries External.OpenAl.Target)
    endif()
    target_link_libraries(${MyLibraryName} ${${MyLibraryName}.Libraries})

    EndProduct(${MyLibraryName} library)
endif()
