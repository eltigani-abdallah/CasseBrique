#ifndef CASSEBRIQUE_PADDLE_H
#define CASSEBRIQUE_PADDLE_H
#include <SFML/Graphics.hpp>
#include "Direction.h"


class Paddle {

public:
    /**
     * Construct a paddle
     * @param screenWidth to set paddle location should be inherited from GameManager
     * @param screenHeight to set paddle starting location should be inherited from GameManager
     */
    Paddle(float screenWidth, float screenHeight);

    /**
     * move the paddle left and right
     * @param direction Direction enum that goes LEFT and RIGHT
     * @param deltaTime framerate
     */
    void move(Direction direction, float deltaTime);

    /**
     *
     * @return sf::RectangleShape of the paddle
     */
    const sf::RectangleShape& getShape() const;

    /**
     *
     * @return sf::Vector2f of the paddle position
     */
    sf::Vector2f getPosition() const;

    /**
     *
     * @return sf::Vector2f of the paddle size
     */
    sf::Vector2f getSize() const;

    /**
     * set the paddle's current speed. used to double the speed when holding shift
     * @param newSpeed new speed for the paddle
     */
    void setCurrentSpeed(float newSpeed);

    /**
     *
     * @return float of the paddle's original seed
     */
    float getOriginSpeed() const;

    /**
     * reset paddle to starting location
     */
    void reset();




private:

    sf::RectangleShape shape;
    float currentSpeed;
    float originSpeed;
    float offset;

    float screenWidth;
    float screenHeight;
};


#endif //CASSEBRIQUE_PADDLE_H