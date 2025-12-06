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

const double raysNumber = 120;
const int FOV = M_PI / 3;
const double halfFOV = FOV / 2;
const double deltaAngle = FOV / raysNumber;
const int maxDepth = 800;

void rayCasting() {
    double curAngle = playerZ - halfFOV;
    double xo = playerX;
    double yo = playerY;

    for (int ray = 0; ray < raysNumber; ray++) {
        double sin_a = sin(curAngle);
        double cos_a = cos(curAngle);
        
        for (int depth = 0; depth < maxDepth; depth++) {
            double x = xo + depth * cos_a;
            double y = yo + depth * sin_a;
            DrawLine(playerX, playerY, x, y, DARKGRAY);
        }
        curAngle += deltaAngle;
    }
}

void map() {
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

    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 16; x++) {
            switch (map[y][x]) {
                case 0:
                    DrawRectangle(x * 80, y * 60, 80, 60, BLACK);
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
	
	/* RAYX = PLAYERX + WIDTH * COS(PLAYER_ANGLE) */
	/* RAYY = PLAYERY + WIDTH * SIN(PLAYER_ANGLE) */
	// DrawLine(playerX, playerY, playerX + screenWidth * cos(playerZ), playerY + screenWidth * sin(playerZ), RED);
} 

void drawFPS(int valueFPS) {
    char FPS[100];
    snprintf(FPS, sizeof(FPS), "FPS: %d", valueFPS);
	DrawText(FPS, 10, 10, 32, GREEN);
}

int main() {
    InitWindow(screenWidth, screenHeight, "RayRender - Ray-casting algorithm written in C");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            map();
            player(playerX, playerY, speed);
            rayCasting();
            drawFPS(GetFPS());
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
