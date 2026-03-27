#include "GameWorld.h"

int main(){

    GameWorld myWorld = GameWorld("World.txt");

    TDT4102::AnimationWindow game_window(50, 50, 64*17, 7*64, "My Game");
    
    while(!game_window.should_close()){
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 17; j++){
                game_window.draw_rectangle({j*64 - 300, i*64}, 64, 64, charToColor.at(myWorld.tile_vec.at(i).at(j).tile_type));
            }
        }
    
    game_window.next_frame();
    }

    return 0;
}