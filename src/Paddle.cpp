#include "Paddle.h"

Paddle::Paddle(float screenWidth, float screenHeight)
    :shape(sf::Vector2f(150, 22)) {


    speed = 50;
    offset = 20;

    shape.setPosition(sf::Vector2f((screenWidth-shape.getSize().x)/2,
        screenHeight-shape.getSize().y-offset));
    shape.setFillColor(sf::Color::White);
}

const sf::RectangleShape &Paddle::getShape() const {
    return shape;
}
