#if !defined(ARCADIA_ENGINE_DEMO_MAINSCENE_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_MAINSCENE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"
#include "Arcadia/Engine/Demo/Scene.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demp.MainScene", Arcadia_Engine_Demo_MainScene,
                          u8"Arcadia.Engine.Demo.Scene");

struct Arcadia_Engine_Demo_MainScene {
  Arcadia_Engine_Demo_Scene parent;
};

Arcadia_Engine_Demo_MainScene*
Arcadia_Engine_Demo_MainScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine
  );

#endif // ARCADIA_ENGINE_DEMO_MAINSCENE_H_INCLUDED
