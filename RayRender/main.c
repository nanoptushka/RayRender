#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <stdio.h>
#include <math.h>
#include <raylib.h>

#include "settings.h"

#include "player.h"
#include "ray_casting.h"
#include "mini_map.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RayRender");

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        char title[100];
        snprintf(title, sizeof(title), "RayRender [fps: %d]", GetFPS());
        SetWindowTitle(title); 
        
        BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, LIME);
            
            player();
            ray_casting();  
            mini_map();
            
        EndDrawing(); 
    }
    CloseWindow();

    return 0;
}
