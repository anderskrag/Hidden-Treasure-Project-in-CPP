#pragma once
#include "GameWorld.h"
#include "TreasureWindow.h"
#include <vector>
#include "time.h"

class HiddenTreasure{
    GameWorld world;
    int top_left_x = 100;
    int top_left_y = 50;
    GameWindow window;
    PlayerRules player_rules;
    PlayerActions player_actions;
    
    
    time_t start_time = 0;
    bool DOWN_already_down = false;
    bool UP_already_down = false;
    bool LEFT_already_down = false;
    bool RIGHT_already_down = false;
    
    bool game_live = true;

    public:
        HiddenTreasure(std::filesystem::path filename, int lack_of_air, double heart_chance, double gold_chance, unsigned int lvl);

        void handle_time();
        void handle_input();
        void handle_gravity();
        void handle_menu();

        void new_lvl();
        void add_new_line();
        void run();
};