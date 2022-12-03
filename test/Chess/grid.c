#include "grid.h"
#include "Violet/Entity.h"
#include <raylib.h>

void DrawTile(ecs_iter_t* it){
    ECS_COMPONENT(VECSGetWorld(), Grid);
    Transform* transform = ecs_field(it, Transform, 1);
    Color* color = ecs_field(it, Color, 2);
    const Grid* grid = ecs_singleton_get(VECSGetWorld(), Grid);

    for(int i = 0; i <= it->count; i++){
        DrawRectangle(
            transform[i].translation.x * grid->size + grid->offset_x, 
            transform[i].translation.y * grid->size + grid->offset_y, 
            transform[i].scale.x * grid->size,
            transform[i].scale.y * grid->size,
            color[i]);
    }
}


void SetGrid(float size, float offset_x, float offset_y){
    ECS_COMPONENT(VECSGetWorld(), Color);
    ECS_COMPONENT(VECSGetWorld(), Grid);
    ecs_singleton_set(VECSGetWorld(), Grid, {.offset_x = offset_x, .offset_y = offset_y, .size = size});
    
    ECS_ENTITY(VECSGetWorld(), VERPOnDraw, EcsPhase);
    ECS_SYSTEM(VECSGetWorld(), DrawTile, VERPOnDraw, Transform, Color);
}

ecs_entity_t CreateTile(Transform transform, Color color){
    ECS_COMPONENT(VECSGetWorld(), Grid);
    ECS_COMPONENT(VECSGetWorld(), Color);

    ecs_entity_t tile = VECSCreateEntity(transform);
    ecs_add(VECSGetWorld(), tile , Grid);
    ecs_set(VECSGetWorld(), tile, Color, {color.r,color.g,color.b,color.a});
    
    return tile;
}