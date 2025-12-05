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

#include "Arcadia/ADL/ColorDefinition.h"

#include "Arcadia/DDL/Include.h"
#include "Arcadia/DDLS/Include.h"
#include "Arcadia/ADL/Definitions.h"

static const char* SCHEMA =
"{\n"
"  kind : \"Schema\",\n"
"  name : \"Color\",\n"
"  definition : {\n"
"    kind : \"Map\",\n"
"    entries : [\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"type\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"name\",\n"
"        type : {\n"
"          kind : \"String\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"red\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"green\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"      {\n"
"        kind : \"MapEntry\",\n"
"        name : \"blue\",\n"
"        type : {\n"
"          kind : \"Number\",\n"
"        },\n"
"      },\n"
"    ],\n"
"  },\n"
"}\n"
;

static void
Arcadia_ADL_ColorDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ColorDefinition* self
  );

static void
Arcadia_ADL_ColorDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ColorDefinition* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructorCallbackFunction*) & Arcadia_ADL_ColorDefinition_constructImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*) & Arcadia_ADL_ColorDefinition_visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.ADL.ColorDefinition", Arcadia_ADL_ColorDefinition,
                         u8"Arcadia.ADL.Definition", Arcadia_ADL_Definition,
                         &_typeOperations);

static void
Arcadia_ADL_ColorDefinition_visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ColorDefinition* self
  )
{/*Intentionally empty.*/}

static void
Arcadia_ADL_ColorDefinition_constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_ColorDefinition* self
  )
{
  Arcadia_TypeValue _type = _Arcadia_ADL_ColorDefinition_getType(thread);
  {
    Arcadia_Value definitions, name;
    definitions = Arcadia_ValueStack_getValue(thread, 5);
    name = Arcadia_ValueStack_getValue(thread, 4);
    Arcadia_ValueStack_pushValue(thread, &name);
    Arcadia_ValueStack_pushValue(thread, &definitions);
    Arcadia_ValueStack_pushNatural8Value(thread, 2);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (Arcadia_ValueStack_getSize(thread) < 1 || 5 != Arcadia_ValueStack_getNatural8Value(thread, 0)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->red = Arcadia_ValueStack_getNatural8Value(thread, 3);
  self->green = Arcadia_ValueStack_getNatural8Value(thread, 2);
  self->blue = Arcadia_ValueStack_getNatural8Value(thread, 1);
  Arcadia_Object_setType(thread, (Arcadia_Object*)self, _type);
  Arcadia_ValueStack_popValues(thread, 5 + 1);
}

Arcadia_ADL_ColorDefinition*
Arcadia_ADL_ColorDefinition_create
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* name,
    Arcadia_Natural8Value red,
    Arcadia_Natural8Value green,
    Arcadia_Natural8Value blue
  )
{
  Arcadia_SizeValue oldValueStackSize = Arcadia_ValueStack_getSize(thread);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)definitions);
  Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)name);
  Arcadia_ValueStack_pushNatural8Value(thread, red);
  Arcadia_ValueStack_pushNatural8Value(thread, green);
  Arcadia_ValueStack_pushNatural8Value(thread, blue);
  Arcadia_ValueStack_pushNatural8Value(thread, 5);
  ARCADIA_CREATEOBJECT(Arcadia_ADL_ColorDefinition);
}

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

static Arcadia_DDL_Node*
load
  (
    Arcadia_Thread* thread,
    Arcadia_String* ddlSource,
    Arcadia_String* ddlsSource
  )
{
  Arcadia_DDL_DefaultReader* ddlReader = (Arcadia_DDL_DefaultReader*)Arcadia_DDL_DefaultReader_create(thread);
  Arcadia_DDL_Node* ddlNode = Arcadia_DDL_DefaultReader_run(thread, ddlReader, ddlSource);

  Arcadia_DDLS_DefaultReader* ddlsReader = (Arcadia_DDLS_DefaultReader*)Arcadia_DDLS_DefaultReader_create(thread);
  Arcadia_DDLS_Node* ddlsNode = Arcadia_DDLS_DefaultReader_run(thread, ddlsReader, ddlsSource);
  if (!Arcadia_Object_isInstanceOf(thread, (Arcadia_Object*)ddlsNode, _Arcadia_DDLS_SchemaNode_getType(thread))) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_ArgumentTypeInvalid);
    Arcadia_Thread_jump(thread);
  }

  Arcadia_DDLS_ValidationContext* ddlsValidator = Arcadia_DDLS_ValidationContext_create(thread);
  Arcadia_DDLS_ValidationContext_addSchema(thread, ddlsValidator, (Arcadia_DDLS_SchemaNode*)ddlsNode);
  Arcadia_DDLS_ValidationContext_run(thread, ddlsValidator, Arcadia_String_createFromCxxString(thread, "Color"), ddlNode);

  return ddlNode;
}

Arcadia_ADL_ColorDefinition*
Arcadia_ADL_ColorDefinition_parse
  (
    Arcadia_Thread* thread,
    Arcadia_ADL_Definitions* definitions,
    Arcadia_String* input
  )
{
  
  Arcadia_DDL_Node* ddlNode = load(thread, input, Arcadia_String_createFromCxxString(thread, SCHEMA));
  Arcadia_String* TYPE = Arcadia_String_createFromCxxString(thread, "type"),
                * NAME = Arcadia_String_createFromCxxString(thread, "name"),
                * RED = Arcadia_String_createFromCxxString(thread, "red"),
                * GREEN = Arcadia_String_createFromCxxString(thread, "green"),
                * BLUE = Arcadia_String_createFromCxxString(thread, "blue");

  Arcadia_String* type = getStringValue(thread, (Arcadia_DDL_MapNode*)ddlNode, TYPE);
  Arcadia_String* name = getStringValue(thread, (Arcadia_DDL_MapNode*)ddlNode, NAME);
  Arcadia_Natural8Value red = getNatural8Value(thread, (Arcadia_DDL_MapNode*)ddlNode, RED);
  Arcadia_Natural8Value green = getNatural8Value(thread, (Arcadia_DDL_MapNode*)ddlNode, GREEN);
  Arcadia_Natural8Value blue = getNatural8Value(thread, (Arcadia_DDL_MapNode*)ddlNode, BLUE);
  Arcadia_Value t;
  // Assert the definition has the correct type.
  t = Arcadia_Value_makeObjectReferenceValue(Arcadia_String_createFromCxxString(thread, u8"Color"));
  if (!Arcadia_Object_isEqualTo(thread, (Arcadia_Object*)type, &t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_SemanticalError);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_ADL_ColorDefinition* definition = Arcadia_ADL_ColorDefinition_create(thread, definitions, name, red, green, blue);
  // Assert there is no definition of the same name in the definitions.
  t = Arcadia_Map_get(thread, definitions->definitions, Arcadia_Value_makeObjectReferenceValue(name));
  if (!Arcadia_Value_isVoidValue(&t)) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_Exists);
    Arcadia_Thread_jump(thread);
  }
  Arcadia_Map_set(thread, definitions->definitions, Arcadia_Value_makeObjectReferenceValue(name), Arcadia_Value_makeObjectReferenceValue(definitions), NULL, NULL);
  return definition;
}
