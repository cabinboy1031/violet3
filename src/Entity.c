#include "Violet/Entity.h"
#include "flecs.h"
#include "flecs/addons/flecs_c.h"
#include <raylib.h>

ecs_world_t *globalVioletEntitySystem;

ecs_world_t* VECSInit(){
    globalVioletEntitySystem = ecs_init();
    return globalVioletEntitySystem;
}

ecs_world_t* VECSGetWorld(){
    return globalVioletEntitySystem;
}

void VECSDestruct(){
    ecs_fini(globalVioletEntitySystem);
}

ecs_entity_t VECSCreateEntity(){
    ecs_entity_t e = ecs_new_id(globalVioletEntitySystem); 

    // The only required component in the entire engine.
    // Other components should be added to the entity
    ECS_COMPONENT(globalVioletEntitySystem, Transform);
    ecs_add(globalVioletEntitySystem, e, Transform);
    
    return e;
}