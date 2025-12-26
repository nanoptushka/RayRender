void player() {
  double move_dir_x = cos(player_z);
  double move_dir_y = sin(player_z);

  int new_player_x = player_x;
  int new_player_y = player_y;

  if (IsKeyDown(KEY_W)) {
    new_player_x += move_dir_x * SPEED;
    new_player_y += move_dir_y * SPEED;
  }
  if (IsKeyDown(KEY_S)) {
    new_player_x -= move_dir_x * SPEED;
    new_player_y -= move_dir_y * SPEED;
  }

  if (IsKeyDown(KEY_A)) {
    new_player_x += cos(player_z - M_PI/2) * SPEED;
    new_player_y += sin(player_z - M_PI/2) * SPEED;
  }
  if (IsKeyDown(KEY_D)) {
    new_player_x += cos(player_z + M_PI/2) * SPEED;
    new_player_y += sin(player_z + M_PI/2) * SPEED;
  }
  
  int map_cell_x = (int)(new_player_x / CELL_SIZE_X);
  int map_cell_y = (int)(new_player_y / CELL_SIZE_Y);

  if (map_cell_x >= 0 && map_cell_x < MAP_WIDTH_CELLS &&
      map_cell_y >= 0 && map_cell_y < MAP_HEIGHT_CELLS) {
      if (MAP[map_cell_y][map_cell_x] == 0) {
          player_x = new_player_x;
          player_y = new_player_y;
      }
  }

  if (IsKeyDown(KEY_LEFT)) {
    player_z -= ROTATION_SPEED;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    player_z += ROTATION_SPEED;
  }
} 
