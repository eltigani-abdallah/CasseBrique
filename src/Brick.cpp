#include "Brick.h"

Brick::Brick(float posX, float posY) :
shape(sf::Vector2f(60,30)){
    shape.setPosition(sf::Vector2f(posX, posY));
    shape.setFillColor(sf::Color::White);

    hp = 1;

}

void Brick::getHit() {
    hp-=1;
}

bool Brick::isDestroyed() const {
    return hp <= 0;
}

const sf::RectangleShape&  Brick::getShape() const {
    return shape;
}

sf::Vector2f Brick::getSize() const {
    return shape.getSize();
}

sf::Vector2f Brick::getPosition() const {
    return shape.getPosition();
}
