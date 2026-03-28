#include "TreasureWindow.h"

void GameWindow::draw_world(GameWorld world){
    for(int i = 0; i < 7; i++){
            for(int j = 0; j < 17; j++){
                draw_rectangle({j*world.tile_vec.at(i).at(j).pixels_width, i*world.tile_vec.at(i).at(j).pixels_height}, 64, 64, charToColor.at(world.tile_vec.at(i).at(j).tile_type));
            }
        }
}