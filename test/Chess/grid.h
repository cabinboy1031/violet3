/**
 * @file grid.h
 * @author your name (you@domain.com)
 * @brief Functions for allowing entities to move and display along a grid.
 * @version 0.1
 * @date 2022-12-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "flecs.h"
#include <Violet/Entity.h>
#include <raylib.h>

typedef struct Grid {
    float size;
    float offset_x, offset_y;
} Grid;

/**
 * @brief Create a Grid object
 * 
 * @param size 
 * @param offset 
 * @return ecs_entity_t the grid entity descriptor
 */
void SetGrid(float size, float offset_x, float offset_y);

/**
 * @brief Create a Tile object
 * 
 * @param transform
 * @param color
 *
 * @return ecs_entity_t 
 */
ecs_entity_t CreateTile(Transform t, Color c);