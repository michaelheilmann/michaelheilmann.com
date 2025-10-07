// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2025 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/Engine/Demo/Configuration.h"
#include <stdlib.h>
#include <string.h>

#include "Arcadia/Ring1/Include.h"
#include "Arcadia/Ring2/Include.h"
#include "Arcadia/Audials/Include.h"
#include "Arcadia/Visuals/Include.h"
#include "Arcadia/DataDefinitionLanguage/Include.h"

#include "Arcadia/Engine/Demo/Audials.h"
#include "Arcadia/Engine/Demo/Visuals.h"

void
main1
  (
    Arcadia_Process* process,
    int argc,
    char **argv
  )
{
  Arcadia_BooleanValue quit = Arcadia_BooleanValue_False;
  Arcadia_Engine* engine = NULL;
  Arcadia_Visuals_Window* window = NULL;
  Arcadia_DataDefinitionLanguage_Tree_Node* configuration = NULL;

  Arcadia_Thread* thread = Arcadia_Process_getThread(process);

  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(thread, &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    
    {
      Arcadia_DataDefinitionLanguage_Tree_Node* temporary = (Arcadia_DataDefinitionLanguage_Tree_Node*)Cfg_loadConfiguration(thread);
      Arcadia_Object_lock(thread,  (Arcadia_Object*)temporary);
      configuration = temporary;
    }

    {
      Arcadia_Engine* temporary = Arcadia_Engine_getOrCreate(thread);
      Arcadia_Object_lock(thread, (Arcadia_Object*)temporary);
      engine = temporary;
    }
    Arcadia_String* windowMode = NULL;
    Arcadia_Visuals_DisplayDevice* displayDevice = NULL;
    Arcadia_Engine_Demo_startupVisuals(thread, engine, configuration, &displayDevice, &windowMode, &window);

    Arcadia_FileSystem* fileSystem = Arcadia_FileSystem_getOrCreate(thread);
    Arcadia_FileHandle* fileHandle = Arcadia_FileHandle_create(thread, fileSystem);
    Arcadia_FileHandle_openStandardOutput(thread, fileHandle);

    // (1) Initialize Audials.
    Arcadia_Engine_Demo_startupAudials(thread, engine, configuration);

    // (2) Play sine wave.
    Arcadia_Audials_System_playSine(thread, (Arcadia_Audials_System*)engine->audialsSystem);

    Arcadia_Process_stepArms(process);

    // (8) Enter the message loop.
    while (!quit) {
      Arcadia_Process_stepArms(process);
      Arcadia_Audials_System_update(thread, (Arcadia_Audials_System*)engine->audialsSystem);
      Arcadia_Visuals_System_update(thread, (Arcadia_Visuals_System*)engine->visualsSystem);
      Arcadia_Visuals_Window_beginRender(thread, window);
      Arcadia_Visuals_Window_endRender(thread, window);

      Arcadia_Engine_Event* event = Arcadia_Engine_dequeEvent(thread, engine);
      if (NULL != event && Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)event, _Arcadia_Visuals_KeyboardKeyEvent_getType(thread))) {
        Arcadia_Visuals_KeyboardKeyEvent* keyboardKeyEvent = (Arcadia_Visuals_KeyboardKeyEvent*)event;
        if (Arcadia_Visuals_KeyboardKeyEvent_getAction(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKeyAction_Released &&
            Arcadia_Visuals_KeyboardKeyEvent_getKey(thread, keyboardKeyEvent) == Arcadia_Visuals_KeyboardKey_Escape) {
          quit = Arcadia_BooleanValue_True;
        }
      }
    }

    // (9) Ensure the window is closed.
    Arcadia_Visuals_Window_close(thread, window);

    Cfg_saveConfiguration(thread, configuration);

    Arcadia_Thread_popJumpTarget(thread);

    // (10) Clean the message queue. FIXME: The messages prevent the engine from being gc'ed.
    while (Arcadia_Engine_dequeEvent(thread, engine)) {
      fprintf(stdout, "%s:%d: purging message\n", __FILE__, __LINE__);
    }

    if (window) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine->audialsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsSystem);
      engine->audialsSystem = NULL;
    }
    if (engine->visualsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsSystem);
      engine->visualsSystem = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
    }
  } else {
    Arcadia_Thread_popJumpTarget(thread);

    if (window) {
      // (9) Ensure the window is closed.
      Arcadia_Visuals_Window_close(thread, window);
      Arcadia_Object_unlock(thread, (Arcadia_Object*)window);
      window = NULL;
    }
    if (engine && engine->audialsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->audialsSystem);
      engine->audialsSystem = NULL;
    }
    if (engine && engine->visualsSystem) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine->visualsSystem);
      engine->visualsSystem = NULL;
    }
    if (engine) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)engine);
      engine = NULL;
    }
    if (configuration) {
      Arcadia_Object_unlock(thread, (Arcadia_Object*)configuration);
      configuration = NULL;
    }
  }
}

int
main
  (
    int argc,
    char** argv
  )
{
  Arcadia_Process* process = NULL;
  if (Arcadia_Process_get(&process)) {
    return EXIT_FAILURE;
  }
  Arcadia_JumpTarget jumpTarget;
  Arcadia_Thread_pushJumpTarget(Arcadia_Process_getThread(process), &jumpTarget);
  if (Arcadia_JumpTarget_save(&jumpTarget)) {
    main1(process, argc, argv);
  }
  Arcadia_Thread_popJumpTarget(Arcadia_Process_getThread(process));
  Arcadia_Status status = Arcadia_Thread_getStatus(Arcadia_Process_getThread(process));
  Arcadia_Process_relinquish(process);
  process = NULL;
  if (status) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
