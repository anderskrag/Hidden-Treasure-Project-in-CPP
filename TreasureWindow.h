#pragma once
#include "AnimationWindow.h"
#include "GameWorld.h"

class GameWindow : public TDT4102::AnimationWindow {
    private:
    

    public:
        GameWindow(int x = 50, int y = 50, int width = 1024, int height = 768, const std::string& title = "Animation Window")
         : AnimationWindow(x, y, width, height, title){};
        void draw_world(GameWorld world);
};