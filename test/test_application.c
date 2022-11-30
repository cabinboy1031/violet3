#include <flecs.h>
#include <raylib.h>
#include "Violet/Entity.h"
#include "Violet/Rendering/RenderPipeline.h"

int main(){
    VERPSetupRenderer(800, 800, "Test window!");

    VECSInit();
    VERPSetup();
    
    

    while(ecs_progress(VECSGetWorld(), 0) && !WindowShouldClose()){};
    CloseWindow();
    

    VECSDestruct();
}