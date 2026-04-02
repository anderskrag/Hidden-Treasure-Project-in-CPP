#include "TreasureWindow.h"
#include <iostream>

void GameWindow::draw_player(Player& player){
    draw_rectangle({player.col_index * tile_width +5, (player.row_index - first_tile_line_index) * tile_height +5}, tile_width -10, tile_height -5, TDT4102::Color::grey);
    if(player.facing_left){
        draw_rectangle({player.col_index * tile_width + player_eye_distance_from_front, (player.row_index - first_tile_line_index) * tile_height + player_eye_distance_from_top}, 8, 8, TDT4102::Color::black);
    }
    else{
        draw_rectangle({(player.col_index + 1) * tile_width - player_eye_distance_from_front -8, (player.row_index - first_tile_line_index) * tile_height + player_eye_distance_from_top}, 8, 8, TDT4102::Color::black);
    }
}

void GameWindow::draw_world(GameWorld& world, Player& player){
    for(int i = first_tile_line_index; i < first_tile_line_index + world.init_height; i++){
        for(int j = 0; j < world.width; j++){
                draw_rectangle({j*tile_width, (i-first_tile_line_index)*tile_height}, tile_width, tile_height, charToColor.at(world.tile_vec.at(i).at(j).tile_type));
        }
        // std::cout << i << std::endl;     
    }
    draw_player(player);
}