// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024 Michael Heilmann (contact@michaelheilmann.com).
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

// Last modified: 2024-09-26

#include "Audials/Include.h"

#include "R.h"

#include "al.h"
// NULL
#include <stddef.h>
// ALCdevice
#include "alc.h"

#define R_Status_EnvironmentFailed (1000)

// A list of sounds.
// The list is cleared when the audio system shuts down.
static R_List* g_sounds = NULL;

static ALCdevice* g_device = NULL;

// Get the name of the default input device.
static R_String*
getDefaultInputDevice
  (
  )
{
  const ALCchar* start = alcGetString(NULL, ALC_CAPTURE_DEFAULT_DEVICE_SPECIFIER);
  const ALCchar* current = start;
  while ('\0' != *current) {
    current++;
  }
  return R_String_create_pn(start, current - start);
}

// Get the name of the default output device.
static R_String*
getDefaultOutputDevice
  (
  )
{
  const ALCchar* start = alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER);
  const ALCchar* current = start;
  while ('\0' != *current) {
    current++;
  }
  return R_String_create_pn(start, current - start);
}

// Get the names of the input devices.
static R_List*
getInputDevicesNames
  (
  )
{
  if (ALC_FALSE == alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  R_List* inputDevicesNames = R_List_create();
  const ALCchar* start = alcGetString(NULL, ALC_CAPTURE_DEVICE_SPECIFIER);
  const ALCchar* current = start;
  while (true) {
    while ('\0' != *current) {
      current++;
    }
    if (start != current) {
      R_List_appendObjectReferenceValue(inputDevicesNames, (R_ObjectReferenceValue)R_String_create_pn(start, current - start));
      current++;
      start = current;
    } else {
      break;
    }
  }
  return inputDevicesNames;
}

// Get the names of the output devices.
static R_List*
getOutputDevicesNames
  (
  )
{
  if (ALC_FALSE == alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT")) {
    R_setStatus(R_Status_EnvironmentFailed);
    R_jump();
  }
  R_List* outputDevicesNames = R_List_create();
  const ALCchar* start = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
  const ALCchar* current = start;
  while (true) {
    while ('\0' != *current) {
      current++;
    }
    if (start != current) {
      R_List_appendObjectReferenceValue(outputDevicesNames, (R_ObjectReferenceValue)R_String_create_pn(start, current - start));
      current++;
      start = current;
    } else {
      break;
    }
  }
  return outputDevicesNames;
}

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

static UINT g_oldCodePage = CP_NONE;

void
Console_startup
  (
  )
{ 

  g_oldCodePage = GetConsoleOutputCP();
  SetConsoleOutputCP(CP_UTF8);
}

void
Console_shutdown
  (
  )
{ 
  SetConsoleOutputCP(g_oldCodePage);
  g_oldCodePage = CP_NONE;
}

void
Audials_startup
  (
  )
{
  Console_startup();
  fwrite("input devices:\n", 1, sizeof("input devices:\n") - 1, stdout);
  R_List* inputDevicesNames = getInputDevicesNames();
  for (R_SizeValue i = 0, n = R_List_getSize(inputDevicesNames); i < n; ++i) {
    R_String* inputDeviceName = (R_String*)R_List_getObjectReferenceValueAt(inputDevicesNames, i);
    fwrite(R_String_getBytes(inputDeviceName), 1, R_String_getNumberOfBytes(inputDeviceName), stdout);
    fwrite("\n", 1, sizeof("\n") - 1, stdout);
  }
  fwrite("default input device:\n", 1, sizeof("default input device:\n") - 1, stdout);
  R_String* inputDeviceName = getDefaultInputDevice();
  fwrite(R_String_getBytes(inputDeviceName), 1, R_String_getNumberOfBytes(inputDeviceName), stdout);
  fwrite("\n", 1, sizeof("\n") - 1, stdout);

  fwrite("output devices:\n", 1, sizeof("output devices:\n") - 1, stdout);
  R_List* outputDevicesNames = getOutputDevicesNames();
  for (R_SizeValue i = 0, n = R_List_getSize(inputDevicesNames); i < n; ++i) {
    R_String* outputDeviceName = (R_String*)R_List_getObjectReferenceValueAt(outputDevicesNames, i);
    fwrite(R_String_getBytes(outputDeviceName), 1, R_String_getNumberOfBytes(outputDeviceName), stdout);
    fwrite("\n", 1, sizeof("\n") - 1, stdout);
  }
  fwrite("default output device:\n", 1, sizeof("default output device:\n") - 1, stdout);
  R_String* outputDeviceName = getDefaultOutputDevice();
  fwrite(R_String_getBytes(outputDeviceName), 1, R_String_getNumberOfBytes(outputDeviceName), stdout);
  fwrite("\n", 1, sizeof("\n") - 1, stdout);

}

void
Audials_shutdown
  (
  )
{ }

static void
Audials_Sound_finalize
  (
    Audials_Sound* self
  )
{ }

Audials_Sound*
Audials_Sound_create
  (
  )
{
  return NULL;
}

void
Audials_Sound_play
  (
    Audials_Sound* self
  )
{
}
