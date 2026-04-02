#pragma once
#include "GameWorld.h"
#include "TreasureWindow.h"
#include <vector>

class HiddenTreasure{
    GameWorld world;
    GameWindow window;
    PlayerRules player_rules;
    PlayerActions player_actions;
    std::vector<WorldTile> default_world_line;

    int top_left_x = 100;
    int top_left_y = 50;
    bool DOWN_already_down = false;
    bool UP_already_down = false;
    bool LEFT_already_down = false;
    bool RIGHT_already_down = false;

    public:
        HiddenTreasure(std::filesystem::path filename);

        void handle_input();
        void handle_gravity();
        void add_new_line();
        void run();
};