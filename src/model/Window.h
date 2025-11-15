#ifndef CASSEBRIQUE_WINDOW_H
#define CASSEBRIQUE_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <optional>

static class Window {
    public:
    static sf::RenderWindow createWindow(unsigned int width, unsigned int height, std::string title);
    static sf::Vector2i getMousePosition(sf::RenderWindow& window);
    static void openWindow(sf::RenderWindow& window);
    static sf::Font loadFont(std::string fontPath);
    static void setTitle(sf::RenderWindow& window, sf::Font font,std::string titleText, unsigned int characterSize);
    static void setButton(std::string buttonText, int characterSize);





    private:
    bool isOpen;
    sf::Font font;


};


#endif //CASSEBRIQUE_WINDOW_H