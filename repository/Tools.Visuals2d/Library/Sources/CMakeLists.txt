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

# Last modified: 2024-09-16

cmake_minimum_required(VERSION 3.20)

if (NOT MyProjectIsDefined)
  if (NOT DEFINED MyProjectName)
    set(MyProjectName "Arcadia")
  endif()
  project(${MyProjectName})
  enable_testing()
  include(FetchContent)
  set(REPOSITORY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
  include(${REPOSITORY_SOURCE_DIR}/cmake/all.cmake)
  set(MyProjectIsDefined)
endif()

FetchProduct(${MyProjectName}.Arms "${REPOSITORY_SOURCE_DIR}/Arms1/Sources" "path to the ARMS1 source directory")
FetchProduct(${MyProjectName}.R "${REPOSITORY_SOURCE_DIR}/R1/Sources" "path to the R1 source directory")

if (NOT TARGET Tools.Visuals2d)
    add_library(Tools.Visuals2d)
    BeginProduct(Tools.Visuals2d)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Tools/Visuals2d/Configure.h @ONLY)

    list(APPEND Tools.Visuals2d.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/Include.c)
    list(APPEND Tools.Visuals2d.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/Include.h)
    list(APPEND Tools.Visuals2d.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/PixelBuffer.c)
    list(APPEND Tools.Visuals2d.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/PixelBuffer.h)
    list(APPEND Tools.Visuals2d.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/ImageWriterParameters.c)
    list(APPEND Tools.Visuals2d.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/ImageWriterParameters.h)
    list(APPEND Tools.Visuals2d.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/ImageWriter.c)
    list(APPEND Tools.Visuals2d.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Tools/Visuals2d/ImageWriter.h)
    list(APPEND Tools.Visuals2d.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Tools/Visuals2d/Configure.h)

    target_link_libraries(Tools.Visuals2d Arcadia.R Arcadia.Arms)

    EndProduct(Tools.Visuals2d library)
endif()
