#include "apple.h"
#include <flecs.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "Violet/Entity.h"
#include "grid.h"

void SpawnApple(ecs_iter_t*);

void apple_InitializeSystems(){
    ECS_COMPONENT(VECSGetWorld(), Apple);
    ECS_SYSTEM(VECSGetWorld(), SpawnApple, EcsOnUpdate, Transform, Apple);
    ecs_singleton_set(VECSGetWorld(), Apple, {.apple_limit = 1});

    ecs_entity_t apple = CreateTile((Transform){{
                .x = GetRandomValue(0,10),
                .y = GetRandomValue(0,10)
            },
            {},
            {1,1}
        }, 
        RED);
    ecs_add(VECSGetWorld(), apple, Apple);
}

void SpawnApple(ecs_iter_t* it){
    ECS_COMPONENT(it->world, Transform);
    ECS_COMPONENT(it->world, Apple);
    VECS_FIELD(it, Apple, a, 2);
    
    printf("Number of Apples: %d\n", it->count);
    if(it->count <= a->apple_limit){
        ecs_entity_t apple = CreateTile((Transform){{
                    .x = GetRandomValue(0,10),
                    .y = GetRandomValue(0,10)
                },
                {},
                {1,1}
            }, 
            RED);
        ecs_add(it->world, apple, Apple);

    }
}