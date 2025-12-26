void mini_map() {
    const int MINI_MAP_SCALE = 6; 
    const int MINI_MAP_CELL_X = CELL_SIZE_X / MINI_MAP_SCALE;
    const int MINI_MAP_CELL_Y = CELL_SIZE_Y / MINI_MAP_SCALE;
    const int MINI_MAP_OFFSET_X = 10;
    const int MINI_MAP_OFFSET_Y = 10;

    for (int y = 0; y < MAP_HEIGHT_CELLS; y++) {
        for (int x = 0; x < MAP_WIDTH_CELLS; x++) {
            int draw_x = MINI_MAP_OFFSET_X + x * MINI_MAP_CELL_X;
            int draw_y = MINI_MAP_OFFSET_Y + y * MINI_MAP_CELL_Y;

            switch (MAP[y][x]) {
                case 0: 
                    break;
                case 1:
                    DrawRectangle(draw_x, draw_y, MINI_MAP_CELL_X, MINI_MAP_CELL_Y, DARKGREEN);
                    break;
            }
        }
    }
    
    DrawCircle(MINI_MAP_OFFSET_X + (player_x / MINI_MAP_SCALE), MINI_MAP_OFFSET_Y + (player_y / MINI_MAP_SCALE), PLAYER_SIZE / MINI_MAP_SCALE, DARKGREEN);
}
