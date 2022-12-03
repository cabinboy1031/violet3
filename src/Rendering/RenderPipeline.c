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


    ECS_ENTITY(world, VECSPostUpdate, EcsPhase);
    ecs_add_pair(world, VERPBeginDraw, EcsDependsOn, VECSPostUpdate);
    ecs_add_pair(world, VERPOnDraw, EcsDependsOn, VERPBeginDraw);
    ecs_add_pair(world, VERPPostDraw, EcsDependsOn, VERPOnDraw);
    
    ECS_TAG(world, Renderer);
    ECS_ENTITY(world, RenderEntity, Renderer);

    // Default BeginDraw and PostDraw functions for the render pipeline
    ECS_SYSTEM(world, VERPBeginDrawing, VERPBeginDraw, Renderer);
    ECS_SYSTEM(world, VERPEndDrawing,   VERPPostDraw, Renderer);
}

void VERPSetupRenderer(int width, int height, const char *title){
    InitWindow(width,height,title);
    SetTargetFPS(60);
}