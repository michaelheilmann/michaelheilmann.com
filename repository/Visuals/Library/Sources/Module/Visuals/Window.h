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

#if !defined(ARCADIA_VISUALS_WINDOW_H_INCLUDED)
#define ARCADIA_VISUALS_WINDOW_H_INCLUDED

#include "Arcadia/Ring2/Include.h"
#include "Module/Visuals/Icon.h"
#include "Module/Visuals/PixelBuffer.h"

// An instance of "NativeWindow" is in "closed" state when it is created.
// A successful call to "NativeWindow_open" puts the window in "opened" state.
// The window is put in "closed" state if it is destructed or by a successful call to "NativeWindow_close".
Arcadia_declareObjectType(u8"Arcadia.Visuals.Window", Arcadia_Visuals_Window, u8"Arcadia.Object");

struct Arcadia_Visuals_Window {
  Arcadia_Object _parent;

  void (*open)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*close)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  Arcadia_BooleanValue (*getQuitRequested)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*setQuitRequested)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_BooleanValue);

  void (*update)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*getRequiredBigIconSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*getRequiredSmallIconSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  Arcadia_Visuals_Icon* (*getBigIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*setBigIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*);

  Arcadia_Visuals_Icon* (*getSmallIcon)(Arcadia_Thread*, Arcadia_Visuals_Window* self);
  void (*setSmallIcon)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Visuals_Icon*);

  Arcadia_String* (*getTitle)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*setTitle)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_String*);

  void (*getCanvasSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*beginRender)(Arcadia_Thread*, Arcadia_Visuals_Window*);
  void (*endRender)(Arcadia_Thread*, Arcadia_Visuals_Window*);

  void (*setPosition)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getPosition)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

  void (*setSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value, Arcadia_Integer32Value);
  void (*getSize)(Arcadia_Thread*, Arcadia_Visuals_Window*, Arcadia_Integer32Value*, Arcadia_Integer32Value*);

};

/// @brief Ensure this window is opened.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_open
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Ensure this window is closed.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_close
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Get if this application should quit.
/// @param self A pointer to this window.
/// @return #Arcadia_BooleanValue_True if this application was requested to quit. #Arcadia_BooleanValue_False if this application was requested to continue.
Arcadia_BooleanValue
Arcadia_Visuals_Window_getQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set if the application should quit.
/// @param self A pointer to this window.
/// @param quitRequested #Arcadia_BooleanValue requests the application to quit. #Arcadia_BooleanValue_False request the application to continue.
void
Arcadia_Visuals_Window_setQuitRequested
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_BooleanValue quitRequested
  );

/// @brief Update this window.
/// @param self A pointer to this window.
void
Arcadia_Visuals_Window_update
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Get the size (width and height), in pixels, of a big window icon.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @post
/// On Success:
/// - <code>*width</code> was assigned the width, in pixels, required for a big window icon.
/// - <code>*height</code> was assigned the height, in pixels, required for a big window icon.
void
Arcadia_Visuals_Window_getRequiredBigIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get the size (width and height), in pixels, of a small window icon.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// @post
/// On Success:
/// - <code>*width</code> was assigned the width, in pixels, required for a small window icon.
/// - <code>*height</code> was assigned the height, in pixels, required for a small window icon.
void
Arcadia_Visuals_Window_getRequiredSmallIconSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Get the big icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set or remove the big icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
Arcadia_Visuals_Window_setBigIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  );

/// @brief Get the small icon.
/// @param self A pointer to this window.
/// @return A pointer to the icon that is currently assigned. A null pointer of no icon is currently assigned.
Arcadia_Visuals_Icon*
Arcadia_Visuals_Window_getSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set or remove the small icon.
/// @param self A pointer to this window.
/// @param icon A pointer to the icon to be assigned.
/// Pass a null pointer to remove the icon that is currently assigned.
void
Arcadia_Visuals_Window_setSmallIcon
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Visuals_Icon* icon
  );

/// @brief Get the title.
/// @param self A pointer to this window.
/// @return The title.
Arcadia_String*
Arcadia_Visuals_Window_getTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set the title.
/// @param self A pointer to this window.
/// @param title The title.
void
Arcadia_Visuals_Window_setTitle
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_String* title
  );

/// @brief Get the canvas size.
/// @param self A pointer to this window.
/// @param width A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the width, in pixels, of the canvas.
/// @param height A pointer to a <code>Arcadia_Integer32Value</code> variable.
/// On success, that variable is assigned the height, in pixels, of the canvas.
void
Arcadia_Visuals_Window_getCanvasSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

/// @brief Begin rendering to this window.
/// @param self A pointer to ths window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
Arcadia_Visuals_Window_beginRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief End rendering to this window.
/// @param self A pointer to this window.
/// @warning The successful calls to Window_beginRender and Window_endRender must be balanced.
void
Arcadia_Visuals_Window_endRender
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self
  );

/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param left, top Arcadia_Integer32Value values.
/// @post
/// This window was assigned the left position @a left.
/// This window was assigned the top position @ top.
void
Arcadia_Visuals_Window_setPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value left,
    Arcadia_Integer32Value top
  );


/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param left, top Pointers to Arcadia_Integer32Value variables.
/// @post
/// <code>*left</code> was assigned the left position of this window.
/// <code>*top</code> was assigned the top position of this window.
void
Arcadia_Visuals_Window_getPosition
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* left,
    Arcadia_Integer32Value* top
  );

/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param width, height Arcadia_Integer32Value values.
/// @post
/// This window was assigned the width @a width.
/// This window was assigned the height @ height.
void
Arcadia_Visuals_Window_setSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value width,
    Arcadia_Integer32Value height
  );

/// @brief Set the position of this window.
/// @param self A pointer to this window.
/// @param width, height Pointers to Arcadia_Integer32Value variables.
/// @post
/// <code>*width</code> was assigned the width of this window.
/// <code>*height</code> was assigned the height of this window.
void
Arcadia_Visuals_Window_getSize
  (
    Arcadia_Thread* thread,
    Arcadia_Visuals_Window* self,
    Arcadia_Integer32Value* width,
    Arcadia_Integer32Value* height
  );

#endif // ARCADIA_VISUALS_WINDOW_H_INCLUDED
