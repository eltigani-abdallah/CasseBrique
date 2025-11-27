#ifndef CASSEBRIQUE_BALL_H
#define CASSEBRIQUE_BALL_H
#include <SFML/Graphics.hpp>
#include "Surface.h"


class Ball {
private:
    sf::RectangleShape shape;
    float velocity;
    sf::Vector2f position;
    sf::Vector2f size;


public:
    Ball();

    void update(float deltaTime);
    void bounce(Surface surface);
    sf::RectangleShape getShape();
};


#endif //CASSEBRIQUE_BALL_H