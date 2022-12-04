#include <flecs.h>
#include <raylib.h>

typedef Vector2 Velocity;

typedef struct SnakeTile {
    ecs_entity_t id;
    struct SnakeTile* next;
} SnakeTile;

void snake_InitializeSystems();
void snake_CreateSnakeHead(Transform);

void MoveSnake(ecs_iter_t*);
void ChangeSnakeDirection(ecs_iter_t*);
void SpawnSnakeTail(ecs_iter_t*);