#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H
#include <flecs.h>
#include <raylib.h>

ecs_world_t* VECSInit();
ecs_world_t* VECSGetWorld();
void VECSDestruct();

#endif
