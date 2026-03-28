#include "GameWorld.h"
#include "TreasureWindow.h"
#include "HiddenTreasure.h"

int main(){
    HiddenTreasure my_game("init_world.txt");
    my_game.run();

    return 0;
}