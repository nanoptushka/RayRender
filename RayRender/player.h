void player() {
  double move_dir_x = cos(player_z);
  double move_dir_y = sin(player_z);

  int newPlayerX = player_x;
  int newPlayerY = player_y;

  if (IsKeyDown(KEY_W)) {
    newPlayerX += move_dir_x * SPEED;
    newPlayerY += move_dir_y * SPEED;
  }
  if (IsKeyDown(KEY_S)) {
    newPlayerX -= move_dir_x * SPEED;
    newPlayerY -= move_dir_y * SPEED;
  }

  if (IsKeyDown(KEY_A)) {
    newPlayerX += cos(player_z - M_PI/2) * SPEED;
    newPlayerY += sin(player_z - M_PI/2) * SPEED;
  }
  if (IsKeyDown(KEY_D)) {
    newPlayerX += cos(player_z + M_PI/2) * SPEED;
    newPlayerY += sin(player_z + M_PI/2) * SPEED;
  }
  
  int mapCellX = (int)(newPlayerX / CELL_SIZE_X);
  int mapCellY = (int)(newPlayerY / CELL_SIZE_Y);

  if (mapCellX >= 0 && mapCellX < MAP_WIDTH_CELLS &&
      mapCellY >= 0 && mapCellY < MAP_HEIGHT_CELLS) {
      if (MAP[mapCellY][mapCellX] == 0) {
          player_x = newPlayerX;
          player_y = newPlayerY;
      }
  }

  if (IsKeyDown(KEY_LEFT)) {
    player_z -= ROTATION_SPEED;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    player_z += ROTATION_SPEED;
  }
} 
