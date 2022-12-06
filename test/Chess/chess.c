#include <Violet/Entity.h>
#include <Violet/Rendering/RenderPipeline.h>
#include <flecs.h>
#include <raylib.h>
#include "grid.h"
#include "snake.h"
#include "apple.h"


int main(){
    VERPSetupRenderer(800, 800, "Test window!");
    ecs_world_t *world = VECSInit();

    VERPSetup();
    
    /* Tiles use this grid as a singleton */
    SetGrid(20, 40,40);
    
    snake_InitializeSystems();
    snake_CreateSnakeHead((Transform){
            {10,10,0},
            {},
            {1,1}
        });
    
    apple_InitializeSystems();

    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}
