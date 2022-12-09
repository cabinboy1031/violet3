#include <Violet/Entity.h>
#include <Violet/Rendering/RenderPipeline.h>
#include <Violet/Input.h>
#include <flecs.h>
#include <raylib.h>
#include "grid.h"
#include "snake.h"
#include "apple.h"

DEFINE_INPUT_COMPONENT(Snake, up, down, left, right, spawn_tail)

int main(){
    VERPSetupRenderer(800, 800, "Test window!");
    ecs_world_t *world = VECSInit();
    VERPSetup();
    
    /* Tiles use this grid as a singleton */
    SetGrid(20, 40,40);

    ECS_COMPONENT(world, SnakeInputComponent);
    Snake_input_desc_t *desc = &(Snake_input_desc_t){
        .up     = KEY_W,
        .down   = KEY_S,
        .left   = KEY_A,
        .right  = KEY_D,
        .spawn_tail = KEY_K
    };
    SnakeInputComponent *comp = SnakeInputMalloc(desc);
    ecs_singleton_add(world, SnakeInputComponent);
    ecs_singleton_set(world, SnakeInputComponent, &comp);

    ECS_ENTITY(world, VECSPreUpdate, EcsPhase);
    ECS_SYSTEM(world, SnakeInputUpdate, VECSPreUpdate, SnakeInputComponent);
    
    snake_InitializeSystems();
    ecs_entity_t snake_head = snake_CreateSnakeHead((Transform){
            {10,10,0},
            {},
            {1,1}
        });
    ecs_add(world, snake_head, SnakeInputComponent);
    
    apple_InitializeSystems();

    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}
