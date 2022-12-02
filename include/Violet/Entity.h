#ifndef ENTITY_SYSTEM_H
#define ENTITY_SYSTEM_H
#include <flecs.h>
#include <raylib.h>

/**
 * @brief Initialize the component system
 * This should ALWAYS be done first.
 * 
 * This also exposes the pipeline phase VECSUpdate. All other custom phases should branch off here
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
 * @brief Creates a default entity with a Transform componentlled in main
 * 
 * @return ecs_entity_t 
 */
ecs_entity_t VECSCreateEntity();


/**
 * @brief Progresses the engine world, called once and runs everything. run every frame
 * 

 * @param runCondition additional conditions of when the engine should run or stop.
 * @return whether the engine should keep running.
 */
bool VECSProgress(bool runCondition);

#endif
