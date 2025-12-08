#include "Button.h"

Button::Button(std::string buttonLabel, const sf::Font& font, float textSize, sf::Vector2f position, sf::Color normalColor, sf::Color hoverColor)
    : shape(sf::Vector2f(100,50)){

    shape.setOrigin(shape.getLocalBounds().getCenter());
    shape.setPosition(position);



    buttonText.emplace(font);
    buttonText->setCharacterSize(textSize);
    buttonText->setString(buttonLabel);
    buttonText->setOrigin(buttonText->getLocalBounds().getCenter());
    buttonText->setPosition(position);
    buttonText->setFillColor(sf::Color::Black);

    this->hoverColor = hoverColor;
    this->normalColor = normalColor;

}


bool Button::isHovered(sf::RenderWindow& window) {
    if (shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {

        shape.setFillColor(hoverColor);
        return true;
    }

    shape.setFillColor(normalColor);
    return false;
}

bool Button::isClicked(sf::RenderWindow& window) {
    if (isHovered(window) == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        return true;
    }
    return false;
}

const sf::RectangleShape&  Button::getShape() const{
    return shape;
}

const sf::Text& Button::getText() const {
    return buttonText.value();
}