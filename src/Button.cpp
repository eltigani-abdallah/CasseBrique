#include "Button.h"

Button::Button(std::string buttonLabel, sf::Font font, float textSize, sf::Vector2f position, sf::Color normalColor, sf::Color hoverColor)
    : shape(sf::Vector2f(100,50)){

    shape.setOrigin(shape.getLocalBounds().getCenter());
    shape.setPosition(position);



    buttonText.emplace(font);
    buttonText->setCharacterSize(textSize);
    buttonText->setString(buttonLabel);
    buttonText->setOrigin(buttonText->getLocalBounds().getCenter());
    buttonText->setPosition(shape.getLocalBounds().getCenter());
    buttonText->setFillColor(normalColor);

    this->hoverColor = hoverColor;
    this->normalColor = normalColor;

}


bool Button::isHovered() {
    if (shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {

        shape.setFillColor(hoverColor);
        return true;
    }

    shape.setFillColor(normalColor);
    return false;
}

bool Button::isClicked() {
    if (isHovered() == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return true;
    }
    return false;
}