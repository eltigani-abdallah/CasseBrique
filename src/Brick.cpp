#include "Brick.h"

Brick::Brick(float posX, float posY, int hp) :
shape(sf::Vector2f(100,50)){
    shape.setPosition(sf::Vector2f(posX, posY));

    this->hp = hp;

    switch (hp) {
        case 4:
            shape.setFillColor(sf::Color::Green);
            break;
        case 3:
            shape.setFillColor(sf::Color::Yellow);
            break;
        case 2:
            shape.setFillColor(sf::Color(255,165,0)); //orange
            break;
        case 1:
            shape.setFillColor(sf::Color::Red);
            break;

    }



}


void Brick::getHit() {
    hp-=1;
    switch (hp) {
        case 4:
            shape.setFillColor(sf::Color::Green);
            break;
        case 3:
            shape.setFillColor(sf::Color::Yellow);
            break;
        case 2:
            shape.setFillColor(sf::Color(255,165,0)); //orange
            break;
        case 1:
            shape.setFillColor(sf::Color::Red);
            break;

    }
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
