#ifndef CASSEBRIQUE_BALL_H
#define CASSEBRIQUE_BALL_H
#include <SFML/Graphics.hpp>
#include "Surface.h"
#include "GameState.h"
#include <iostream>


class Ball {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    float speed;



public:
    /**
     * ball constructor
     */
    Ball();

    /**
     * move the ball in the space
     * @param deltaTime framerate
     */
    void update(float deltaTime);

    /**
     * bounce off the environment. reverses either velocity.x or velocity.y
     * @param surface enum (WALL, TOP, PADDLE)
     */
    void bounce(Surface surface);

    /**
     * check if the ball fell off the screen
     * @param screenHeight height of the screen. should be inheirted from GameManager
     * @return true if the ball is too far down
     */
    bool isOutOfBounds(float screenHeight);

    /**
     *
     * @return ball sf::Rectangle address
     */
    const sf::RectangleShape& getShape() const;

    /**
     *
     * @return sf::Vector2f of the ball's size
     */
    sf::Vector2f getSize() const;

    /**
     *
     * @return sf::Vector2f of the ball's position
     */
    sf::Vector2f getPosition() const;

    /**
     * set ball position
     * @param newPosition sf::Vector2f of the position the ball should be in
     */
    void setPosition(sf::Vector2f newPosition);

    /**
     *
     * @return sf::Vector2f of the ball's velocity
     */
    sf::Vector2f getVelocity() const;

    /**
     * set ball velocity to change directions
     * @param newVelocity new velocity of the ball
     */
    void setVelocity(sf::Vector2f newVelocity);

    /**
     *
     * @return ball speed
     */
    float getSpeed();

    /**
     *
     * @param newSpeed speed to set for the ball
     */
    void setSpeed(float newSpeed);

    /**
     * reset ball to its original position
     */
    void reset();
};


#endif //CASSEBRIQUE_BALL_H