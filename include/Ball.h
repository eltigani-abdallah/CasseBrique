#ifndef CASSEBRIQUE_BALL_H
#define CASSEBRIQUE_BALL_H
#include <SFML/Graphics.hpp>
#include "Surface.h"
#include "GameState.h"
#include <iostream>


class Ball {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;



public:
    Ball();

    void update(float deltaTime);
    void bounce(Surface surface);
    bool isOutOfBounds(float screenHeight);


    const sf::RectangleShape& getShape() const;
    sf::Vector2f getSize() const;
};


#endif //CASSEBRIQUE_BALL_H