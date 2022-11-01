/**
 * Author: mysticalCabinboy
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"

#include "Violet/Rendering.h"
#include "Violet/Rendering/Registry.h"
#include "Violet/Rendering/EntityPool.h"


typedef uint32_t u32;
/////////////////////////////////////////////////////////////////////////////////////////
// Renderer structure and data layout
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct Renderer {
    u32* modelID;
    Transform* transforms;
    u32 model_s;

    Registry* registry;
    u32 registryLastID;

    EntityPool* modelPool;
} Renderer;

static Renderer renderer;

void VGRSetupRenderer(int width, int height, const char* title){
    renderer.modelID = NULL;
    renderer.transforms = 0;
    renderer.model_s = 0;

    renderer.registry = registryAPI.init();
    renderer.registryLastID = 1;

    renderer.modelPool = poolAPI.init(sizeof(Model));
}

u32 VGRRegisterModel(char* registryName, Model* model){
    u32 newID = renderer.registryLastID;
    renderer.registryLastID++;
    // Associate the registry name with its new id
    // To keep order, ensure it is the largest ID
    registryAPI.addEntry(renderer.registry, registryName,newID);

    poolAPI.addObject(renderer.modelPool, newID, model);

    return newID;
}

u32 VGRRegisterModelWithID(char* registryName, u32 registryID, Model* model){
    if(VGRGetModelByID(registryID)){
        printf("Error!: Attempt to register two models by the same id!\n New model registry name: %s\nModelID: %d", registryName, registryID);
    }
    registryAPI.addEntry(renderer.registry, registryName,registryID);
    poolAPI.addObject(renderer.modelPool,registryID, model);

    return registryID;
}

u32 VGRGetModelID(char* registryName){
    return registryAPI.getEntry(renderer.registry,registryName);
}

Model* VGRGetModelByID(u32 modelID){
    return poolAPI.get(renderer.modelPool, modelID);
}

void VGRUnloadModel(char* registryName){
    u32 modelID = VGRGetModelID(registryName);
    if(modelID != 0){
        registryAPI.deleteEntry(renderer.registry, registryName);
        poolAPI.removeObject(renderer.modelPool, modelID);
    }
}

void VGRCleanupRenderer(){
    registryAPI.delete(renderer.registry);
    poolAPI.destroy(renderer.modelPool);

    free(renderer.modelID);
    free(renderer.transforms);
}

Drawable VGRCreateDrawableByName(char* registryname, Transform transform){
    //TODO: Unimplemented
    return (Drawable){};
}

Drawable VGRCreateDrawable(u32 rendererID, Transform transform){
    //TODO: Unimplemented
    return (Drawable){};
}

Drawable VGRCreateDrawableByCopy(Drawable drawable, Transform transform){
    //TODO: Unimplemented
    return (Drawable){};
}

u32 VGRGetDrawableModelID(Drawable drawable){
    //TODO: Unimplemented
    return 0;
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
