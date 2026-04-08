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
        int money = 0;
        unsigned int lvl = 1;

        Player() : row_index(1), col_index(1), facing_left(false) {};
        Player(int row_index, int col_index, bool facing_left, int health, int money, unsigned int lvl) 
        : row_index(row_index), col_index(col_index), facing_left(facing_left), health(health), money(money), lvl(lvl) {};
};

class Heart {
    public:
        int row_index;
        int col_index;

        Heart(int row_index, int col_index) : row_index(row_index), col_index(col_index){};
};

class Gold {
    public:
        int row_index;
        int col_index;

        Gold(int row_index, int col_index) : row_index(row_index), col_index(col_index){};
};

class Fire {
    public:
        int row_index;
        int col_index;
        Fire(int row_index, int col_index) : row_index(row_index), col_index(col_index){};
};

class GameWorld {
    public:
        std::vector<std::vector<WorldTile>> tile_vec;
        Player playerInWorld;
        int width;
        int init_height;
        int height;
        int sky_height;

        int lack_of_air;
        double heart_chance;
        double gold_chance;
        double fire_chance;
        
        std::vector<Gold> gold_vec;
        std::vector<Heart> hearts_vec;
        std::vector<Fire> fire_vec;

        std::vector<WorldTile> default_world_line;
        GameWorld(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, double fire_chance, unsigned int lvl);

        void clearWorld();
};

class PlayerRules {
    public:
        bool canMoveLeft(GameWorld& world);
        bool canMoveRight(GameWorld& world);
        bool canDigLeft(GameWorld& world);
        bool canDigRight(GameWorld& world);
        bool canDigDownLeft(GameWorld& world);
        bool canDigDownRight(GameWorld& world);

        bool heartCollisionCheck(GameWorld& world);
        bool goldCollisionCheck(GameWorld& world);
        bool fireCollisionCheck(GameWorld& world);
};

class PlayerActions {
    public:
        void moveLeft(GameWorld& world);
        void moveRight(GameWorld& world);
        void digLeft(GameWorld& world);
        void digRight(GameWorld& world);
        void digDownLeft(GameWorld& world);
        void digDownRight(GameWorld& world);
        void heartCollision(GameWorld& world);
        void goldCollision(GameWorld& world);
        void fireCollision(GameWorld& world);
    };
