#include "Violet/Rendering/RenderPipeline.h"
#include "Violet/Entity.h"
#include "flecs.h"
#include "flecs/addons/flecs_c.h"
#include <stdio.h>

void VERPBeginDrawing(ecs_iter_t* it){
    BeginDrawing();
    ClearBackground(RAYWHITE);
}

void VERPEndDrawing(ecs_iter_t* it){
    EndDrawing(); 
}

void UpdateSquare(ecs_iter_t *it){

    printf("%s number of entities: %d\n",ecs_get_name(it->world, it->system),it->count);
    Transform *t = ecs_field(it, Transform, 1);
    
    for(int i = 0; i < it->count; i++){
    printf("%s translation: (%f,%f,%f)\n",
    ecs_get_name(it->world, it->system),
        t[i].translation.x,
        t[i].translation.y,
        t[i].translation.z);

        if(t[i].translation.x > 800){
            t[i].translation.x = 100;
        } else {
            t[i].translation.x += 1;
        }
    }
    
}

void DrawSquare(ecs_iter_t *it){
    ecs_world_t* world = it->world;

    Transform *t = ecs_field(it, Transform, 1);
    Color *c = ecs_field(it, Color, 2);
    
    printf("number of entities: %d\n",it->count);
    for(int i = 0; i <= it->count; i++){
        DrawRectangle(
            t[i].translation.x,
            t[i].translation.y, 
            t[i].scale.x, 
            t[i].scale.y,
            *c);
    }
};

void VERPSetup(){
    ecs_world_t* world = VECSGetWorld();
    ECS_COMPONENT(world, Transform);
    ECS_COMPONENT(world, Color);

    
    /*
    * Render pipeline definition and ordering
    * - Rendering: The phase hook itself, allowing the pipeline to be ordered before or after the setup functions as needed.
    *   - BeginDraw: Anything that needs to happen at the start of the frame. Sorting, effects, etc.
    *   - OnDraw: Everything else.
    *   - PostDraw: Ending the current frame for the renderer and post processing.
    */ 

    ecs_entity_t VERPBeginDraw = ecs_new_w_id(world, EcsPhase);
    ecs_entity_t VERPOnDraw = ecs_new_w_id(world, EcsPhase);
    ecs_entity_t VERPPostDraw = ecs_new_w_id(world, EcsPhase);


    ECS_ENTITY(world, VECSUpdate, EcsPhase);
    ecs_add_pair(world, VERPBeginDraw, EcsDependsOn, VECSUpdate);
    ecs_add_pair(world, VERPOnDraw, EcsDependsOn, VERPBeginDraw);
    ecs_add_pair(world, VERPPostDraw, EcsDependsOn, VERPOnDraw);
    
    ECS_TAG(world, Renderer);
    ECS_ENTITY(world, RenderEntity, Renderer);
    
    // Test entity
    ECS_ENTITY(world, TestEntity);
    ecs_entity_t testEntity = VECSCreateEntity();
    ecs_set(world,testEntity, Transform, {
        .translation = {100,100,100},
        .scale = {100,100,100}
        });
    ecs_set(world,testEntity,Color,{RED.r,RED.g, RED.b,RED.a});

    ecs_entity_t testEntity2 = VECSCreateEntity();
    ecs_set(world,testEntity2, Transform, {
        .translation = {100,200,100},
        .scale = {100,100,100}
        });
    ecs_set(world,testEntity2,Color,{RED.r,RED.g, RED.b,RED.a});
    
    ecs_entity_t move_sys = ecs_system_init(world, &(ecs_system_desc_t){
        .entity = ecs_entity(world,{
            .name = "MoveSquares",
            .add = {ecs_dependson(VECSUpdate)}
        }),
        .query.filter.expr = "Transform",
        .callback = UpdateSquare
    });
    
    ECS_SYSTEM(world, VERPBeginDrawing, VERPBeginDraw, Renderer);
    ECS_SYSTEM(world, DrawSquare,       VERPOnDraw,Transform,Color);
    ECS_SYSTEM(world, VERPEndDrawing,   VERPPostDraw, Renderer);
}

void VERPSetupRenderer(int width, int height, const char *title){
    InitWindow(width,height,title);
    SetTargetFPS(60);
}