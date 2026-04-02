#pragma once
#include "AnimationWindow.h"
#include "GameWorld.h"

class GameWindow : public TDT4102::AnimationWindow {
    private:
        int tile_width = 64;
        int tile_height = 64;
        int player_eye_distance_from_front = tile_width*0.2;
        int player_eye_distance_from_top = tile_height*0.3;     

    public:
        int first_tile_line_index = 0;

        GameWindow(int x = 50, int y = 50, int width = 1024, int height = 768, const std::string& title = "Animation Window")
         : AnimationWindow(x, y, width, height, title){};
        void draw_player(Player& player);
        void draw_world(GameWorld& world, Player& player);
};