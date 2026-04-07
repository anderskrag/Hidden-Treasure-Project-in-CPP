#include "TreasureWindow.h"
#include <iostream>

void GameWindow::draw_lvl(Player& player){
    std::string lvl_string = "lvl: ";
    lvl_string += std::to_string(player.lvl);
    draw_text({8*64, 18}, lvl_string);
}

void GameWindow::draw_gold(GameWorld& world){
    for(Gold gold : world.gold_vec){
        draw_rectangle({gold.col_index * tile_width + 20, (gold.row_index - first_tile_line_index) * tile_height + 20}, 20, 20, TDT4102::Color::gold);
    }
}

void GameWindow::draw_money(Player& player){
    std::string money_string = "$$$: ";
    money_string += std::to_string(player.money);
    draw_text({5*64, 18}, money_string, TDT4102::Color::gold);
}

void GameWindow::draw_health(Player& player){
    int bar_height = 50;
    int bar_width = 110;
    draw_rectangle(health_topleft, bar_width, bar_height, TDT4102::Color::white);
    for(int i = 0; i < player.health; i++){
        draw_rectangle({health_topleft.x + i + 5, health_topleft.y + 5}, 1, bar_height - 10, TDT4102::Color::red);
    }
}

void GameWindow::draw_hearts(GameWorld& world){
    for(Heart heart : world.hearts_vec){
        draw_rectangle({heart.col_index * tile_width + 20, (heart.row_index - first_tile_line_index) * tile_height + 20}, 20, 20, TDT4102::Color::red);
    }
}

void GameWindow::draw_player(Player& player){
    draw_rectangle({player.col_index * tile_width +5, (player.row_index - first_tile_line_index) * tile_height +5}, tile_width -10, tile_height -5, TDT4102::Color::grey);
    if(player.facing_left){
        draw_rectangle({player.col_index * tile_width + player_eye_distance_from_front, (player.row_index - first_tile_line_index) * tile_height + player_eye_distance_from_top}, 8, 8, TDT4102::Color::black);
    }
    else{
        draw_rectangle({(player.col_index + 1) * tile_width - player_eye_distance_from_front -8, (player.row_index - first_tile_line_index) * tile_height + player_eye_distance_from_top}, 8, 8, TDT4102::Color::black);
    }
    draw_health(player);
    draw_money(player);
    draw_lvl(player);
}

void GameWindow::draw_world(GameWorld& world, Player& player){
    for(int i = first_tile_line_index; i < first_tile_line_index + world.init_height; i++){
        for(int j = 0; j < world.width; j++){
                draw_rectangle({j*tile_width, (i-first_tile_line_index)*tile_height}, tile_width, tile_height, charToColor.at(world.tile_vec.at(i).at(j).tile_type));
        }
    }
    draw_gold(world);
    draw_hearts(world);
    draw_player(player);
}