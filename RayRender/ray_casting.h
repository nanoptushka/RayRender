void ray_casting() {
    double currentRayAngle = player_z - HALF_FOV;
    
    for (int ray = 0; ray < RAYS_NUMBER; ray++) {
        double sin_a = sin(currentRayAngle);
        double cos_a = cos(currentRayAngle);
        
        double currentDepth = 0.0;
        
        for (int depth_step = 0; depth_step < MAX_DEPTH; depth_step++) {
            double x = player_x + depth_step * cos_a;
            double y = player_y + depth_step * sin_a;
            
            int mapX = (int)(x / CELL_SIZE_X);
            int mapY = (int)(y / CELL_SIZE_Y);
            
            if (mapX >= 0 && mapX < MAP_WIDTH_CELLS &&
                mapY >= 0 && mapY < MAP_HEIGHT_CELLS) {
                
                if (MAP[mapY][mapX] == 1) {
                    currentDepth = depth_step;
                    break;
                }
            } else {
                currentDepth = depth_step;
                break;
            }
            if (depth_step == MAX_DEPTH - 1) {
                currentDepth = MAX_DEPTH;
            }
        }
        
        double correctedDepth = currentDepth * cos(currentRayAngle - player_z);
        wall_distances[ray] = fmax(0.1, correctedDepth);

        currentRayAngle += DELTA_ANGLE ;
    }
}
