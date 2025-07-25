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

set(MyModule ${MyProjectName}.Audials)

if (NOT TARGET ${MyModule})
  option(${MyModule}.OpenAl.Enabled "TRUE enables OpenAL support. FALSE disables OpenAL support. Default is FALSE" FALSE)

  BeginProduct(${MyModule} library)

  set(${MyModule}.Backend.None 0)
  set(${MyModule}.Backend.OpenAl 1)
  set(${MyModule}.Backend ${${MyModule}.Backend.None})

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Windows} AND ${${MyModule}.OpenAl.Enabled})
    # Use OpenAL under Windows if enabled.
    set(${MyModule}.Backend ${${MyModule}.Backend.OpenAl})
    set(MyDependenciesDirectory "C:/arcadia-dependencies")
    list(APPEND ${MyModule}.PrivateLibraries ${OPENGL_LIBRARIES})
    if (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X64})
      set(${MyModule}.OpenAl.Libraries ${MyDependenciesDirectory}/my-openal-$<LOWER_CASE:$<CONFIG>>-x64/lib/OpenAL32.lib winmm.lib Avrt.lib)
      set(${MyModule}.OpenAl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-openal-$<LOWER_CASE:$<CONFIG>>-x64/include)
    elseif (${${MyModule}.InstructionSetArchitecture} STREQUAL ${${MyModule}.InstructionSetArchitecture.X86})
      set(${MyModule}.OpenAl.Libraries ${MyDependenciesDirectory}/my-openal-$<LOWER_CASE:$<CONFIG>>-x86/lib/OpenAL32.lib winmm.lib Avrt.lib)
      set(${MyModule}.OpenAl.HeaderFilesDirectory ${MyDependenciesDirectory}/my-openal-$<LOWER_CASE:$<CONFIG>>-x86/include)
    else()
      message(FATAL_ERROR " - unsupported instruction set architecture")
    endif()
    message(STATUS " - ${MyModule}.OpenAl.Libraries = ${${MyModule}.OpenAl.Libraries}")
    list(APPEND ${MyModule}.PrivateLibraries ${${MyModule}.OpenAl.Libraries})
    message(STATUS " - ${MyModule}.OpenAl.HeaderFilesDirectory = ${${MyModule}.OpenAl.HeaderFilesDirectory}")
    list(APPEND ${MyModule}.IncludeDirectories ${${MyModule}.OpenAl.HeaderFilesDirectory})
  endif()

  if (${${MyModule}.OperatingSystem} STREQUAL ${${MyModule}.OperatingSystem.Linux} AND ${${MyModule}.OpenAl.Enabled})
    # Use OpenAL under Linux if enabled.
    find_package(OpenAL)
    if (NOT OPENAL_FOUND)
      message(FATAL_ERROR " - OpenAL not found")
    else()
      message(STATUS " - OpenAL found - OPENAL_LIBRARY = ${OPENAL_LIBRARY}")
      list(APPEND ${MyModule}.PrivateLibraries ${OPENAL_LIBRARY})
      message(STATUS " - OpenAL found - OPENAL_INCLUDE_DIR = ${OPENAL_INCLUDE_DIR}")
      list(APPEND ${MyModule}.IncludeDirectories ${OPENAL_INCLUDE_DIR})
    endif()
  endif()

  list(APPEND ${MyModule}.SourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Include.c)
  list(APPEND ${MyModule}.HeaderFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Include.h)

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Configure.h.i ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Audials/Configure.h @ONLY)
  list(APPEND ${MyModule}.ConfigurationTemplateFiles ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Module/Audials/Configure.h.i)
  list(APPEND ${MyModule}.ConfigurationFiles ${CMAKE_CURRENT_BINARY_DIR}/Sources/Module/Audials/Configure.h)

  list(APPEND ${MyModule}.Libraries ${MyProjectName}.Ring2)
  EndProduct(${MyModule})
  set_target_properties(${MyModule} PROPERTIES FOLDER "Audials")

endif()
