#include "GameManager.h"

GameManager::GameManager(unsigned int windowWidth, unsigned int windowHeight)
    : window(sf::VideoMode({windowWidth, windowHeight}),"CassarBrique"),
    paddle(windowWidth, windowHeight){
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
    sf::Vector2f ballPos= ball.getPosition();
    sf::Vector2f ballSize= ball.getSize();

    sf::Vector2f paddlePos= paddle.getPosition();
    sf::Vector2f paddleSize= paddle.getSize();

    // ↓ Ball collision ↓
    if (ballPos.x < 0 || ballPos.x +ballSize.x > window.getSize().x) {
        ball.bounce(Surface::WALL);
    }

    if (ballPos.y < 0) {
        ball.bounce(Surface::TOP);
    }

    if (ball.isOutOfBounds(window.getSize().y)) {
        ball.bounce(Surface::TOP);
    }

    if (ballPos.y + ballSize.y >= paddlePos.y) {
        ball.bounce(Surface::PADDLE);
    }

    // ↑ ball collision ↑

    // ↓ paddle movement ↓

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        paddle.move(Direction::LEFT, deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        paddle.move(Direction::RIGHT, deltaTime);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) {
        paddle.setCurrentSpeed(paddle.getOriginSpeed() * 2);
    } else {
        paddle.setCurrentSpeed(paddle.getOriginSpeed());
    }
    // ↑ paddle movement ↑



}

void GameManager::render() {
    window.clear();

    window.draw(ball.getShape());
    window.draw(paddle.getShape());
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
