#include "Violet/Rendering/EntityPool.h"

#include <stdio.h>
#include <memory.h>

static EntityPool* init(size_t objectSize){
    EntityPool* entityPool = malloc(sizeof(EntityPool));
    entityPool->size = objectSize;
    entityPool->size = 0;
    entityPool->pool = calloc(0, sizeof(objectSize));

    return entityPool;
}

static void destroy(EntityPool* entityPool){
    if(entityPool == 0){
        return;
    }
    for(int i = 0; i < entityPool->size; i++){
        entityPool->pool[i].data = 0;
        entityPool->pool[i].id = 0;
    }
    free(entityPool);
    entityPool = 0;
}

static void* get(EntityPool* entityPool, u32 id){
    for(int i = 0; i < entityPool->size; i++){
        if(entityPool->pool[i].id == id){
            return entityPool->pool[i].data;
        }
    }
    return 0;
}

static void addObject(EntityPool* entityPool, u32 id, void* object){
    if(get(entityPool,id) != 0){
        printf("ERROR: Attempt to set two objects in the same pool to the same ID.");
        return;
    }

    struct EntityData* newList = calloc(entityPool->size + 1, sizeof(entityPool->size));
    memcpy(newList, entityPool->pool, entityPool->entitySize * entityPool->size);
    memset(entityPool->pool, 0, sizeof(EntityData) * entityPool->size);
    newList[entityPool->size].data = object;
    newList[entityPool->size].id   = id;
}

static void removeObject(EntityPool* entityPool, u32 id){
        for(int i = 0; i < entityPool->size; i++){
            if(entityPool->pool[i].id == id){
                entityPool->pool[i].id = 0;
            }
        }
}

const PoolAPI poolAPI = {
init,
destroy,
addObject,
removeObject,
get
};
