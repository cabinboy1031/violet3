#ifndef VIOLET_OBJECT_POOL_H
#define VIOLET_OBJECT_POOL_H
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;

typedef struct EntityData {
    u32   id;
    void* data;
} EntityData;

typedef struct EntityPool{
    struct EntityData *pool;
    size_t  size;
    size_t entitySize;
} EntityPool;

typedef struct {
    EntityPool* (*init)    (size_t);
    void        (*destroy) (EntityPool *);
    void        (*addObject)     (EntityPool*, u32, void*);
    void        (*removeObject)  (EntityPool*, u32);
    void*       (*get)     (EntityPool*, u32);
} PoolAPI;

extern const PoolAPI poolAPI;

#endif // VIOLET_OBJECT_POOL_H
