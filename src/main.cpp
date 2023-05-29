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
#include "rlgl.h"
#include "raymath.h"

#include "trace.hpp"

void DrawGrid( const Camera2D &camera, const int screenWidth, const int screenHeight ) {
    int left_most_view = camera.target.x - ( screenWidth / camera.zoom );
    int right_most_view = camera.target.x + ( screenWidth / camera.zoom );

    int top_most_view = camera.target.y - ( screenHeight / camera.zoom );
    int bottom_most_view = camera.target.y + ( screenHeight / camera.zoom );

    for ( int i = left_most_view; i <= right_most_view; i += 10 ) {
        i /= 10;
        i *= 10;
        DrawLine( i, bottom_most_view, i, top_most_view, DARKGRAY );
    }

    for ( int i = top_most_view; i <= bottom_most_view; i += 10 ) {
        i /= 10;
        i *= 10;
        DrawLine( left_most_view, i, right_most_view, i, DARKGRAY );
    }

    DrawLineV( Vector2{ static_cast< float >( left_most_view ), 0 }, Vector2{ static_cast< float >( right_most_view ), 0 }, WHITE );
    DrawLineV( Vector2{ 0, static_cast< float >( bottom_most_view ) }, Vector2{ 0, static_cast< float >( top_most_view ) }, WHITE );
}

int main( int, char ** ) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow( screenWidth, screenHeight, "math_tool" );

    Trace::Instance().Message( "I am here.", FILENAME, LINENUMBER );

    Camera2D camera = { 0 };
    camera.target = Vector2{ -screenWidth / 2, -screenHeight / 2 };
    camera.zoom = 1.f;

    SetTargetFPS( 60 ); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while ( !WindowShouldClose() ) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if ( IsMouseButtonDown( MOUSE_BUTTON_RIGHT ) ) {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale( delta, -1.0f / camera.zoom );

            camera.target = Vector2Add( camera.target, delta );
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if ( wheel != 0 ) {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D( GetMousePosition(), camera );

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += ( wheel * zoomIncrement );
            if ( camera.zoom < zoomIncrement ) camera.zoom = zoomIncrement;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground( BLACK );

        BeginMode2D( camera );

        DrawGrid( camera, screenWidth, screenHeight );

        EndMode2D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
