Core_Result Core_KeyboardKeyMessage_getAction(Core_KeyboardKeyAction* RETURN, Core_KeyboardKeyMessage* SELF) {
  *RETURN = SELF->action;
  return Core_Success;
}

Core_Result Core_KeyboardKeyMessage_getKey(Core_KeyboardKey* RETURN, Core_KeyboardKeyMessage* SELF) {
  *RETURN = SELF->key;
  return Core_Success;
}
