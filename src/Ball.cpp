#include "Ball.h"



Ball::Ball()
    : shape(sf::Vector2f(15,15)){
    shape.setPosition(sf::Vector2f(300,620));
    velocity = sf::Vector2f(100,200);
    shape.setFillColor(sf::Color::White);
}

sf::Vector2f Ball::getSize() const {
    return shape.getSize();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

bool Ball::isOutOfBounds(float screenHeight) {
    if (shape.getPosition().y > screenHeight) {
        return true;
    }
    return false;

}

const sf::RectangleShape& Ball::getShape() const {
    return shape;
}

void Ball::update(float deltaTime) {
    sf::Vector2f currentPosition = shape.getPosition();
    shape.setPosition(currentPosition+=velocity*deltaTime);
}

void Ball::bounce(Surface surface) {
    switch (surface) {
        case Surface::TOP:
        case Surface::PADDLE:
            velocity.y*=-1;
            break;
        case Surface::WALL:
            velocity.x*=-1;
            break;
    }
}