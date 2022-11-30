#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H
#include <flecs.h>
#include <raylib.h>

/**
 * @brief Initialize the component system
 * This should ALWAYS be done first.
 * 
 * @return ecs_world_t* the ECS world, there MUST NOT be one already initialized.
 */
ecs_world_t* VECSInit();

/**
 * @brief Get the ECS world.
 * @return ecs_world_t* 
 */
ecs_world_t* VECSGetWorld();

/**
 * @brief The ECS cleanup function.
 */
void VECSDestruct();

/**
 * @brief Creates a default entity with a Transform component
 * 
 * @return ecs_entity_t 
 */
ecs_entity_t VECSCreateEntity();

#endif
