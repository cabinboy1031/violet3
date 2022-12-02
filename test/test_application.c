#include <stdio.h>
#include <flecs.h>
#include <raylib.h>
#include "Violet/Entity.h"
#include "Violet/Rendering/RenderPipeline.h"

typedef struct Velocity{
    float x, y;
} Velocity;

void UpdateSquare(ecs_iter_t *it){
    Transform *t = ecs_field(it, Transform, 1);
    Velocity *v = ecs_field(it, Velocity, 2);
    
    for(int i = 0; i < it->count; i++){
    printf("%s translation: (%f,%f,%f)\n",
    ecs_get_name(it->world, it->system),
        t[i].translation.x,
        t[i].translation.y,
        t[i].translation.z);

        if(t[i].translation.x > 800){
            t[i].translation.x = 100;
        } else {
            t[i].translation.x += v[i].x;
            t[i].translation.y += v[i].y;
        }
    }
    
}

void DrawSquare(ecs_iter_t *it){
    ecs_world_t* world = it->world;

    Transform *t = ecs_field(it, Transform, 1);
    Color *c = ecs_field(it, Color, 2);
    
    printf("number of entities: %d\n",it->count);
    for(int i = 0; i <= it->count; i++){
        printf("%s number of entities: %d\n",ecs_get_name(it->world, it->system),it->count);
        DrawRectangle(
            t[i].translation.x,
            t[i].translation.y, 
            t[i].scale.x, 
            t[i].scale.y,
            *c);
    }
};


int main(){
    VERPSetupRenderer(800, 800, "Test window!");

    VECSInit();
    VERPSetup();
    
    ecs_world_t* world = VECSGetWorld();
    ECS_COMPONENT(world, Transform);
    ECS_COMPONENT(world, Color);
    ECS_COMPONENT(world, Velocity);

    // Test entities
    ecs_entity_t testEntity = VECSCreateEntity(
        (Transform){
            .translation = {100,100,100},
            .rotation = {},
            .scale = {100,100,100}});
    ecs_set(world,testEntity,Color,
                {255,0,0,255});
    ecs_set(world, testEntity,Velocity, {1,0});

    ecs_entity_t testEntity2 = VECSCreateEntity((Transform){
        .translation = {100,200,100},
        .rotation = {},
        .scale = {100,100,100}});
    ecs_set(world,testEntity2,Color,
            {0,255,0,255});
    ecs_set(world, testEntity2,Velocity, {1,1});
    

    ECS_ENTITY(world, VECSUpdate, EcsPhase);
    ecs_entity_t move_sys = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world,{
            .name = "MoveSquares",
            .add = {ecs_dependson(VECSUpdate)}
        }),
        .query.filter.expr = "Transform Velocity",
        .callback = UpdateSquare
    });

    ECS_ENTITY(world, VERPOnDraw, EcsPhase);
    ecs_entity_t draw_sys = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world,{
            .name = "DrawSquares",
            .add = {ecs_dependson(VERPOnDraw)}
        }),
        .query.filter.expr = "Transform Color",
        .callback = DrawSquare
    });

    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}