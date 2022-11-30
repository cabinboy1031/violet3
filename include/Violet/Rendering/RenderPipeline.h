#include <raylib.h>
#include <flecs.h>

/**
 * @brief the render pipeline setup function.
 * This initializes all the components that one may require for rendering.
 */
void VERPSetup();


void VERPSetupRenderer(int width, int height, const char *title);

void VERPFrame(bool runCondition);