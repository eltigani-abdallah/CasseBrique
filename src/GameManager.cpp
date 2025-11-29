#include "GameManager.h"

GameManager::GameManager(unsigned int windowWidth, unsigned int windowHeight)
    : window(sf::VideoMode({windowWidth, windowHeight}),"CassarBrique"){
    window.setFramerateLimit(60);

}

void GameManager::handleEvents() {
    while (const std::optional event =window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void GameManager::update(float deltaTime) {

    ball.update(deltaTime);

    //handle physics here
}

void GameManager::render() {
    window.clear();

    window.draw(ball.getShape());
    //draw stuff here
    window.display();
}

void GameManager::run() {
    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();
        handleEvents();


        update(deltaTime.asSeconds());
        render();

    }
}
