#include "HiddenTreasure.h"
#include <fstream>
#include <filesystem>
#include "time.h" 
#include <random>  

HiddenTreasure::HiddenTreasure(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, double fire_chance, unsigned int lvl)
: world(filename, lack_of_air, heart_chance, gold_chance, fire_chance, lvl),
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

    if(player_rules.heartCollisionCheck(this->world)){
        player_actions.heartCollision(this->world);
    }
    if(player_rules.goldCollisionCheck(this->world)){
        player_actions.goldCollision(this->world);
    }
    if(player_rules.fireCollisionCheck(this->world)){
        player_actions.fireCollision(this->world);
    }
}

void HiddenTreasure::add_new_line(){
    world.height++;

    std::vector<WorldTile> temp_line;
    temp_line = world.default_world_line;
    for(int i = 2; i < world.width - 2; i++){
        std::random_device my_rd;
        std::default_random_engine generator(my_rd());
        std::uniform_real_distribution<double> dist(0, 1);
        double res = dist(generator);
        if(res < world.heart_chance){
            temp_line.at(i).tile_type = ' ';
            world.hearts_vec.push_back(Heart(world.height - 1, i));
        }
        else if(res < world.heart_chance + world.gold_chance){
            temp_line.at(i).tile_type = ' ';
            world.gold_vec.push_back(Gold(world.height - 1, i));
        }
        else if(res < world.heart_chance + world.gold_chance + world.fire_chance){
            world.fire_vec.push_back(Fire(world.height - 1, i));
        }

    }
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
            world.playerInWorld.health -= world.lack_of_air;
        }
}

void HiddenTreasure::new_lvl(){
    if(world.playerInWorld.money >= world.playerInWorld.lvl * 100){
            world.clearWorld();

            window.first_tile_line_index = 0;

            world = GameWorld("init_world.txt", world.lack_of_air, world.heart_chance*0.9, world.gold_chance, world.fire_chance, world.playerInWorld.lvl + 1);

    }
}

void HiddenTreasure::handle_menu(){
    if(window.is_key_down(KeyboardKey::SPACE)){
        game_live = true;
        world.clearWorld();
        window.first_tile_line_index = 0;
        world = GameWorld("init_world.txt", world.lack_of_air, 0.05, world.fire_chance, world.gold_chance, 1);
        start_time = time(0);
    }
}

void HiddenTreasure::write_score_to_file(std::filesystem::path filename){
    if(!score_written){
        std::ifstream is{filename};
        std::ofstream os_temp{"temp.txt"};
        std::string temp_line;
        while(getline(is, temp_line)){
            os_temp << temp_line << std::endl;
        }
        std::ofstream os{filename};
        std::ifstream is_temp{"temp.txt"};
        int place;
        std::string lvl_string;
        int lvl_on_line;
        std::string whitespace;

        bool line_added = false;
        while(is_temp >> place >> lvl_string >> lvl_on_line){
            // is_temp >> place >> lvl_string >> lvl_on_line;
            getline(is_temp, whitespace); // fjerner /n

            if(lvl_on_line >= world.playerInWorld.lvl){
                os << place << " " << lvl_string << " " << lvl_on_line << std::endl;
            }
            else if(lvl_on_line < world.playerInWorld.lvl && !line_added){
                os << place << " " << lvl_string << " " << world.playerInWorld.lvl << std::endl;
                os << place + 1 << " " << lvl_string << " " << lvl_on_line << std::endl;
                line_added = true;
            }
            else{
                os << place + 1 << " " << lvl_string << " " << lvl_on_line << std::endl;
            }
            
        }

        if(!line_added){
            os << place + 1 << " " << lvl_string << " " << world.playerInWorld.lvl << std::endl;
        }
    }
    score_written = true;
}

void HiddenTreasure::run()
{
    start_time = time(0);

    while (!window.should_close())
    {   
        new_lvl();

        if(game_live){
            score_written = false;

            handle_time();
            handle_input();
            handle_gravity();
            if(world.playerInWorld.health <= 0){
                game_live = false;
            }
        }

        window.draw_world(this->world, this->world.playerInWorld);
        if(!game_live){
            write_score_to_file("highscore.txt");
            window.draw_game_over(this->world);
            handle_menu();
        }

        window.next_frame();
    }
}