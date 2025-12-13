
#include <stdio.h>
#include <math.h>
#include <raylib.h>

/* SCREEN SIZE PARAMETERS */
const int screenWidth = 1280;
const int screenHeight = 720;

/* MAP PARAMETERS */
const int MAP_WIDTH_CELLS = 16;
const int MAP_HEIGHT_CELLS = 12;
const int CELL_SIZE_X = 80;
const int CELL_SIZE_Y = 60;
const int maxDepth = 800;

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

int playerX = CELL_SIZE_X * 1 + CELL_SIZE_X / 2;
int playerY = CELL_SIZE_Y * 1 + CELL_SIZE_Y / 2;
double playerZ = M_PI / 2;
const int playerSize = 15;
const int speed = 4;
const double rotationSpeed = 0.05;

const double raysNumber = 120;
const double FOV = M_PI / 3;
const double halfFOV = FOV / 2;
const double deltaAngle = FOV / raysNumber;

const double WALL_HEIGHT_SCALER = CELL_SIZE_Y;
double wallDistances[120];

void rayCasting() {
    double currentRayAngle = playerZ - halfFOV;
    
    for (int ray = 0; ray < raysNumber; ray++) {
        double sin_a = sin(currentRayAngle);
        double cos_a = cos(currentRayAngle);
        
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
                    break;
                }
            } else {
                currentDepth = depth_step;
                break;
            }
            if (depth_step == maxDepth - 1) {
                currentDepth = maxDepth;
            }
        }
        
        double correctedDepth = currentDepth * cos(currentRayAngle - playerZ);
        wallDistances[ray] = fmax(0.1, correctedDepth);

        currentRayAngle += deltaAngle;
    }
}

void drawMap() {
    const int MINI_MAP_SCALE = 4; 
    const int MINI_MAP_CELL_X = CELL_SIZE_X / MINI_MAP_SCALE;
    const int MINI_MAP_CELL_Y = CELL_SIZE_Y / MINI_MAP_SCALE;
    const int MINI_MAP_OFFSET_X = 10;
    const int MINI_MAP_OFFSET_Y = screenHeight - (MAP_HEIGHT_CELLS * MINI_MAP_CELL_Y) - 10;

    for (int y = 0; y < MAP_HEIGHT_CELLS; y++) {
        for (int x = 0; x < MAP_WIDTH_CELLS; x++) {
            int drawX = MINI_MAP_OFFSET_X + x * MINI_MAP_CELL_X;
            int drawY = MINI_MAP_OFFSET_Y + y * MINI_MAP_CELL_Y;

            switch (map[y][x]) {
                case 0:
                    DrawRectangle(drawX, drawY, MINI_MAP_CELL_X, MINI_MAP_CELL_Y, BLACK);
                    break;
                case 1:
                    DrawRectangle(drawX, drawY, MINI_MAP_CELL_X, MINI_MAP_CELL_Y, GREEN);
                    break;
            }
            DrawRectangleLines(drawX, drawY, MINI_MAP_CELL_X, MINI_MAP_CELL_Y, GRAY);
        }
    }
}

void player() {
  double move_dir_x = cos(playerZ);
  double move_dir_y = sin(playerZ);

  int newPlayerX = playerX;
  int newPlayerY = playerY;

  if (IsKeyDown(KEY_W)) {
    newPlayerX += move_dir_x * speed;
    newPlayerY += move_dir_y * speed;
  }
  if (IsKeyDown(KEY_S)) {
    newPlayerX -= move_dir_x * speed;
    newPlayerY -= move_dir_y * speed;
  }

  if (IsKeyDown(KEY_A)) {
    newPlayerX += cos(playerZ - M_PI/2) * speed;
    newPlayerY += sin(playerZ - M_PI/2) * speed;
  }
  if (IsKeyDown(KEY_D)) {
    newPlayerX += cos(playerZ + M_PI/2) * speed;
    newPlayerY += sin(playerZ + M_PI/2) * speed;
  }
  
  int mapCellX = (int)(newPlayerX / CELL_SIZE_X);
  int mapCellY = (int)(newPlayerY / CELL_SIZE_Y);

  if (mapCellX >= 0 && mapCellX < MAP_WIDTH_CELLS &&
      mapCellY >= 0 && mapCellY < MAP_HEIGHT_CELLS) {
      if (map[mapCellY][mapCellX] == 0) {
          playerX = newPlayerX;
          playerY = newPlayerY;
      }
  }

  if (IsKeyDown(KEY_LEFT)) {
    playerZ -= rotationSpeed;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    playerZ += rotationSpeed;
  }
  
  const int MINI_MAP_SCALE = 4;
  const int MINI_MAP_OFFSET_X = 10;
  const int MINI_MAP_OFFSET_Y = screenHeight - (MAP_HEIGHT_CELLS * (CELL_SIZE_Y / MINI_MAP_SCALE)) - 10;

  DrawCircle(MINI_MAP_OFFSET_X + (playerX / MINI_MAP_SCALE), MINI_MAP_OFFSET_Y + (playerY / MINI_MAP_SCALE), playerSize / MINI_MAP_SCALE, GREEN);
  
  DrawLine(MINI_MAP_OFFSET_X + (playerX / MINI_MAP_SCALE), MINI_MAP_OFFSET_Y + (playerY / MINI_MAP_SCALE),
           MINI_MAP_OFFSET_X + (playerX / MINI_MAP_SCALE) + (int)(playerSize * 2 * move_dir_x / MINI_MAP_SCALE),
           MINI_MAP_OFFSET_Y + (playerY / MINI_MAP_SCALE) + (int)(playerSize * 2 * move_dir_y / MINI_MAP_SCALE), BLUE);
} 

void drawFPS(int valueFPS) {
    char FPS[100];
    snprintf(FPS, sizeof(FPS), "FPS: %d", valueFPS);
    DrawText(FPS, 10, 10, 20, WHITE);
}

int main() {
    InitWindow(screenWidth, screenHeight, "RayRender - A simple ray casting algorithm-based render written in C by nanoptushka");

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        char title[100];
        snprintf(title, sizeof(title), "RayRender [fps: %d]", GetFPS());
        SetWindowTitle(title); 
        
        BeginDrawing();
            ClearBackground(DARKGREEN);
            DrawRectangle(0, 0, screenWidth, screenHeight / 2, LIME);
            player();
            rayCasting();
            for (int ray = 0; ray < raysNumber; ray++) {
            	const double PROJECTION_PLANE_DIST = (1280  / 2) / tan(halfFOV);
                double wallHeight = (WALL_HEIGHT_SCALER * PROJECTION_PLANE_DIST / wallDistances[ray]);
                
                if (wallHeight > screenHeight) wallHeight = screenHeight;
                if (wallHeight < 0) wallHeight = 0;

                double screenX = ray * (screenWidth / raysNumber);
                double columnWidth = (screenWidth / raysNumber);
                
                DrawRectangle(screenX, (screenHeight / 2) - (wallHeight / 2), columnWidth + 1, wallHeight, GREEN);
            }
            drawMap();
            drawFPS(GetFPS());
            
        EndDrawing(); 
    }
    CloseWindow();

    return 0;
}