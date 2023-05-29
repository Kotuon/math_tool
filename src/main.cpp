/**
 * @file main.cpp
 * @author Kelson Wysocki (kelson.wysocki@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-05-29
 *
 *
 *
 */

#include "raylib.h"
#include "trace.hpp"

int main( int, char ** ) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow( screenWidth, screenHeight, "math_tool" );

    Trace::Instance().Message( "I am here.", FILENAME, LINENUMBER );

    SetTargetFPS( 60 ); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while ( !WindowShouldClose() ) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground( DARKGRAY );

        DrawFPS( 10, 10 );

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
