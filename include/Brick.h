#ifndef CASSEBRIQUE_BRICK_H
#define CASSEBRIQUE_BRICK_H

#include <SFML/Graphics.hpp>


class Brick {
private:
    sf::RectangleShape shape;
    int hits;
    bool isActive;


public:

    void getHit();
    void destroy();
    sf::RectangleShape getShape();
};


#endif //CASSEBRIQUE_BRICK_H