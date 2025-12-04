#include "GameManager.h"


int main() {
    GameManager gm(600,800, GameState::PAUSE);

    gm.run();


    return 0;
}