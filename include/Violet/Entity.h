#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H
#include <flecs.h>
#include <raylib.h>

// the global entity system
ecs_world_t *globalVioletEntitySystem;

ecs_world_t *VECSInit();
void VECSDestruct();

#endif
