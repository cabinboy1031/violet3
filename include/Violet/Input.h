#include <stdlib.h>

#define DEFINE_INPUT_COMPONENT_STRUCT(component_name, ...)  \
    typedef struct component_name ## _input_desc_t {  \
        int start;                                              \
        int __VA_ARGS__;                                        \
        int end;                                                \
    } component_name ## _input_desc_t;                          \
                                                                \
    typedef struct component_name ## InputComponent {           \
        component_name ## _input_desc_t *keybinds;              \
        bool start;                                             \
        bool __VA_ARGS__;                                       \
        bool end;                                               \
    } component_name ## InputComponent;                         \
    
#define DEFINE_INPUT_SYSTEM(component_name)                             \
void component_name ## InputUpdate(ecs_iter_t *it){                     \
    VECS_FIELD(it, component_name ## InputComponent,component, 1);      \
    int *keybind = &component->keybinds->start + 1;                     \
    bool *state  = &component->start + 1;                               \
    while(keybind != &component->keybinds->end){                        \
        if(IsKeyPressed(*keybind)){ *state = true;}                     \
        if(IsKeyReleased(*keybind)){ *state = false;}                   \
        keybind++; state++;                                             \
        }\
    }

#define DEFINE_INPUT_COMPONENT_MALLOC(component_name)\
    component_name ## InputComponent* component_name ## InputMalloc(component_name ## _input_desc_t *desc){\
        component_name ## InputComponent* component = malloc(sizeof(component_name ## InputComponent));\
        component->keybinds = desc;\
        return component;\
    }

#define DEFINE_INPUT_COMPONENT(component_name, ...)              \
    DEFINE_INPUT_COMPONENT_STRUCT(component_name, __VA_ARGS__);  \
    DEFINE_INPUT_SYSTEM(component_name);                         \
    DEFINE_INPUT_COMPONENT_MALLOC(component_name);


