/**
 * Author: mysticalCabinboy
 **/
#include "Violet/Rendering.h"
#include "raylib.h"

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
    u32* modelIDs;
    Transform* transforms;

    struct RegistryEntry* registry;
    u32 registryLength;
    struct ModelPoolData* modelPool;
    u32 modelPoolLength;
} Renderer;

void VGRSetupRenderer(){
    //TODO: Unimplemented
}

u32 VGRRegisterModel(const char* registryName, Model model){
    //TODO: Unimplemented
}

u32 VGRRegisterModelWithID(const char* registryName, u32 registryID, Model model){
    //TODO: Unimplemented
}

u32 VGRGetModelID(char* registryName){
    //TODO: Unimplemented

}

void VGRUnloadModel(const char* registryName){
    //TODO: Unimplemented

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
