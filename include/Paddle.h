#ifndef CASSEBRIQUE_PADDLE_H
#define CASSEBRIQUE_PADDLE_H
#include <SFML/Graphics.hpp>
#include "Direction.h"


class Paddle {

public:
    Paddle(float screenWidth, float screenHeight);


    void move(Direction direction, float deltaTime);
    const sf::RectangleShape& getShape() const;
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;




private:

    sf::RectangleShape shape;
    float speed;
    float offset;
};


#endif //CASSEBRIQUE_PADDLE_H