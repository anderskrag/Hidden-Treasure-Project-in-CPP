#include "GameWorld.h"
#include "TreasureWindow.h"
#include "HiddenTreasure.h"

int main(){
    HiddenTreasure my_game("init_world.txt", 1, 0.05, 0.03, 1);
    my_game.run();

    return 0;
}