#ifndef CASSEBRIQUE_BUTTON_H
#define CASSEBRIQUE_BUTTON_H
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <optional>


/**
 * Buttons to be pressed in the main menu using the mouse
 */
class Button {

public:
    /**
     *  button constructor
     * @param buttonText text to place on the button
     * @param font font to be used. inherit from within GameManager constructor please
     * @param position button position. use the center of the button as reference because the constructor will set the text origin to its center
     * @param normalColor color by default
     * @param hoverColor color when hovered
     */
    Button(std::string buttonLabel,sf::Font font, sf::Vector2f position, sf::Color normalColor, sf::Color hoverColor);

    /**
     * check if the button is hovered or not
     */
    bool isHovered();

    /**
     * Start the game. sets GameState to GameState::RUNNING
     */
    void start();

    /**
     * Quits the application
     */
    void quit();

    /**
     * Resumes the game. only available if the menu was opened after quitting to the menu
     */
    void resume();



private:


    sf::RectangleShape shape;

    // color before hovering
    sf::Color normalColor;

    // color when hovering
    sf::Color hoverColor;

    // text to be placed on button
    std::optional<sf::Text> buttonText;

    // text size
    float textSize;

    bool hovered;
};


#endif //CASSEBRIQUE_BUTTON_H