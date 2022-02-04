#ifndef VIOLET_RENDERING_H
#define VIOLET_RENDERING_H
/**
 * Primary rendering backend.
 *
 * --------------------------
 * Registry Stage
 * --------------------------
 * Models need to be registered before they can be used
 * most parts of the game will have models submitted through VGRRegisterModel()
 * Additional textures and shaders will be similarly submitted in this way,
 * (VGRRegisterTexture(), VGRRegisterShader(), etc.)
 * This associates the asset with a name and an internal drawableID used by the renderer.
 *
 * This should typically happen at game load or a lazy method during level loading.
 *
 * --------------------------
 * Loading/Update Stage
 * --------------------------
 * Where most the action happens.
 *
 * Model Loading/Unloading:
 * Models will be referenced by their drawableID
 * then associated with a transform through VGRCreateModel()
 * The loading stage will also create a finished Drawable struct which will contain data such as:
 *  -- Render ID
 *  -- Transform Data
 *  -- function pointer defining unique behavior (if null does nothing different)
 *
 * Drawables may also be unloaded at this stage,
 * Unloaded drawables will be marked to not be rendered.
 * The first unloaded model found in the render state should take this
 *
 *
 * --------------------------
 * Rendering Stage
 * --------------------------
 * the renderer will iterate through the entire render state and apply data as needed.
 * If the render state needs to be modified, these modifications are added to a queue
 * and then applied at the beginning of the next frame.
 *
 *
 * Loading and rendering stage are part of the same loop,
 * but still are done separately.
 *
 * Author: mysticalCabinboy
 * Version: 0.0.1
 **/

#include <cstdint>
#include "raylib.h"

//////////////////////////////////////////////////////////////////////
// Registry stage functions
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Loading stage functions
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
// Rendering stage functions
//////////////////////////////////////////////////////////////////////


#endif // VIOLET_RENDERING_H
