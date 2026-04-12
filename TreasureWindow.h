#pragma once
#include "AnimationWindow.h"
#include "GameWorld.h"

class GameWindow : public TDT4102::AnimationWindow {
    private:
        int tile_width = 64;
        int tile_height = 64;
        int player_eye_distance_from_front = tile_width*0.2;
        int player_eye_distance_from_top = tile_height*0.3;

        TDT4102::Image heart_pic{"heart.png"};
        TDT4102::Image fire_pic{"fire.png"};
        TDT4102::Image gold_pic{"gold.png"};
        TDT4102::Image player_left_pic{"player_left.png"};
        TDT4102::Image player_right_pic{"player_right.png"};

    public:
        int first_tile_line_index = 0;
        TDT4102::Point health_topleft = {static_cast<int>(0.2*64), static_cast<int>(0.2*64)};

        GameWindow(int x = 50, int y = 50, int width = 1024, int height = 768, const std::string& title = "Animation Window")
         : AnimationWindow(x, y, width, height, title){};
        void draw_gold(GameWorld& world);
        void draw_money(Player& player);
        void draw_health(Player& player);
        void draw_lvl(Player& player);
        void draw_hearts(GameWorld& world);
        void draw_player(Player& player);
        void draw_fire(GameWorld& world);
        void draw_world(GameWorld& world, Player& player);

        void draw_pause(GameWorld& world);
        void draw_game_over(GameWorld& world);
        void draw_highscore(std::filesystem::path filename="highscore.txt");
};