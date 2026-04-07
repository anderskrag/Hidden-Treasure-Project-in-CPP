#include "GameWorld.h"
#include <iostream>
#include <random>

GameWorld::GameWorld(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, unsigned int lvl) : lack_of_air(lack_of_air), heart_chance(heart_chance), gold_chance(gold_chance) {
    std::ifstream is{filename};

    if(!is){
        std::cout << "Could not open file!" << std::endl;
    }

    is >> init_height >> width >> sky_height;
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
        }
    }
}

// GameWorld GameWorld::operator=(GameWorld rhs){
//     tile_vec = rhs.tile_vec;
//     playerInWorld.col_index = rhs.playerInWorld.col_index;
//     playerInWorld.row_index = rhs.playerInWorld.row_index;
//     playerInWorld.facing_left = rhs.playerInWorld.facing_left;
//     playerInWorld.money = rhs.playerInWorld.money;
//     playerInWorld.health = rhs.playerInWorld.health;
//     width = rhs.width;
//     gold_vec = rhs.gold_vec;
//     hearts_vec = rhs.hearts_vec;
// }

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