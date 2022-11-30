#include "Violet/Entity.h"
#include "flecs.h"
#include "flecs/addons/flecs_c.h"
#include <raylib.h>
#include <stdio.h>

ecs_world_t *globalVioletEntitySystem;

ecs_world_t* VECSInit(){
    globalVioletEntitySystem = ecs_init();
    ecs_world_t *world = globalVioletEntitySystem;

    // Custom pipeline setup.
    // a new stage needs to use the ECS_PIPELINE() macro to get the pipeline
    // Then the user can add whatever stage they wish through their setup function.
    
    
    ecs_entity_t VECSUpdate = ecs_new_w_id(world,EcsPhase);

    ECS_TAG(world, VECSEntityTick);
    ECS_ENTITY(world, TickEntity, VECSEntityTick);
    
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