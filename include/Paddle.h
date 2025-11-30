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

    void setCurrentSpeed(float newSpeed);
    float getOriginSpeed() const;




private:

    sf::RectangleShape shape;
    float currentSpeed;
    float originSpeed;
    float offset;

    float screenWidth;
    float screenHeight;
};


#endif //CASSEBRIQUE_PADDLE_H