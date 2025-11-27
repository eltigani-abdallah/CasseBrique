#ifndef CASSEBRIQUE_GAMEMANAGER_H
#define CASSEBRIQUE_GAMEMANAGER_H
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "GameState.h"
#include <vector>

class GameManager {
public:
    GameManager(unsigned int windowWidth, unsigned int windowHeight);

    void run();
    void handleEvents();
    void update();
    void render();


private:
    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;

    //figure out a way to make a brick array
    std::vector<Brick> bricks;
    int score;
    GameState state;

};


#endif //CASSEBRIQUE_GAMEMANAGER_H