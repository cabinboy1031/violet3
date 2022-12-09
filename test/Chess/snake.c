#include "snake.h"
#include <stdlib.h>
#include <stdio.h>

#include "flecs.h"
#include "Violet/Entity.h"
#include "Violet/Input.h"
#include <raylib.h>
#include "grid.h"

#define COMPONENTS(world)\
    ECS_COMPONENT(world, Transform);\
    ECS_COMPONENT(world, Velocity);\
    ECS_COMPONENT(world, Color);

#define PHASES(world)\
    ECS_ENTITY(world, VECSPreUpdate,EcsPhase);\
    ECS_ENTITY(world, VECSUpdate,   EcsPhase);


void snake_InitializeSystems(){
    ecs_world_t *world = VECSGetWorld();

    COMPONENTS(world);
    PHASES(world);

    // Tag definitions
    ECS_TAG(world, SnakeHead);
    ECS_TAG(world, SnakeTile);
    ECS_TAG(world, SnakeTail);

    // System definitions
    ECS_SYSTEM(world, ChangeSnakeDirection,VECSPreUpdate,Velocity,SnakeHead);
    ecs_system(world, {
        .entity = ecs_entity(world, {
            .name = "MoveSnake",
            .add = {ecs_dependson(VECSUpdate)}
        }),
        .query.filter.expr = "Transform, Velocity, SnakeTile, SnakeHead",
        .callback = MoveSnake,
        .interval = .1
    });

    ecs_system(world, {
        .entity = ecs_entity(world, {
            .name = "SpawnSnakeTail",
            .add = {ecs_dependson(VECSPreUpdate)}
        }),
        .query.filter.expr = "Transform, Velocity, SnakeTile, SnakeHead",
        .callback = SpawnSnakeTail,
        .interval = .1
    });
}

ecs_entity_t snake_CreateSnakeHead(Transform transform){
    ecs_world_t *world = VECSGetWorld();
    COMPONENTS(world);

    // Unique tag marking the head of the snake
    ECS_TAG(world, SnakeHead);
    ECS_COMPONENT(world, SnakeTile);
    ecs_entity_t snake = CreateTile(transform,GREEN);
    ecs_set(world,snake,Velocity, {1,0});
    ecs_add(world,snake,SnakeHead);
    ecs_set(world,snake,SnakeTile,{
            snake,0
        });
    
    return snake;
}

void SpawnSnakeTail(ecs_iter_t *it){
    VECS_FIELD(it, Transform, t, 1);
    VECS_FIELD(it, Velocity, v, 2);
    VECS_FIELD(it, SnakeTile, st, 3);
    ECS_COMPONENT(it->world, Transform);
    ECS_COMPONENT(it->world, Velocity);
    
    if(IsKeyDown('K')){
        //Iterate to the end of the snake
        SnakeTile* cur = st, *temp = 0;
        if(st->next){
            while(cur->next) {
                temp = cur;
                cur = cur->next;
            }
        }
        
        const Transform *cur_t = ecs_get(it->world, cur->id, Transform);
        ecs_entity_t newTile = CreateTile(*cur_t, GREEN);
        if(temp){
            const Velocity *temp_v = ecs_get(it->world, temp->id, Velocity);
            ecs_set(it->world, newTile, Velocity, {temp_v->x, temp_v->y});
        } else {
            ecs_set(it->world, newTile, Velocity, {v->x, v->y});
        }
        cur->next = malloc(sizeof(SnakeTile));
        cur->next->id = newTile;
        cur->next->next = 0;
    }
}

void MoveSnake(ecs_iter_t *it){
    VECS_FIELD(it, Transform, t, 1);
    VECS_FIELD(it, Velocity , v, 2);
    VECS_FIELD(it, SnakeTile, st,3);

    ECS_COMPONENT(it->world, Velocity);
    ECS_COMPONENT(it->world, Transform);
    ECS_TAG(it->world, SnakeHead);


    SnakeTile* cur = st, *temp = 0;
    while(cur != 0) {
        const Transform *cur_t = ecs_get(it->world, cur->id, Transform);
        const Velocity  *cur_v = ecs_get(it->world, cur->id, Velocity);

        if(temp){
            const Velocity  *temp_v = ecs_get(it->world, temp->id, Velocity);
            ecs_set(it->world, cur->id, Velocity, {temp_v->x, temp_v->y});
        }

        ecs_set(it->world, cur->id, Transform, {{
                cur_t->translation.x + cur_v->x, 
                cur_t->translation.y + cur_v->y, 
                cur_t->translation.z
                },
            cur_t->rotation,
            cur_t->scale
        });

        temp = cur;
        cur = cur->next;
    }
}

void ChangeSnakeDirection(ecs_iter_t *it){
    int key = GetCharPressed();    
    VECS_FIELD(it, Velocity, v, 1);

    if(key == 'w'){ *v = (Velocity){ 0,-1};}
    if(key == 'a'){ *v = (Velocity){-1, 0};}
    if(key == 's'){ *v = (Velocity){ 0, 1};}
    if(key == 'd'){ *v = (Velocity){ 1, 0};}
}