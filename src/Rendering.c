/**
 * Author: mysticalCabinboy
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "Violet/Rendering.h"

typedef uint32_t u32;
/////////////////////////////////////////////////////////////////////////////////////////
// Renderer structure and data layout
/////////////////////////////////////////////////////////////////////////////////////////
struct RegistryEntry {
    char* modelName;
    u32 modelID;
};

struct ModelPoolData {
    u32 modelID;
    Model data;
};

typedef struct Renderer {
    u32* modelID;
    Transform* transforms;
    u32 model_s;

    struct RegistryEntry* registry;
    u32 registry_s;
    u32 registryLastID;

    struct ModelPoolData* modelPool;
    u32 modelPool_s;
} Renderer;

static Renderer renderer;

void VGRSetupRenderer(int width, int height, const char* title){
    renderer.modelID = NULL;
    renderer.transforms = 0;
    renderer.model_s = 0;

    renderer.registry = NULL;
    renderer.registry_s = 0;
    renderer.registryLastID = 1;

    renderer.modelPool = NULL;
    renderer.modelPool_s = 0;
}

u32 VGRRegisterModel(char* registryName, Model model){
    if(renderer.registry == NULL){
        renderer.registry = calloc(1, sizeof(struct RegistryEntry));
        renderer.registry_s = 0;
        renderer.registryLastID = 1;
    }

    // Associate the registry name with its new id
    struct RegistryEntry newEntry;
    newEntry.modelName = registryName;
    newEntry.modelID = renderer.registryLastID;

    renderer.registry[renderer.registry_s] = newEntry;
    renderer.registry_s++;
    renderer.registryLastID++;

    // Load the model into the pool by the given ID.
    if(renderer.modelPool == NULL){
        renderer.modelPool = malloc(sizeof(struct ModelPoolData));
        renderer.modelPool_s = 0;
    }
    struct ModelPoolData newModel;
    newModel.modelID = newEntry.modelID;
    newModel.data = model;
    renderer.modelPool[renderer.modelPool_s] = newModel;
    renderer.modelPool_s++;

    return newModel.modelID;
}

u32 VGRRegisterModelWithID(char* registryName, u32 registryID, Model model){
    if(renderer.registry == NULL){
        renderer.registry = calloc(1, sizeof(struct RegistryEntry));
        renderer.registry_s = 0;
        renderer.registryLastID = 1;
    }

    if(VGRGetModelByID(registryID)){
        printf("Error!: Attempt to register two models by the same id!\n New model registry name: %s\nModelID: %s", registryName, registryID);
    }

    // Associate the registry name with its new id
    struct RegistryEntry newEntry;
    newEntry.modelName = registryName;
    newEntry.modelID = registryID;


    renderer.registry[renderer.registry_s] = newEntry;
    renderer.registry_s++;

    // Load the model into the pool by the given ID.
    if(renderer.modelPool == NULL){
        renderer.modelPool = malloc(sizeof(struct ModelPoolData));
        renderer.modelPool_s = 0;
    }
    struct ModelPoolData newModel;
    newModel.modelID = newEntry.modelID;
    newModel.data = model;
    renderer.modelPool[renderer.modelPool_s] = newModel;
    renderer.modelPool_s++;

    return newModel.modelID;
}

u32 VGRGetModelID(char* registryName){
    for(int i = 0; i < renderer.registry_s; i++){
        if(strcmp(renderer.registry[i].modelName,registryName)== 0){
            return renderer.registry[i].modelID;
        }
    }
    printf("Error: %s not found in registry!", registryName);
    return 0;
}

Model* VGRGetModelByID(u32 modelID){
        for(int i = 0; i < renderer.registry_s; i++){
            if(renderer.modelPool[i].modelID == modelID){
                return &renderer.modelPool[i].data;
            }
        }
        return NULL;
}

void VGRUnloadModel(char* registryName){
    u32 modelID = VGRGetModelID(registryName);
    if(modelID != 0){
        for(int i = 0; i < renderer.registry_s; i++){
            if(strcmp(renderer.registry[i].modelName,registryName)== 0){
                renderer.registry[i].modelID = 0;
            }
        }

        for(int i = 0; i < renderer.registry_s; i++){
            if(renderer.modelPool[i].modelID == modelID){
                renderer.modelPool[i].modelID = 0;
            }
        }
    }
}

void VGRUnloadModelByID(u32 rendererID){
    //TODO: Unimplemented

}

void VGRCleanupRenderer(){
    //TODO: Unimplemented
}

Drawable VGRCreateDrawable(const char* registryname, Transform transform){
    //TODO: Unimplemented
}

Drawable VGRCreateDrawableByID(u32 rendererID, Transform transform){
    //TODO: Unimplemented
}

Drawable VGRCreateDrawableByCopy(Drawable drawable, Transform transform){
    //TODO: Unimplemented
}

u32 VGRGetDrawableModelID(Drawable drawable){
    //TODO: Unimplemented
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
