#include <Violet/Entity.h>
#include <Violet/Rendering/RenderPipeline.h>
#include <flecs.h>
#include <raylib.h>
#include "grid.h"

int main(){
    VERPSetupRenderer(800, 800, "Test window!");

    VECSInit();
    VERPSetup();
    
    SetGrid(80, 40,40);
    
    for(int x = 0; x <= 8; x++){
        for(int y = 0; y <= 8; y++){
            Color color;
            if((x+y)%2 == 0){color = BLACK;} else {color = RED;}
            CreateTile((Transform){{x,y},{},{1,1}},color);
        }
    }
    
    // Run the program
    while(VECSProgress(!WindowShouldClose()));
    // Teardown
    CloseWindow();
    

    VECSDestruct();
}