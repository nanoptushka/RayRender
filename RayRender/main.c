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
            
            for (int ray = 0; ray < RAYS_NUMBER; ray++) {
            	const double PROJECTION_PLANE_DIST = (1280  / 2) / tan(HALF_FOV);
                double wall_height = (WALL_HEIGHT_SCALER * PROJECTION_PLANE_DIST / wall_distances[ray]);
                
                if (wall_height > SCREEN_HEIGHT) wall_height = SCREEN_HEIGHT;
                if (wall_height < 0) wall_height = 0;

                double screen_x = ray * (SCREEN_WIDTH / RAYS_NUMBER);
                double column_width = (SCREEN_WIDTH / RAYS_NUMBER);
                
                DrawRectangle(screen_x, (SCREEN_HEIGHT / 2) - (wall_height / 2), column_width + 1, wall_height, GREEN);
            }
            
            mini_map();
            
        EndDrawing(); 
    }
    CloseWindow();

    return 0;
}
