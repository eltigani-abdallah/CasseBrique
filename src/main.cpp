#include "GameManager.h"


int main() {
    GameManager gm(600,800, GameState::CANNON);

    gm.run();


    return 0;
}