#include "GameManager.h"


int main() {
    GameManager gm(600,800, GameState::MENU);

    gm.run();


    return 0;
}