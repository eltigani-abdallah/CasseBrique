#include "Button.h"

Button::Button(sf::Vector2f size, sf::Vector2f position,
        sf::Color defaultColor,sf::Color hoverColor, sf::Font font) {
    //size of button
    sf::RectangleShape shape(size);
    //position of button on screen
    shape.setPosition(position);

    this->defaultColor = defaultColor;
    this->hoverColor = hoverColor;

}

void Button::onHover() {
    //if hovered is true calculations etc.
    if ()
}