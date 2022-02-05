#ifndef VIOLET_RENDERING_H
#define VIOLET_RENDERING_H
/**
 * Primary rendering API.
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
 * Data SHALL NOT be modified during the rendering stage to allow for threading.
 *
 *
 * Loading and rendering stage are part of the same loop,
 * but still are done separately.
 *
 * Author: mysticalCabinboy
 * Version: 0.0.1
 **/

#include <stdint.h>
#include "raylib.h"

typedef uint32_t u32;

typedef struct Drawable {
    // DO NOT CHANGE DIRECTLY
    int rendererID;

    // FIXME: Modifiable(currently) but should be modified through function.
    Transform* transform;
} Drawable;

/////////////////////////////////////////////////////////////////////////////////////////
// Registry/Cleanup stage functions
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * Setup all prerequisite render API calls for the renderer to work.
 **/
// Note: Given all this is supposed to be API calls and memory setup, should not be unit tested.
void VGRSetupRenderer();

/**
 * Registers a model.
 * @param  const char* a registry name for the model
 * @param  Model a fully loaded model struct to register.
 * @return uint32_t the models ID in the registry.
 */
u32 VGRRegisterModel(const char* registryName , Model model);

/**
 * Registers a model to a specific ID in the registry.
 * @param  const char* a registry name for the model
 * @param  uint32_t a pre_set registryID
 * @param  Model a fully loaded model struct to register.
 * @return uint32_t the models ID in the registry.
 * @error  If a model already has a given ID, throws an error and returns NULL
 */
u32 VGRRegisterModelWithID(const char* registryName , u32 registryID, Model model);

/**
 * Gives a id from the registryName
 * If registryName does not exist, return 0
 **/
u32 VGRGetModelID(char* registryName);

/**
 * Frees the model data and removes the model with the given name
 * from the registry pool.
 **/
void VGRUnloadModel(const char* registryName);

/**
 * Frees the model data and removes the model with the given RendererID
 * from the registry pool.
 **/
void VGRUnloadModelByID(u32 rendererID);

/**
 * Frees ALL model data from the registry and deallocates all memory in the renderer
 **/
void VGRCleanupRenderer();

/////////////////////////////////////////////////////////////////////////////////////////
// Loading stage functions
/////////////////////////////////////////////////////////////////////////////////////////
/**
 * Tells the renderer to create a new "Drawable" in render state
 * @param const char* the registry name of the model to draw
 * @param Transform   the initial location of the new drawable
 * @return Drawable   the drawable with the render ID and modifiable data
 **/
Drawable VGRCreateDrawable(const char* registryName, Transform transform);

/**
 * Tells the renderer to create a new "Drawable" in render state
 * @param uint32_t    the internal model ID
 * @param Transform   the initial location of the new drawable
 * @return Drawable   the drawable with the render ID and modifiable data
 **/
Drawable VGRCreateDrawableByID(u32 rendererID, Transform transform);

/**
 * Tells the renderer to create a new "Drawable" in render state
 * @param Drawable    the drawable to copy from
 * @param Transform   the initial location of the new drawable
 * @return Drawable   the drawable with the render ID and modifiable data
 **/
Drawable VGRCreateDrawableByCopy(Drawable drawable, Transform transform);


/**
 * Gives the model ID the Drawable is associated with
 * @param Drawable a valid drawable
 **/
u32 VGRGetDrawableModelID(Drawable drawable);
/////////////////////////////////////////////////////////////////////////////////////////
// Rendering stage functions
/////////////////////////////////////////////////////////////////////////////////////////
/*
 * REMINDER:
 * For future me(and other devs)
 * VGRDraw() should be where all render backend calls should be used.
 * Otherwise unit testing becomes...wierd.
 * VGRBeginRendering() and VGREndRendering() are for
 * Violet code only.
 *
 * TODO: find other ways to implement library functions such as Text.
 **/

/**
 * Designates the beginning of the render stage
 * The render state should not change during drawing.
 *
 **/
void VGRBeginRendering();

/**
 * Loops through the entire render state and does a draw call on everything.
 **/
void VGRDraw();

/**
 * Designates the end of the render stage.
 * Any modifications to render state during the last frame are applied here.
 **/
void VGREndRendering();





#endif // VIOLET_RENDERING_H
