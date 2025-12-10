#if !defined(ARCADIA_ENGINE_DEMO_SCENE_H_INCLUDED)
#define ARCADIA_ENGINE_DEMO_SCENE_H_INCLUDED

#include "Arcadia/Visuals/Include.h"

Arcadia_declareObjectType(u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                          u8"Arcadia.Object");

struct Arcadia_Engine_Demo_Scene {
  Arcadia_Object parent;
  Arcadia_Engine* engine;
  void (*updateGraphics)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*updateLogic)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*);
};

void
Arcadia_Engine_Demo_Scene_updateGraphics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

void
Arcadia_Engine_Demo_Scene_updateLogic
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  );

#endif // ARCADIA_ENGINE_DEMO_SCENE_H_INCLUDED
