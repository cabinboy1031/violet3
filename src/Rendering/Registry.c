#include "Violet/Rendering/Registry.h"
#include <stdio.h>
#include <memory.h>

static Registry* init(){
    Registry* registry = malloc(sizeof(Registry));
    registry->data = calloc(0, sizeof(struct RegistryEntry));
    registry->size = 0;

    return registry;
}

static void delete(Registry* registry){
    free(registry);
    registry = 0;
}

static void addEntry(Registry* registry, char* name, u32 id){
    if(registryAPI.getEntry(registry, name) != 0){
        printf("ERROR: model name is already registered: %s!", name);
        return;
    }
    struct RegistryEntry* newList = calloc(registry->size + 1, sizeof(struct RegistryEntry));

    memcpy(newList, registry->data, sizeof(struct RegistryEntry) * registry->size);
    memset(registry->data, 0, sizeof(struct RegistryEntry) * registry->size);
    newList[registry->size].name = name;
    newList[registry->size].id   = id;
    registry->size++;

    free(registry->data);
    registry->data = newList;
}

static void deleteEntry(Registry* registry,char* name){
        for(int i = 0; i < registry->size; i++){
            if(strcmp(registry->data[i].name,name)== 0){
                registry->data[i].id = 0;
            }
        }
}

static u32 getEntry(Registry* registry,char* name){
    if(registry == 0){
        return 0;
    }
    for(int i = 0; i < registry->size; i++){
        if(strcmp(registry->data[i].name,name) == 0){
            return registry->data[i].id;
        }
    }
    return 0;
}

const RegistryAPI registryAPI = {
    init,
    delete,
    addEntry,
    deleteEntry,
    getEntry
};
