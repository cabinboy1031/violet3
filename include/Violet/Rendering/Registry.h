#ifndef VIOLET_REGISTRY_H
#define VIOLET_REGISTRY_H
#include <stdlib.h>
#include <stdint.h>

typedef uint32_t u32;


typedef struct Registry{
    struct RegistryEntry {
        char* name;
        u32   id;
    }      *data;
    size_t size;

} Registry;

typedef struct {
    struct Registry* (*init)(void);
    void             (*delete)     (Registry*);
    void             (*addEntry)   (Registry*, char* name, u32 id);
    void             (*deleteEntry)(Registry*,char* name);
    u32              (*getEntry)   (Registry*,char* name);
} RegistryAPI;

extern const RegistryAPI registryAPI;

#endif // VIOLET_REGISTRY_H
