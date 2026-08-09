// The author of this software is Michael Heilmann (contact@michaelheilmann.com).
//
// Copyright(c) 2024-2026 Michael Heilmann (contact@michaelheilmann.com).
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

#include "Arcadia/MILC/Backend/SymbolInfo.h"

#include "Arcadia/MILC/Include.h"
#include "Arcadia/MILC/Backend/Implementation.h"
#include "Arcadia/MILC/AST/Include.h"
#include <assert.h>

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfoDispatch* self
  );

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static Arcadia_MILC_Backend_SymbolInfo*
getModuleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static Arcadia_FilePath*
getCxxHeaderFilePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static Arcadia_FilePath*
getCxxHeaderFileAbsolutePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static Arcadia_FilePath*
getCxxSourceFilePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static Arcadia_FilePath*
getCxxSourceFileAbsolutePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  );

static const Arcadia_ObjectType_Operations _objectTypeOperations = {
  Arcadia_ObjectType_Operations_Initializer,
  .construct = (Arcadia_Object_ConstructCallbackFunction*)&constructImpl,
  .destruct = (Arcadia_Object_DestructCallbackFunction*)&destructImpl,
  .initializeDispatch = (Arcadia_ObjectDispatch_InitializeCallbackFunction*)&initializeDispatchImpl,
  .visit = (Arcadia_Object_VisitCallbackFunction*)&visitImpl,
};

static const Arcadia_Type_Operations _typeOperations = {
  Arcadia_Type_Operations_Initializer,
  .objectTypeOperations = &_objectTypeOperations,
};

Arcadia_defineObjectType(u8"Arcadia.MILC.Backend.SymbolInfo", Arcadia_MILC_Backend_SymbolInfo,
                         u8"Arcadia.Object", Arcadia_Object,
                         &_typeOperations);

static void
constructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{
  Arcadia_EnterConstructor(Arcadia_MILC_Backend_SymbolInfo);
  {
    Arcadia_ValueStack_pushNatural8Value(thread, 0);
    Arcadia_superTypeConstructor(thread, _type, self);
  }
  if (2 != _numberOfArguments) {
    Arcadia_Thread_setStatus(thread, Arcadia_Status_NumberOfArgumentsInvalid);
    Arcadia_Thread_jump(thread);
  }
  self->context = (Arcadia_MILC_Context*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 2, _Arcadia_MILC_Context_getType(thread));
  self->symbol = (Arcadia_MILC_Symbol*)Arcadia_ValueStack_getObjectReferenceValueChecked(thread, 1, _Arcadia_MILC_Symbol_getType(thread));
  Arcadia_LeaveConstructor(Arcadia_MILC_Backend_SymbolInfo);
}

static void
initializeDispatchImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfoDispatch* self
  )
{
  self->getModule = &getModuleImpl;
  self->getCxxHeaderFilePath = &getCxxHeaderFilePathImpl;
  self->getCxxHeaderFileAbsolutePath = &getCxxHeaderFileAbsolutePathImpl;
  self->getCxxSourceFilePath = &getCxxSourceFilePathImpl;
  self->getCxxSourceFileAbsolutePath = &getCxxSourceFileAbsolutePathImpl;
}

static void
destructImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{/*Intentionally empty.*/}

static void
visitImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{
  if (self->context) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->context);
  }

  if (self->symbol) {
    Arcadia_Object_visit(thread, (Arcadia_Object*)self->symbol);
  }
}

static Arcadia_MILC_Backend_SymbolInfo*
getModuleImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{
  if (Arcadia_MILC_Backend_SymbolInfo_isBuiltIn(thread, self)) {
    return NULL;
  }
  Arcadia_MILC_Symbol* moduleSymbol = Arcadia_MILC_Backend_SymbolInfo_getSymbol(thread, self);
  assert(NULL != moduleSymbol);
  while (moduleSymbol->kind != Arcadia_MILC_SymbolKind_Module) {
    moduleSymbol = moduleSymbol->enclosing;
  }
  Arcadia_MILC_Backend_Implementation* implementation = Arcadia_MILC_Backend_Implementation_getInstance(thread, self->context);
  Arcadia_MILC_Backend_SymbolInfo* moduleSymbolInfo =
    (Arcadia_MILC_Backend_SymbolInfo*)
    Arcadia_Map_getObjectReferenceValueChecked
      (
        thread,
        implementation->symbolInfos,
        Arcadia_Value_makeObjectReferenceValue(moduleSymbol),
        _Arcadia_MILC_Backend_SymbolInfo_getType(thread)
      );
  assert(NULL != moduleSymbolInfo);
  return moduleSymbolInfo;
}

static Arcadia_FilePath*
getCxxHeaderFilePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ return NULL; }

static Arcadia_FilePath*
getCxxHeaderFileAbsolutePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ return NULL; }

static Arcadia_FilePath*
getCxxSourceFilePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ return NULL; }

static Arcadia_FilePath*
getCxxSourceFileAbsolutePathImpl
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ return NULL; }

Arcadia_MILC_Backend_SymbolInfo*
Arcadia_MILC_Backend_SymbolInfo_create
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Context* context,
    Arcadia_MILC_Symbol* symbol
  )
{
  _Arcadia_BeginCreate(Arcadia_MILC_Backend_SymbolInfo);
  if (context) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)context); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  if (symbol) Arcadia_ValueStack_pushObjectReferenceValue(thread, (Arcadia_Object*)symbol); else Arcadia_ValueStack_pushVoidValue(thread, Arcadia_VoidValue_Void);
  Arcadia_ValueStack_pushNatural8Value(thread, 2);
  _Arcadia_EndCreate(Arcadia_MILC_Backend_SymbolInfo); 
}

void
Arcadia_MILC_Backend_SymbolInfo_dump
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self,
    Arcadia_SizeValue indent,
    Arcadia_StringBuilder* target
  )
{ Arcadia_VirtualCall(Arcadia_MILC_Backend_SymbolInfo, dump, self, indent, target); }

Arcadia_MILC_Symbol*
Arcadia_MILC_Backend_SymbolInfo_getSymbol
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getSymbol, self); }

Arcadia_String*
Arcadia_MILC_Backend_SymbolInfo_getCxxName
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxName, self); }

Arcadia_String*
Arcadia_MILC_Backend_SymbolInfo_getCxxNameUpperCase
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxNameUpperCase, self); }

Arcadia_MILC_Backend_SymbolInfo*
Arcadia_MILC_Backend_SymbolInfo_getModule
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getModule, self); }

Arcadia_FilePath*
Arcadia_MILC_Backend_SymbolInfo_getCxxHeaderFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxHeaderFilePath, self); }

Arcadia_FilePath*
Arcadia_MILC_Backend_SymbolInfo_getCxxHeaderFileAbsolutePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxHeaderFileAbsolutePath, self); }

Arcadia_FilePath*
Arcadia_MILC_Backend_SymbolInfo_getCxxSourceFilePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxSourceFilePath, self); }

Arcadia_FilePath*
Arcadia_MILC_Backend_SymbolInfo_getCxxSourceFileAbsolutePath
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ Arcadia_VirtualCallWithReturn(Arcadia_MILC_Backend_SymbolInfo, getCxxSourceFileAbsolutePath, self); }

Arcadia_BooleanValue
Arcadia_MILC_Backend_SymbolInfo_isBuiltIn
  (
    Arcadia_Thread* thread,
    Arcadia_MILC_Backend_SymbolInfo* self
  )
{ 
  Arcadia_MILC_Symbols* symbols = Arcadia_MILC_Symbols_getInstance(thread, self->context);
  return Arcadia_MILC_Symbols_isBuiltIn(thread, symbols, self->symbol);
}
