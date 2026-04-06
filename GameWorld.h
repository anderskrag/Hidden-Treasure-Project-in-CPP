#pragma once
#include "AnimationWindow.h"
#include <filesystem>
#include "fstream"
#include "map"
#include "string"

const std::map<char, TDT4102::Color> charToColor {
    {'E', TDT4102::Color::maroon},          //Empty
    {'W', TDT4102::Color::purple},          //Wall
    {'#', TDT4102::Color::saddle_brown},    //Rock  
    {' ', TDT4102::Color::black},     //No rock
    {'S', TDT4102::Color::deep_skyblue},    //Sky
    {'B', TDT4102::Color::green},           //Health and money bar
    {'P', TDT4102::Color::dark_gray},
};

class WorldTile {
    public:
        char tile_type;
    
    WorldTile() : tile_type(' ') {};
    WorldTile(char tile_type) : tile_type(tile_type) {};
};

class Player {
    public:
        int row_index;
        int col_index;
        bool facing_left;
        int health = 100;
        TDT4102::Point health_topleft = {static_cast<int>(0.2*64), static_cast<int>(0.2*64)};

};

class GameWorld {
    public:
        std::vector<std::vector<WorldTile>> tile_vec;
        Player playerInWorld;
        int width;
        int init_height;
        int sky_height;
        std::vector<WorldTile> default_world_line;
        GameWorld(std::filesystem::path filename);
};

class PlayerRules {
    public:
        bool canMoveLeft(GameWorld& world);
        bool canMoveRight(GameWorld& world);
        bool canDigLeft(GameWorld& world);
        bool canDigRight(GameWorld& world);
        bool canDigDownLeft(GameWorld& world);
        bool canDigDownRight(GameWorld& world);
};

class PlayerActions {
    public:
        void moveLeft(GameWorld& world);
        void moveRight(GameWorld& world);
        void digLeft(GameWorld& world);
        void digRight(GameWorld& world);
        void digDownLeft(GameWorld& world);
        void digDownRight(GameWorld& world);
};
