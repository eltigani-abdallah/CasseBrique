#ifndef CASSEBRIQUE_BRICK_H
#define CASSEBRIQUE_BRICK_H
#include <SFML/Graphics.hpp>


class Brick {
private:
    sf::RectangleShape shape;
    int hp;



public:

    Brick(float posX, float posY);
    void getHit();
    bool isDestroyed() const;


    const sf::RectangleShape& getShape() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    void setPosition(sf::Vector2f pos);
};


#endif //CASSEBRIQUE_BRICK_H