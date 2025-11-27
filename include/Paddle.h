#ifndef CASSEBRIQUE_PADDLE_H
#define CASSEBRIQUE_PADDLE_H
#include <SFML/Graphics.hpp>


class Paddle {

public:
    void move();
    sf::RectangleShape getShape();


private:

    sf::RectangleShape shape;
    float speed;
};


#endif //CASSEBRIQUE_PADDLE_H