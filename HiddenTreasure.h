#pragma once
#include "GameWorld.h"
#include "TreasureWindow.h"

class HiddenTreasure{
    GameWorld world;
    GameWindow window;
    bool DOWN_already_down = false;
    bool UP_already_down = false;
    bool LEFT_already_down = false;
    bool RIGHT_already_down = false;

    public:
        HiddenTreasure(std::filesystem::path filename) 
        : world(filename), window(50, 50, 64*17, 7*64, "My Game") {};

        void handle_input();
        void run();
};