/**
 * Author: mysticalCabinboy
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <macro_collections.h>
#include "raylib.h"

#include "Violet/Rendering.h"
#include "utl_futils.h"

#define MODEL_LIST_PARAMS (mlist,ModelList,,,Model)
C_MACRO_COLLECTIONS_EXTENDED(CMC, LIST, MODEL_LIST_PARAMS, (STR));
#define RENDER_POOL_PARAMS (dlist,DrawableList,,,Drawable)
C_MACRO_COLLECTIONS_EXTENDED(CMC, LIST, RENDER_POOL_PARAMS, (STR));

#define REGISTRY_MAP_PARAMS (mreg,ModelRegistry, , char*, u32)
C_MACRO_COLLECTIONS_EXTENDED(CMC, HASHMAP, REGISTRY_MAP_PARAMS, (STR));

typedef uint32_t u32;

Drawable defaultDrawable;
/////////////////////////////////////////////////////////////////////////////////////////
// Renderer structure and data layout
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct Renderer {
    struct DrawableList* data;

    Registry* registry;
    u32 registryLastID;

    struct ModelList* modelPool;
} Renderer;

static Renderer renderer;

void VGRSetup(int width, int height, const char* title){
    renderer.data = dlist_new(2, 
    &(struct DrawableList_fval){
    });

    renderer.registry = registryAPI.init();
    renderer.registryLastID = 1;
    
    renderer.modelPool = mlist_new(1, 
    &(struct ModelList_fval){});
}

u32 VGRRegisterModel(char* registryName, Model* model){
    u32 newID = renderer.registryLastID;
    renderer.registryLastID++;
    // Associate the registry name with its new id
    // To keep order, ensure it is the largest ID
    registryAPI.addEntry(renderer.registry, registryName,newID);

    return newID;
}

u32 VGRRegisterModelWithID(char* registryName, u32 registryID, Model* model){
    if(VGRGetModelByID(registryID)){
        printf("Error!: Attempt to register two models by the same id!\n New model registry name: %s\nModelID: %d", registryName, registryID);
    }
    registryAPI.addEntry(renderer.registry, registryName,registryID);

    return registryID;
}

u32 VGRGetModelID(char* registryName){
    return registryAPI.getEntry(renderer.registry,registryName);
}

Model* VGRGetModelByID(u32 modelID){
    return mlist_get_ref(renderer.modelPool, modelID);
}

void VGRUnloadModel(char* registryName){
    u32 modelID = VGRGetModelID(registryName);
    if(modelID != 0){
        registryAPI.deleteEntry(renderer.registry, registryName);
    }
}

void VGRCleanupRenderer(){
    registryAPI.delete(renderer.registry);

    dlist_free(renderer.data);
    mlist_free(renderer.modelPool);
}

void VGRSetDrawFunc(Drawable drawable, void (*drawFunc)(Transform)){
    drawable.drawFunc = drawFunc;    
}

Drawable VGRCreateDrawableByName(char* registryname){
    u32 id = registry.getEntry(registryname);
    return VGRCreateDrawable(id);
}

Drawable VGRCreateDrawable(u32 rendererID){
    Drawable newDrawable = (Drawable){.modelID = rendererID, .drawFunc = defaultDrawable.drawFunc};
    dlist_push_back(renderer.data, newDrawable);
    return newDrawable;
}

Drawable VGRCreateDrawableByCopy(Drawable drawable){
    return (Drawable){.modelID = drawable.modelID, .drawFunc = drawable.drawFunc};
}

u32 VGRGetDrawableModelID(Drawable drawable){
    return drawable.modelID;
}

void VGRBeginRendering(){
    //TODO: Unimplemented
}

void VGRDraw(){
    //TODO: Unimplemented
}

void VGREndRendering(){
    //TODO: Unimplemented
}

bool VGRWindowShouldClose(){
    return WindowShouldClose();
}

void VGRClearBackground(Color color){
    ClearBackground(color);
}
