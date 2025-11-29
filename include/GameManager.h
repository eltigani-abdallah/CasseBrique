#ifndef CASSEBRIQUE_GAMEMANAGER_H
#define CASSEBRIQUE_GAMEMANAGER_H
#include "./Paddle.h"
#include "./Ball.h"
#include "./Brick.h"
#include "./GameState.h"
#include <vector>
#include <SFML/System/Clock.hpp>

class GameManager {
public:
    GameManager(unsigned int windowWidth, unsigned int windowHeight);

    void run();
    void handleEvents();
    void update(float deltaTime);
    void render();


private:
    sf::RenderWindow window;
    sf::Clock clock;
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;
    int score;
    GameState state;

};


#endif //CASSEBRIQUE_GAMEMANAGER_H