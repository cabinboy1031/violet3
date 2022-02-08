#include "Violet/Rendering/ObjectPool.h"

#include <stdio.h>
#include <memory.h>

static ObjectPool* init(size_t objectSize){
    ObjectPool* objectPool = malloc(sizeof(ObjectPool));
    objectPool->objectSize = objectSize;
    objectPool->size = 0;
    objectPool->pool = calloc(0, sizeof(objectSize));

    return objectPool;
}

static void destroy(ObjectPool* objectPool){
    if(objectPool == 0){
        return;
    }
    for(int i = 0; i < objectPool->size; i++){
        objectPool->pool[i].data = 0;
        objectPool->pool[i].id = 0;
    }
    free(objectPool);
    objectPool = 0;
}

static void addObject(ObjectPool* objectPool, u32 id, void* object){
    if(poolAPI.get(objectPool,id) != 0){
        printf("ERROR: Attempt to set two objects in the same pool to the same ID.");
        return;
    }

    struct ObjectData* newList = calloc(objectPool->size + 1, sizeof(objectPool->objectSize));
    memcpy(newList, objectPool->pool, sizeof(objectPool->objectSize) * objectPool->size);
    memset(objectPool->pool, 0, sizeof(objectPool->objectSize) * objectPool->size);
    newList[objectPool->size].data = object;
    newList[objectPool->size].id   = id;
}

static void removeObject(ObjectPool* objectPool, u32 id){
        for(int i = 0; i < objectPool->size; i++){
            if(objectPool->pool[i].id == id){
                objectPool->pool[i].id = 0;
            }
        }
}

static void* get(ObjectPool* objectPool, u32 id){
    for(int i = 0; i < objectPool->size; i++){
        if(objectPool->pool[i].id == id){
            return objectPool->pool[i].data;
        }
    }
    return 0;
}

const PoolAPI poolAPI = {
init,
destroy,
addObject,
removeObject,
get
};
