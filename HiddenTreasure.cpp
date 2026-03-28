#include "HiddenTreasure.h"

void HiddenTreasure::handle_input(){
    if(!window.is_key_down(KeyboardKey::LEFT)){
        LEFT_already_down = false;
    }
    if(window.is_key_down(KeyboardKey::LEFT) && !LEFT_already_down){
            WorldTile temp_tile = world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1);
            world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1) = world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index);
            world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index) = temp_tile;
            world.playerInWorld.col_index--;
            world.playerInWorld.facing_left = true;
            LEFT_already_down = true;
        }


    if(!window.is_key_down(KeyboardKey::RIGHT)){
        RIGHT_already_down = false;
    }    
    if(window.is_key_down(KeyboardKey::RIGHT) && !RIGHT_already_down){
            WorldTile temp_tile = world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1);
            world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1) = world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index);
            world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index) = temp_tile;
            world.playerInWorld.col_index++;
            world.playerInWorld.facing_left = false;
            RIGHT_already_down = true;
        }

   
    if(!window.is_key_down(KeyboardKey::DOWN)){
        DOWN_already_down = false;
    }
    if(window.is_key_down(KeyboardKey::DOWN) && !DOWN_already_down){
        if(world.playerInWorld.facing_left){
            if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == '#' 
            && world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type == '#'){
                world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type = ' ';
                world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type = ' ';
            }
            if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == 'S'
            && world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type == '#'){
                world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type = ' ';
            }   
        }
        else{ //Player facing right
            if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == '#' 
            && world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type == '#'){
                world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type = ' ';
                world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type = ' ';
            }
            if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == 'S'
            && world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type == '#'){
                world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type = ' ';
            }
        }

        DOWN_already_down = true;
    }
}

void HiddenTreasure::run(){
    while(!window.should_close()){

        window.draw_world(world);
        handle_input();
        window.next_frame();
    }
}