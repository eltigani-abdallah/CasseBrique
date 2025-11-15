#ifndef CASSEBRIQUE_MOUSE_H
#define CASSEBRIQUE_MOUSE_H
#include <SFML/Graphics.hpp>
/**
@brief Controls and returns mouse info. <br>
easier than performing calculations on the fly
 */
class Mouse {
public:
    /**
     *
     * @param window  pointer to the address of a sf::RenderWindow window
     * @return mouse position as sf::Vector2f
     */
    static sf::Vector2f getMousePosition(sf::RenderWindow* window);

    /**
     * @brief checks if the mouse was clicked
     * @return true if the mouse was clicked, otherwise returns false
     */
    static bool mouseLeftClick();

    /**
     * @brief checks if the mouse was <b>released</b>
     * @return true if released after a click, false otherwise
     */
    static bool mouseLeftRelease();

private:

    //previous state of left mouse click, to be used to check for release
    static bool prevState;
    // current state of left mouse click
    static bool currentState;


};

#endif //CASSEBRIQUE_MOUSE_H