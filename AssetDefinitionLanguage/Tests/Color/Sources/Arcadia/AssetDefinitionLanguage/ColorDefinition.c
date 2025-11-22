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

#include "Arcadia/AssetDefinitionLanguage/ColorDefinition.h"

static void
Arcadia_AssetDefinitionLanguage_ColorDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_ColorDefinition* self
  );

static void
Arcadia_AssetDefinitionLanguage_ColorDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_ColorDefinition* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_AssetDefinitionLanguage_ColorDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_AssetDefinitionLanguage_ColorDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.AssetDefinitionLanguage.ColorDefinition", Arcadia_AssetDefinitionLanguage_ColorDefinition,
                         u8"Arcadia.AssetDefinitionLanguage.Definition", Arcadia_AssetDefinitionLanguage_Definition,
                         &_typeOperations);

static void
Arcadia_AssetDefinitionLanguage_ColorDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_ColorDefinition* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_AssetDefinitionLanguage_ColorDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_AssetDefinitionLanguage_ColorDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_AssetDefinitionLanguage_ColorDefinition_getType(thread);
  {
    Arcadia_Value t = Arcadia_ValueStack_getValue(thread, 1);
    Arcadia_ValueStack_pushValue(thread, &t);
    Arcadia_ValueStack_pushNatural8Value(thread, 1);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 4 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->blue = Arcadia_ValueStack_getNatural8Value(thread, 4);
  self->green = Arcadia_ValueStack_getNatural8Value(thread, 3);
  self->red = Arcadia_ValueStack_getNatural8Value(thread, 2);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 4 + 1);
}

Arcadia_AssetDefinitionLanguage_ColorDefinition*
Arcadia_AssetDefinitionLanguage_ColorDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_String* name,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, red);
  Arcadia_ValueStack_pushNatural8Value(thread, green);
  Arcadia_ValueStack_pushNatural8Value(thread, blue);
  Arcadia_ValueStack_pushNatural8Value(thread, 4);
  ARCADIA_CREATEOBJECT(Arcadia_AssetDefinitionLanguage_ColorDefinition);
}

#include "Arcadia/DDL/Include.h"

// (1) check that node is a map
// (1) check that only entries with keys specified in "keys" are in the map.
// (1) check that no two entries are in the map which have the same key.
static void
checkMap
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_Node* node,
    Arcadia_Set* required
  )
{
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)node, _Arcadia_DDL_MapNode_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  // Add entries (key,true) for all the keys.
  Arcadia_Map* symbols = (Arcadia_Map*)Arcadia_HashMap_create(thread, Arcadia_Value_makeVoidValue(Arcadia_VoidValue_Void));
  Arcadia_DDL_MapNode* mapNode = (Arcadia_DDL_MapNode*)node;
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
        (
          thread,
          (Arcadia_List*)mapNode->entries,
          i,
          _Arcadia_DDL_MapEntryNode_getType(thread)
        );
    Arcadia_DDL_NameNode* key = mapEntryNode->key;
    // If the key is in the received map already, raise an error. Otherwise add the key.
    Arcadia_Value k = Arcadia_Value_makeObjectReferenceValue(key->value);
    Arcadia_Value v = Arcadia_Value_makeObjectReferenceValue(mapEntryNode->value);
    Arcadia_Value result = Arcadia_Map_get(thread, symbols, k);
    if (!Arcadia_Value_isVoidValue(&result)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    } else {
      Arcadia_Map_set(thread, symbols, k, v, NULL, NULL);
    }
    // If the name of the key is not in the map.
    if (!Arcadia_Set_contains(thread, required, k)) {
      Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
      Arcadia_Thread_jump(thread);
    }
  }
}

static Arcadia_Natural8Value
getNatural8Value
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
        (
          thread,
          (Arcadia_List*)mapNode->entries,
          i,
          _Arcadia_DDL_MapEntryNode_getType(thread)
        );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_NumberNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_NumberNode* numberNode = (Arcadia_DDL_NumberNode*)valueNode;
      return Arcadia_String_toNatural8(thread, numberNode->value);
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

static Arcadia_String*
getStringValue
  (
    Arcadia_Thread* thread,
    Arcadia_DDL_MapNode* mapNode,
    Arcadia_String* key
  )
{
  for (Arcadia_SizeValue i = 0, n = Arcadia_Collection_getSize(thread, (Arcadia_Collection*)mapNode->entries); i < n; ++i) {
    Arcadia_DDL_MapEntryNode* mapEntryNode =
      (Arcadia_DDL_MapEntryNode*)
      Arcadia_List_getObjectReferenceValueCheckedAt
      (
        thread,
        (Arcadia_List*)mapNode->entries,
        i,
        _Arcadia_DDL_MapEntryNode_getType(thread)
      );
    Arcadia_DDL_NameNode* keyNode = mapEntryNode->key;
    Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(key);
    if (Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)keyNode->value, &t)) {
      Arcadia_DDL_Node* valueNode = mapEntryNode->value;
      if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)valueNode, _Arcadia_DDL_StringNode_getType(thread))) {
        Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
        Arcadia_Thread_jump(thread);
      }
      Arcadia_DDL_StringNode* stringNode = (Arcadia_DDL_StringNode*)valueNode;
      return stringNode->value;
    }
  }
  Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
  Arcadia_Thread_jump(thread);
}

Arcadia_AssetDefinitionLanguage_ColorDefinition*
Arcadia_AssetDefinitionLAnguage_ColorDefinition_parse
  (
    Arcadia_Thread* thread,
    Arcadia_String* input
  )
{
  Arcadia_DDL_Parser* parser = Arcadia_DDL_Parser_create(thread);

  Arcadia_DDL_Parser_setInput(thread, parser, input);
  Arcadia_DDL_Node* node = Arcadia_DDL_Parser_run(thread, parser);

  Arcadia_String* TYPE = Arcadia_String_createFromCxxString(thread, "type"),
                * NAME = Arcadia_String_createFromCxxString(thread, "name"),
                * RED = Arcadia_String_createFromCxxString(thread, "red"),
                * GREEN = Arcadia_String_createFromCxxString(thread, "green"),
                * BLUE = Arcadia_String_createFromCxxString(thread, "blue");

  Arcadia_Set* required = (Arcadia_Set*)Arcadia_HashSet_create(thread);
  Arcadia_Set_add(thread, required, Arcadia_Value_makeObjectReferenceValue(TYPE), NULL);
  Arcadia_Set_add(thread, required, Arcadia_Value_makeObjectReferenceValue(NAME), NULL);
  Arcadia_Set_add(thread, required, Arcadia_Value_makeObjectReferenceValue(RED), NULL);
  Arcadia_Set_add(thread, required, Arcadia_Value_makeObjectReferenceValue(GREEN), NULL);
  Arcadia_Set_add(thread, required, Arcadia_Value_makeObjectReferenceValue(BLUE), NULL);
  checkMap(thread, node, required);

  Arcadia_String* type = getStringValue(thread, (Arcadia_DDL_MapNode*)node, TYPE);
  Arcadia_String* name = getStringValue(thread, (Arcadia_DDL_MapNode*)node, NAME);
  Arcadia_Natural8Value red = getNatural8Value(thread, (Arcadia_DDL_MapNode*)node, RED);
  Arcadia_Natural8Value green = getNatural8Value(thread, (Arcadia_DDL_MapNode*)node, GREEN);
  Arcadia_Natural8Value blue = getNatural8Value(thread, (Arcadia_DDL_MapNode*)node, BLUE);
  Arcadia_Value t = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Types.Color"));
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)type, &t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }

  return
    Arcadia_AssetDefinitionLanguage_ColorDefinition_create
      (
        thread,
        name,
        red,
        green,
        blue
      );
}
