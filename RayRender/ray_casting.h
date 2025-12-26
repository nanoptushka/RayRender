void ray_casting() {
    double current_ray_angle = player_z - HALF_FOV;
    
    for (int ray = 0; ray < RAYS_NUMBER; ray++) {
        double sin_a = sin(current_ray_angle);
        double cos_a = cos(current_ray_angle);
        
        double current_depth = 0.0;
        
        for (int depth_step = 0; depth_step < MAX_DEPTH; depth_step++) {
            double x = player_x + depth_step * cos_a;
            double y = player_y + depth_step * sin_a;
            
            int map_x = (int)(x / CELL_SIZE_X);
            int map_y = (int)(y / CELL_SIZE_Y);
            
            if (map_x >= 0 && map_x < MAP_WIDTH_CELLS &&
                map_y >= 0 && map_y < MAP_HEIGHT_CELLS) {
                
                if (MAP[map_y][map_x] == 1) {
                    current_depth = depth_step;
                    break;
                }
            } else {
                current_depth = depth_step;
                break;
            }
            if (depth_step == MAX_DEPTH - 1) {
                current_depth = MAX_DEPTH;
            }
        }
        
        double corrected_depth = current_depth * cos(current_ray_angle - player_z);
        wall_distances[ray] = fmax(0.1, corrected_depth);

        current_ray_angle += DELTA_ANGLE;

        const double PROJECTION_PLANE_DIST = (SCREEN_WIDTH  / 2) / tan(HALF_FOV);
        double wall_height = (WALL_HEIGHT_SCALER * PROJECTION_PLANE_DIST / wall_distances[ray]);
                
        if (wall_height > SCREEN_HEIGHT) wall_height = SCREEN_HEIGHT;
        if (wall_height < 0) wall_height = 0;
                
        DrawRectangle(ray * (SCREEN_WIDTH / RAYS_NUMBER), (SCREEN_HEIGHT / 2) - (wall_height / 2), (SCREEN_WIDTH / RAYS_NUMBER) + 1, wall_height, GREEN);
    }
}
