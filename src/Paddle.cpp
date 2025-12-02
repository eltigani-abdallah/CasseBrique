#include "Paddle.h"

Paddle::Paddle(float screenWidth, float screenHeight)
    :shape(sf::Vector2f(150, 22)) {

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    originSpeed = 100;
    currentSpeed = 100;
    offset = 20;

    shape.setPosition(sf::Vector2f((screenWidth-shape.getSize().x)/2,
        screenHeight-shape.getSize().y-offset));
    shape.setFillColor(sf::Color::White);
}

void Paddle::setCurrentSpeed(float newSpeed) {
    currentSpeed = newSpeed;
}

float Paddle::getOriginSpeed() const {
    return originSpeed;
}

const sf::RectangleShape &Paddle::getShape() const {
    return shape;
}

sf::Vector2f Paddle::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Paddle::getSize() const {
    return shape.getSize();
}

void Paddle::move(Direction direction, float deltaTime) {
    sf::Vector2f currentPosition = shape.getPosition();
    switch (direction) {
        case Direction::LEFT:
            currentPosition.x-=currentSpeed*deltaTime;
            if (currentPosition.x<0) {
                currentPosition.x=0;
            }
            break;
        case Direction::RIGHT:
            currentPosition.x+=currentSpeed*deltaTime;
            if (currentPosition.x>screenWidth-shape.getSize().x) {
                currentPosition.x=screenWidth-shape.getSize().x;
            }
            break;
    }

    shape.setPosition(currentPosition);
}

void Paddle::reset() {
    shape.setPosition(sf::Vector2f((screenWidth-shape.getSize().x)/2,
        screenHeight-shape.getSize().y-offset));
}