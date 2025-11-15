
#ifndef CASSEBRIQUE_BUTTON_H
#define CASSEBRIQUE_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(sf::Vector2f size, sf::Vector2f position,
        sf::Color defaultColor,sf::Color hoverColor,
        sf::Font font);

    ~Button();

    void onHover();

    bool mouseIsPressed();
    bool mouseIsReleased();

private:
    sf::Vector2f size;
    sf::Vector2f position;

    sf::Color defaultColor;
    sf::Color hoverColor;


    bool isHovered;
    bool isClicked;
    bool isClickedInButton;

    bool isPressed;
    bool isReleased;




};

#endif //CASSEBRIQUE_BUTTON_H