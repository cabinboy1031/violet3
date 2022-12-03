#include <Violet/Entity.h>
#include <Violet/Rendering/RenderPipeline.h>
#include <flecs.h>
#include <raylib.h>
#include "grid.h"

typedef Vector2 Velocity;

void MoveSnake(ecs_iter_t *it){
    Transform *t = ecs_field(it, Transform,1);
    Velocity *v = ecs_field(it, Velocity, 2);

    Velocity temp, carry = v[0];
    for(int i = 0; i < it->count; i++){
        t[i].translation.x += v[i].x;
        t[i].translation.y += v[i].y;
        temp = v[i];
        v[i] = carry;
        carry = temp;
    }
}

void ChangeSnakeDirection(ecs_iter_t *it){
    int key = GetCharPressed();    
    Velocity *v = ecs_field(it, Velocity, 1);

    if(key == 'w'){ *v = (Velocity){ 0,-1};}
    if(key == 'a'){ *v = (Velocity){-1, 0};}
    if(key == 's'){ *v = (Velocity){ 0, 1};}
    if(key == 'd'){ *v = (Velocity){ 1, 0};}
}

int main(){
    VERPSetupRenderer(800, 800, "Test window!");

    VECSInit();
    VERPSetup();
    
    SetGrid(20, 40,40);

    ecs_world_t *world = VECSGetWorld();

    ECS_COMPONENT(world, Transform);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Color);

    ECS_TAG(world, SnakeHead);
    ecs_entity_t snake = CreateTile((Transform){{10,10,0},{},{1,1}},RED);
    // Add a snake tag to this rectangle
    ecs_set(world,snake,Velocity, {1,0});
    ecs_add(world,snake,SnakeHead);

    ECS_ENTITY(world, VECSPreUpdate,EcsPhase);
    ECS_ENTITY(world, VECSUpdate,EcsPhase);
    ECS_SYSTEM(world, ChangeSnakeDirection,VECSPreUpdate,Velocity,SnakeHead);
    ecs_system(world, {
        .entity = ecs_entity(world, {
            .name = "MoveSnake",
            .add = {ecs_dependson(VECSUpdate)}
        }),
        .query.filter.expr = "[cascade] Transform , [cascade] Velocity ",
        .callback = MoveSnake,
        .interval = .25
    });

    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}
