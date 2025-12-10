#include "Arcadia/Engine/Demo/MainScene.h"

static void
Arcadia_Engine_Demo_MainScene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  );

static void
Arcadia_Engine_Demo_MainScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  );

static void
Arcadia_Engine_Demo_MainScene_updateGraphics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

static void
Arcadia_Engine_Demo_MainScene_updateLogic
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  );  

static const Arcadia_ObjectType_Operations _Arcadia_Engine_Demo_MainScene_objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*)&Arcadia_Engine_Demo_MainScene_construct,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&Arcadia_Engine_Demo_MainScene_visit,
};

static const Arcadia_Type_Operations _Arcadia_Engine_Demo_MainScene_typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_Arcadia_Engine_Demo_MainScene_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.Engine.Demo.MainScene", Arcadia_Engine_Demo_MainScene,
                         u8"Arcadia.Engine.Demo.Scene", Arcadia_Engine_Demo_Scene,
                         &_Arcadia_Engine_Demo_MainScene_typeOperations);

static void
Arcadia_Engine_Demo_MainScene_construct
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_Engine_Demo_MainScene_getType(thread);
  {
    Arcadia_Value v = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &v);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 1 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  ((Arcadia_Engine_Demo_Scene*)self)->updateGraphics = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*, Arcadia_Integer32Value, Arcadia_Integer32Value)) & Arcadia_Engine_Demo_MainScene_updateGraphics;
  ((Arcadia_Engine_Demo_Scene*)self)->updateLogic = (void (*)(Arcadia_Thread*, Arcadia_Engine_Demo_Scene*))&Arcadia_Engine_Demo_MainScene_updateLogic;
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 1 + 1);
}

static void
Arcadia_Engine_Demo_MainScene_visit
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  )
{ }

static void
Arcadia_Engine_Demo_MainScene_updateGraphics
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  )
{
  Arcadia_Engine* engine = ((Arcadia_Engine_Demo_Scene*)self)->engine;
  Arcadia_Visuals_Scene_MeshContext* meshContext =
    Arcadia_Visuals_SceneNodeFactory_createMeshContext
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_MeshContext_setBackendContext(thread, (Arcadia_Visuals_Scene_MeshContext*)meshContext, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_MeshContext_render(thread, (Arcadia_Visuals_Scene_MeshContext*)meshContext); // TODO: Remove this.

  Arcadia_Visuals_Scene_ViewportNode* viewportNode1 =
    (Arcadia_Visuals_Scene_ViewportNode*)
    Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_ViewportNode* viewportNode2 =
    (Arcadia_Visuals_Scene_ViewportNode*)
    Arcadia_Visuals_SceneNodeFactory_createViewportNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );

  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)viewportNode1, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, viewportNode1, 255.f, 0.f, 0.f, 255.f);
  Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, viewportNode1, 0.f, 0.f, 0.5f, 1.f);
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, viewportNode1, width, height);

  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)viewportNode2, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_ViewportNode_setClearColor(thread, viewportNode2, 0.f, 255.f, 0.f, 255.f);
  Arcadia_Visuals_Scene_ViewportNode_setRelativeViewportRectangle(thread, viewportNode2, 0.5f, 0.f, 1.0f, 1.f);
  Arcadia_Visuals_Scene_ViewportNode_setCanvasSize(thread, viewportNode2, width, height);

  Arcadia_Visuals_Scene_CameraNode* cameraNode =
    (Arcadia_Visuals_Scene_CameraNode*)
    Arcadia_Visuals_SceneNodeFactory_createCameraNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_MeshNode* meshNode =
    (Arcadia_Visuals_Scene_MeshNode*)
    Arcadia_Visuals_SceneNodeFactory_createMeshNode
      (
        thread,
        (Arcadia_Visuals_SceneNodeFactory*)engine->visualsSceneNodeFactory,
        (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext
      );
  Arcadia_Visuals_Scene_Node_setBackendContext(thread, (Arcadia_Visuals_Scene_Node*)meshNode, (Arcadia_Visuals_BackendContext*)engine->visualsBackendContext);
  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, cameraNode, viewportNode1);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)viewportNode1, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)cameraNode, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, meshContext);

  Arcadia_Visuals_Scene_CameraNode_setViewport(thread, cameraNode, viewportNode2);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)viewportNode2, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)cameraNode, meshContext);
  Arcadia_Visuals_Scene_Node_render(thread, (Arcadia_Visuals_Scene_Node*)meshNode, meshContext);
}

static void
Arcadia_Engine_Demo_MainScene_updateLogic
  (
    Arcadia_Thread* thread,
    Arcadia_Engine_Demo_MainScene* self
  )
{/*Intentionally empty.*/}

Arcadia_Engine_Demo_MainScene*
Arcadia_Engine_Demo_MainScene_create
  (
    Arcadia_Thread* thread,
    Arcadia_Engine* engine
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  if (engine) {
    Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)engine);
  } else {
    Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  }
  Arcadia_ValueStack_pushNatural8Value(thread, 1);
  ARCADIA_CREATEOBJECT(Arcadia_Engine_Demo_MainScene);
}
