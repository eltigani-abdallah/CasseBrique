#include "Window.h"



sf::RenderWindow Window::createWindow(unsigned int width, unsigned int height, std::string title) {
    return sf::RenderWindow(sf::VideoMode({width, height}),title);
}


sf::Vector2i getMousePosition(sf::RenderWindow& window) {
    return sf::Mouse::getPosition(window);
}

void openWindow(sf::RenderWindow& window) {
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

        }
    }
}

sf::Font loadFont(std::string fontPath) {
    sf::Font font;
    if (!font.openFromFile(fontPath)) {
        std::cerr << "Could not load font from file " << fontPath << std::endl;
        exit(1);
    }
        return font;
}

void setTitle(sf::RenderWindow& window,sf::Font font, std::string titleText, unsigned int characterSize) {
    sf::Text title(font, titleText);
    title.setCharacterSize(characterSize);
    title.setPosition(title.getPosition() + sf::Vector2f{150.f, 200.f});

    window.draw(title);

}
