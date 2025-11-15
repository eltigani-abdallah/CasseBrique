
#include "Mouse.h"

bool prevState = false;
bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);


sf::Vector2f Mouse::getMousePosition(sf::RenderWindow* window) {
    return sf::Vector2f(sf::Mouse::getPosition(*window));
}

bool Mouse::mouseLeftClick() {
    bool wasClicked = currentState && !prevState;
    prevState = currentState;
    return wasClicked;
}

bool Mouse::mouseLeftRelease() {
    bool wasReleased = prevState && !currentState;
    prevState = currentState;
    return wasReleased;
}



