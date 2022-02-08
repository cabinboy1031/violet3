#ifndef VIOLET_OBJECT_POOL_H
#define VIOLET_OBJECT_POOL_H
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;

typedef struct ObjectPool{
    struct ObjectData {
        u32   id;
        void* data;
    }      *pool;
    size_t  size;
    size_t objectSize;
} ObjectPool;

typedef struct {
    ObjectPool* (*init)    (size_t);
    void        (*destroy) (ObjectPool*);
    void        (*addObject)     (ObjectPool*, u32, void*);
    void        (*removeObject)  (ObjectPool*, u32);
    void*       (*get)     (ObjectPool*, u32);
} PoolAPI;

extern const PoolAPI poolAPI;

#endif // VIOLET_OBJECT_POOL_H
