#include <Violet/Entity.h>
#include <Violet/Rendering/RenderPipeline.h>
#include <flecs.h>
#include <raylib.h>
#include "grid.h"

typedef struct Velocity{
    int x,y;
}Velocity;

void MoveSnake(ecs_iter_t it){
}

int main(){
    VERPSetupRenderer(800, 800, "Test window!");

    VECSInit();
    VERPSetup();
    
    SetGrid(20, 40,40);

    ECS_COMPONENT(VECSGetWorld(), Color);
    ecs_entity_t snake = CreateTile((Transform){{10,10,0},{},{1,1}},RED);
    // Add a snake tag to this rectangle
    ECS_COMPONENT(VECSGetWorld(),Velocity);
    ecs_add(VECSGetWorld(),snake,Velocity);

    
    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}
