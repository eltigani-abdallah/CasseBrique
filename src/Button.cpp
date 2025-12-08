#include "Button.h"

Button::Button(std::string buttonLabel, sf::Font font, sf::Vector2f position, sf::Color normalColor, sf::Color hoverColor){
    buttonText.emplace(font);
    buttonText->setCharacterSize(textSize);
    buttonText->setString(buttonLabel);
    buttonText->setOrigin(buttonText->getLocalBounds().getCenter());
    buttonText->setPosition(position);
    buttonText->setFillColor(normalColor);

    this->hoverColor=hoverColor;
}
