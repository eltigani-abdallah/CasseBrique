#include "GameManager.h"

GameManager::GameManager(unsigned int windowWidth, unsigned int windowHeight)
    : window(sf::VideoMode({windowWidth, windowHeight}),"CassarBrique"){
    window.setFramerateLimit(60);

    /*
     *ball, paddle constructors here
     */
}

void GameManager::handleEvents() {
    while (const std::optional event =window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void GameManager::update() {
    //handle physics here
}

void GameManager::render() {
    window.clear();

    //draw stuff here
    window.display();
}

void GameManager::run() {
    while (window.isOpen()) {
        handleEvents();


        update();
        render();

    }
}
