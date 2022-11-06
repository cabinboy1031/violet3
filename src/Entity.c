#include "flecs.h"
#include <Violet/Entity.h>

ecs_world_t *VECSInit(){
    globalVioletEntitySystem = ecs_init();
    
    // the only required component is the transform
    // the rest of the components should be exposed through its own function in a defined system
    ECS_COMPONENT(globalVioletEntitySystem, Transform);
    
    return globalVioletEntitySystem;
}

void VECSDestruct(){
    ecs_fini(globalVioletEntitySystem);
}