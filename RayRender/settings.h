const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int FPS = 60;

const int MAP_WIDTH_CELLS = 16;
const int MAP_HEIGHT_CELLS = 12;
const int CELL_SIZE_X = 80;
const int CELL_SIZE_Y = 60;
const int MAX_DEPTH = 800;
const double ROTATION_SPEED = 0.05;
const int PLAYER_SIZE = 30;
const int SPEED = 4;

const double RAYS_NUMBER = 120;
const double FOV = M_PI / 3;
const double HALF_FOV = FOV / 2;
const double DELTA_ANGLE = FOV / RAYS_NUMBER;

const double WALL_HEIGHT_SCALER = CELL_SIZE_Y;

const int MAP[12][16] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

int player_x = CELL_SIZE_X * 1 + CELL_SIZE_X / 2;
int player_y = CELL_SIZE_Y * 1 + CELL_SIZE_Y / 2;
double player_z = M_PI / 2;

double wall_distances[1280];