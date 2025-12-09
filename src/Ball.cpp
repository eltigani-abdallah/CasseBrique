#include "Ball.h"

#include "../cmake-build-debug/_deps/sfml-src/extlibs/headers/stb_image/stb_image.h"


Ball::Ball()
    : shape(sf::Vector2f(15,15)){

    velocity = sf::Vector2f(0,0);
    shape.setFillColor(sf::Color::White);
    speed= 0;
}

void Ball::reset() {
    shape.setPosition(sf::Vector2f(300,620));
}

sf::Vector2f Ball::getSize() const {
    return shape.getSize();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

void Ball::setPosition(sf::Vector2f newPosition) {
    shape.setPosition(newPosition);
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

void Ball::setVelocity(sf::Vector2f newVelocity) {
    velocity = newVelocity;
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
    shape.setPosition(currentPosition+=velocity*speed*deltaTime);
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

float Ball::getSpeed() {
    return speed;
}

void Ball::setSpeed(float newSpeed) {
    speed = newSpeed;
}