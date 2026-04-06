#include "HiddenTreasure.h"
#include <iostream>
#include <filesystem>
#include "Stopwatch.h"
#include "time.h"   

HiddenTreasure::HiddenTreasure(std::filesystem::path filename)
: world(filename),
 window(top_left_x, top_left_y, world.width*64, world.init_height*64, "My Game") {};


void HiddenTreasure::handle_input()
{
    if (!window.is_key_down(KeyboardKey::LEFT))
    {
        LEFT_already_down = false;
    }
    if (window.is_key_down(KeyboardKey::LEFT) && !LEFT_already_down)
    {
        LEFT_already_down = true;

        if (player_rules.canMoveLeft(this->world))
        {
            player_actions.moveLeft(this->world);
        }
        else if (player_rules.canDigLeft(this->world))
        {
            player_actions.digLeft(this->world);
        }
        if (!world.playerInWorld.facing_left)
        {
            world.playerInWorld.facing_left = true;
        }
    }

    if (!window.is_key_down(KeyboardKey::RIGHT))
    {
        RIGHT_already_down = false;
    }
    if (window.is_key_down(KeyboardKey::RIGHT) && !RIGHT_already_down)
    {
        RIGHT_already_down = true;
        if (player_rules.canMoveRight(this->world))
        {
            player_actions.moveRight(this->world);
        }
        else if (player_rules.canDigRight(this->world))
        {
            player_actions.digRight(this->world);
        }
        if (world.playerInWorld.facing_left)
        {
            world.playerInWorld.facing_left = false;
        }
    }

    if (!window.is_key_down(KeyboardKey::DOWN))
    {
        DOWN_already_down = false;
    }
    if (window.is_key_down(KeyboardKey::DOWN) && !DOWN_already_down)
    {
        DOWN_already_down = true;

        if (player_rules.canDigDownLeft(this->world)){
            player_actions.digDownLeft(this->world);
        }

        if (player_rules.canDigDownRight(this->world)){
            player_actions.digDownRight(this->world);
        }
    }
}

void HiddenTreasure::add_new_line(){
    std::vector<WorldTile> temp_line;
    temp_line = world.default_world_line;
    world.tile_vec.push_back(temp_line);
}

void HiddenTreasure::handle_gravity()
{
    if (world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index).tile_type == ' ')
    {
        world.playerInWorld.row_index++;
    }
    if(world.playerInWorld.row_index > window.first_tile_line_index + world.init_height - 4){
        window.first_tile_line_index++;
        add_new_line();
    }
}

void HiddenTreasure::handle_time(){
    if(time(0) - start_time > 1){
            start_time++;
            world.playerInWorld.health--;
        }
}

void HiddenTreasure::run()
{
    start_time = time(0);

    while (!window.should_close())
    {   
        handle_time();

        if(world.playerInWorld.health > 0){
            window.draw_world(this->world, this->world.playerInWorld);
            handle_input();
            handle_gravity();
            window.next_frame();
        }
        else{
            std::cout << "You lost!" << std::endl;
        }
    }
}