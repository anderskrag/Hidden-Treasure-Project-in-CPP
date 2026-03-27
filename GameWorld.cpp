#include "GameWorld.h"
#include <iostream>

GameWorld::GameWorld(std::filesystem::path filename){
    std::ifstream is{filename};

    if(!is){
        std::cout << "Could not open file!" << std::endl;
    }

   
    is >> height >> width;
    tile_vec.resize(height, std::vector<WorldTile>(width));

    std::string line;
    getline(is, line); //Removes ' ' from the stream.
    int line_count = 0;
    while(getline(is, line)){
        for(int i = 0; i < width; i++){
            tile_vec.at(line_count).at(i) = WorldTile(line.at(i));
        }
        line_count++;
    }

}

// GameWorld::GameWorld(int init_height, int width){
//     tile_vec.resize(init_height, std::vector<WorldTile>(width));
// }
