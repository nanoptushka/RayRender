# if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <stdio.h>
#include <math.h>
#include <raylib.h>

/* SCREEN SIZE PARAMETERS */
const int screenWidth = 1280;
const int screenHeight = 720;
/* PLAYER PARAMETERS */
int playerX = screenWidth / 2;
int playerY = screenHeight / 2;
double playerZ = 0.0;
const int playerSize = 15;
const int speed = 4;

const double raysNumber = 128;
const int FOV = M_PI / 3;
const double halfFOV = FOV / 2;
const double deltaAngle = FOV / raysNumber;
const int maxDepth = 800;

const int MAP_WIDTH_CELLS = 16;
const int MAP_HEIGHT_CELLS = 12;
const int CELL_SIZE_X = 80;
const int CELL_SIZE_Y = 60;
double wallDistances[1280];
const double PROJECTION_COEFF = screenWidth;

int map[12][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void rayCasting() {
    double currentRayAngle = playerZ - halfFOV;
    
    for (int ray = 0; ray < raysNumber; ray++) {
        double sin_a = sin(currentRayAngle);
        double cos_a = cos(currentRayAngle);
        
        double rayEndX = playerX;
        double rayEndY = playerY;
        double currentDepth = 0.0;
        for (int depth_step = 0; depth_step < maxDepth; depth_step++) {
            double x = playerX + depth_step * cos_a;
            double y = playerY + depth_step * sin_a;
            
            int mapX = (int)(x / CELL_SIZE_X);
            int mapY = (int)(y / CELL_SIZE_Y);
            
            if (mapX >= 0 && mapX < MAP_WIDTH_CELLS &&
                mapY >= 0 && mapY < MAP_HEIGHT_CELLS) {
                
                if (map[mapY][mapX] == 1) {
                    currentDepth = depth_step;
                    rayEndX = x;
                    rayEndY = y;
                    break;
                }
            } else {
                currentDepth = depth_step;
                rayEndX = x; 
                rayEndY = y;
                break;
            }

            if (depth_step == maxDepth - 1) {
                currentDepth = maxDepth;
            }
            rayEndX = x;
            rayEndY = y;
        }

        double correctedDepth = currentDepth * cos(currentRayAngle - playerZ);
        
        wallDistances[ray] = correctedDepth; 

		DrawLine(playerX, playerY, (int)rayEndX, (int)rayEndY, DARKGRAY);
        currentRayAngle += deltaAngle;
    }
}

void drawMap() {
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 16; x++) {
            switch (map[y][x]) {
                case 0:
                    break;
                case 1:
                    DrawRectangleLines(x * 80, y * 60, 80, 60, RED);
                    break;
            }
        }
    }
}

void player() {
	if (IsKeyDown(KEY_W)) {
		if (playerY >= playerSize) {
			playerY = playerY - speed;
		}
	}
		
	if (IsKeyDown(KEY_S)) {
		if (playerY <= screenHeight - playerSize) {
			playerY = playerY + speed;
		}
	}

	if (IsKeyDown(KEY_A)) {
		if (playerX >= playerSize) {
			playerX = playerX - speed;
		}
	}
		
	if (IsKeyDown(KEY_D)) {
		if (playerX <= screenWidth - playerSize) {
			playerX= playerX + speed;
		}
	}

	if (IsKeyDown(KEY_LEFT)) {
		playerZ = playerZ - 0.02;
	}
		
	if (IsKeyDown(KEY_RIGHT)) {
		playerZ = playerZ + 0.02;
	}
	
	DrawCircle(playerX, playerY, playerSize, GREEN);
} 

/*
void drawFPS(int valueFPS) {
    char FPS[100];
    snprintf(FPS, sizeof(FPS), "FPS: %d", valueFPS);
	DrawText(FPS, 10, 10, 32, GREEN);
}
*/

int main() {
    InitWindow(screenWidth, screenHeight, "");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
    	char title[1000];
    	snprintf(title, sizeof(title), "RayRender [fps: %d]", GetFPS());
    	SetWindowTitle(title); 
        BeginDrawing();
            ClearBackground(BLACK);
            rayCasting();
            for (int ray = 0; ray < raysNumber; ray++) {
                if (wallDistances[ray] > 0) {
                    double wallHeight = screenWidth / wallDistances[ray];
                    double screenX = ray * (screenWidth / raysNumber);
                    DrawRectangle(screenX, (screenHeight / 2) - (wallHeight / 2), (screenWidth / raysNumber), wallHeight * 20 , WHITE);
                }
            }
            drawMap();
            player(playerX, playerY, speed);
            /* drawFPS(GetFPS()); */
        EndDrawing();
    }
    CloseWindow();

    return 0;
}