#include "Arcadia/Engine/Demo/Scene.h"

static void
Arcadia_Engine_Demo_Scene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  );

static void
Arcadia_Engine_Demo_Scene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  );
  

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_Scene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Engine_Demo_Scene_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_Scene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_Scene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_Scene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_Arcadia_Engine_Demo_Scene_typeOperations);

static void
Arcadia_Engine_Demo_Scene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_Scene_getType(thread);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->engine = Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_Engine_getType(thread));
  self->updateLogic = NULL;
  self->updateGraphics = NULL;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_Engine_Demo_Scene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  )
{
  if (self->engine) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->engine);
  }
}

void
Arcadia_Engine_Demo_Scene_updateLogic
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self
  )
{ self->updateLogic(thread, self); }

void
Arcadia_Engine_Demo_Scene_updateGraphics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_Scene* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{ self->updateGraphics(thread, self, width, height); }
