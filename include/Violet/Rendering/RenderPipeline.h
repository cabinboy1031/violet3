/**
 * @file RenderPipeline.h
 * @author Ian Hemmer (you@domain.com)
 * @brief The render pipeline functions and wrapper calls for RayLib
 * @version 0.1
 * @date 2022-12-02
 * 
 * 
 */
#include <raylib.h>
#include <flecs.h>

/**
 * @brief the render pipeline setup function.
 * Creates ECSPhases that manage the rendering.
 * Also creates the systems that ensure proper render order
 * The phases are executed in this order:
 *      VERPBeginDraw
 *      VERPOnDraw
 *      VERPPostDraw
 * 
 * Most systems should use VERPOnDraw.
 */
void VERPSetup();

/**
 * @brief Sets up the window and render calls for a given library.
 * Should be the first thing that gets called in any program.
 * 
 * @param width window width
 * @param height window height
 * @param title window title
 */
void VERPSetupRenderer(int width, int height, const char *title);