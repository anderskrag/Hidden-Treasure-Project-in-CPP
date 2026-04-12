#include "GameWorld.h"
#include <iostream>
#include <random>
#include <system_error>

GameWorld::GameWorld(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, double fire_chance, unsigned int lvl) : lack_of_air(lack_of_air), heart_chance(heart_chance), gold_chance(gold_chance), fire_chance(fire_chance) {
    std::ifstream is{filename};

    try{
        if(!is){
            throw std::filesystem::filesystem_error("File not found", filename, std::make_error_code(std::errc::no_such_file_or_directory));
        }
        if(!(is >> init_height >> width >> sky_height)){
            throw std::filesystem::filesystem_error("Wrong format", filename, std::make_error_code(std::errc::invalid_argument));
        }
        
        height = init_height;
        tile_vec.resize(init_height, std::vector<WorldTile>(width));

        std::string line;
        getline(is, line); //Removes ' ' from the stream.
        int line_count = 0;
        while(getline(is, line)){
            for(int i = 0; i < width; i++){
                tile_vec.at(line_count).at(i) = WorldTile(line.at(i));
                if(tile_vec.at(line_count).at(i).tile_type == 'P'){
                    playerInWorld = Player(line_count, i, false, 100, 0, lvl);
                    playerInWorld.row_index = line_count;
                    playerInWorld.col_index = i;
                    playerInWorld.facing_left = false;
                    tile_vec.at(line_count).at(i).tile_type = 'S'; // Har nå ingen spiller-tile. Spilleren er uavhengig av brettet på et vis
                }
            }
            line_count++;
        }
        default_world_line = tile_vec.at(sky_height);

        for(int i = sky_height; i < init_height - 1; i++){
            for(int j = 2; j < width - 5; j++){
                std::random_device rd;
                std::default_random_engine generator(rd());
                std::uniform_real_distribution<double> distribution(0, 1);
                double res = distribution(generator);

                if(res < heart_chance){
                    tile_vec.at(i).at(j).tile_type = ' ';
                    hearts_vec.push_back(Heart(i, j));
                }
                else if(res < heart_chance + gold_chance){
                    tile_vec.at(i).at(j).tile_type = ' ';
                    gold_vec.push_back(Gold(i, j));
                }
                else if(res < heart_chance + gold_chance + fire_chance){
                    fire_vec.push_back(Fire(i, j));
                }
            }
        }
    }
    catch(std::filesystem::filesystem_error& e){
        std::cout << e.what() << std::endl;
    }
    catch(std::out_of_range& e){
        std::cout << "out of range when creating world" << std::endl;
    }
}

void GameWorld::clearWorld(){
    default_world_line.clear();
    gold_vec.clear();
    hearts_vec.clear();
    tile_vec.clear();
    fire_vec.clear();
}

bool PlayerRules::canMoveLeft(GameWorld& world){
    if((world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == ' '
    || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == 'S')
    && world.playerInWorld.facing_left){
        return true;
    }
    else{
        return false;
    }
}

bool PlayerRules::canMoveRight(GameWorld& world){
    if((world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == ' '
    || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == 'S')
    && !world.playerInWorld.facing_left){
        return true;
    }
    else{
        return false;
    }
}

bool PlayerRules::canDigLeft(GameWorld& world){
    if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == '#'
    && world.playerInWorld.facing_left){
        return true;
    }
    else{
        return false;
    }
}

bool PlayerRules::canDigRight(GameWorld& world){
    if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == '#'
    && !world.playerInWorld.facing_left){
        return true;
    }
    else{
        return false;
    }
}

bool PlayerRules::canDigDownLeft(GameWorld& world){
    if(
        (world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == '#'
        || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == ' '
        || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == 'S')
        &&
        (world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type == '#'
        || world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type == ' ')
        &&
        world.playerInWorld.facing_left
    ){
        return true;
    }
    else{
        return false;
    }
}

bool PlayerRules::canDigDownRight(GameWorld& world){
    if(
        (world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == '#'
        || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == ' '
        || world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == 'S')
        &&
        (world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type == '#'
        || world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type == ' ')
        &&
        !world.playerInWorld.facing_left
    ){
        return true;
    }
    else{
        return false;
    }
}

void PlayerActions::moveLeft(GameWorld& world){
    world.playerInWorld.col_index--;
}

void PlayerActions::moveRight(GameWorld& world){
    world.playerInWorld.col_index++;
}

void PlayerActions::digLeft(GameWorld& world){
    world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type = ' ';
};

void PlayerActions::digRight(GameWorld& world){
    world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type = ' ';
};

void PlayerActions::digDownLeft(GameWorld& world){
    if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type == 'S'){
        world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type = ' ';
    }
    else{
        world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index - 1).tile_type = ' ';
        world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index - 1).tile_type = ' ';
    }
};

void PlayerActions::digDownRight(GameWorld& world){
    if(world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type == 'S'){
        world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type = ' ';
    }
    else{
        world.tile_vec.at(world.playerInWorld.row_index).at(world.playerInWorld.col_index + 1).tile_type = ' ';
        world.tile_vec.at(world.playerInWorld.row_index + 1).at(world.playerInWorld.col_index + 1).tile_type = ' ';
    }
};


bool PlayerRules::heartCollisionCheck(GameWorld& world){
    for(Heart heart : world.hearts_vec){
        if(world.playerInWorld.row_index == heart.row_index && world.playerInWorld.col_index == heart.col_index){
            return true;
        }
    }
    return false;
}

void PlayerActions::heartCollision(GameWorld& world){
    if(world.playerInWorld.health + 10 > 100){
        world.playerInWorld.health = 100;
    }
    else{
        world.playerInWorld.health += 10;
    }
    for(int i = 0; i < world.hearts_vec.size(); i++){
        if(world.playerInWorld.row_index == world.hearts_vec.at(i).row_index && world.playerInWorld.col_index == world.hearts_vec.at(i).col_index){
            world.hearts_vec.erase(world.hearts_vec.begin() + i);
        }
    }
}

bool PlayerRules::goldCollisionCheck(GameWorld& world){
    for(Gold gold : world.gold_vec){
        if(world.playerInWorld.row_index == gold.row_index && world.playerInWorld.col_index == gold.col_index){
            return true;
        }
    }
    return false;
}

void PlayerActions::goldCollision(GameWorld& world){
    world.playerInWorld.money += 100;
    for(int i = 0; i < world.gold_vec.size(); i++){
        if(world.playerInWorld.row_index == world.gold_vec.at(i).row_index && world.playerInWorld.col_index == world.gold_vec.at(i).col_index){
            world.gold_vec.erase(world.gold_vec.begin() + i);
        }
    }
}

bool PlayerRules::fireCollisionCheck(GameWorld& world){
    for(Fire fire : world.fire_vec){
        if(fire.row_index == world.playerInWorld.row_index && fire.col_index==world.playerInWorld.col_index){
            return true;
        }
    }
    return false;
}

void PlayerActions::fireCollision(GameWorld& world){
    world.playerInWorld.health -= 10;
    for(int i = 0; i < world.fire_vec.size(); i++){
        if(world.playerInWorld.row_index == world.fire_vec.at(i).row_index && world.playerInWorld.col_index == world.fire_vec.at(i).col_index){
            world.fire_vec.erase(world.fire_vec.begin() + i);
        }
    }
}