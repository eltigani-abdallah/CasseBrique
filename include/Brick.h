#ifndef CASSEBRIQUE_BRICK_H
#define CASSEBRIQUE_BRICK_H
#include <SFML/Graphics.hpp>


class Brick {
private:
    sf::RectangleShape shape;
    int hp;



public:
    /**
     * Construct a brick, otherwise it wouldn't be called <b>brick</b> breaker
     * @param posX X position of the brick's top left corner
     * @param posY Y position of the brick's top left corner
     * @param hp starting hp
     */
    Brick(float posX, float posY, int hp);

    /**
     * reduces the HP of a brick by 1. <br> maybe in the future bricks would have more HP?
     */
    void getHit();

    /**
     *
     * @return true if brick hp is less than or equals 0
     */
    bool isDestroyed() const;

    /**
     *
     * @return sf::Rectangle shape address
     */
    const sf::RectangleShape& getShape() const;

    /**
     *
     * @return brick top left corner coordinates as sf::Vector2f
     */
    sf::Vector2f getPosition() const;

    /**
     *
     * @return brick size as sf::Vector2f
     */
    sf::Vector2f getSize() const;


};


#endif //CASSEBRIQUE_BRICK_H