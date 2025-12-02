#include "GameManager.h"

GameManager::GameManager(unsigned int windowWidth, unsigned int windowHeight, GameState state)
    : window(sf::VideoMode({windowWidth, windowHeight}),"CassarBrique"),
    paddle(windowWidth, windowHeight),
    state(state){
    window.setFramerateLimit(60);

    initializeBricks(5,5);

    font.openFromFile("../asset/font/arial.ttf");

    winText.emplace(font);
    winText->setCharacterSize(30);
    winText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2));
    winText->setString("VICTORY");

    loseText.emplace(font);
    loseText->setCharacterSize(30);
    loseText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2));
    loseText->setString("GAME OVER");


    restartText.emplace(font);
    restartText->setCharacterSize(15);
    restartText->setString("Press [Space] to restart");

    restartText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2+30));


}

void GameManager::handleEvents() {
    while (const std::optional event =window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void GameManager::update(float deltaTime) {

    if (state==GameState::RUNNING) {
        ball.update(deltaTime);
        sf::Vector2f ballPos= ball.getPosition();
        sf::Vector2f ballSize= ball.getSize();
        sf::Vector2f ballCenter(ballPos.x+ballSize.x/2,ballPos.y+ballSize.y/2);

        // ↓ check if all bricks are destroyed ↓
        if (bricks.empty()) {
            state=GameState::WIN;
        }

        // ↑ check if all bricks are destroyed ↑

        // ↓ Ball collision ↓
        if (ballPos.x < 0 || ballPos.x +ballSize.x > window.getSize().x) {
            ball.bounce(Surface::WALL);
        }

        if (ballPos.y < 0) {
            ball.bounce(Surface::TOP);
        }

        if (ball.isOutOfBounds(window.getSize().y)) {
            state=GameState::LOSE;
        }

        if (ball.getShape().getGlobalBounds().findIntersection(paddle.getShape().getGlobalBounds())) {
            ball.bounce(Surface::PADDLE);
        }

        for (Brick& brick:bricks) {
            sf::Vector2f brickPos = brick.getPosition();
            sf::Vector2f brickSize = brick.getSize();

            sf::Vector2f brickCenter(brickPos.x+brickSize.x/2,brickPos.y+brickSize.y/2);

            sf::Vector2f deltaBallPos(ballCenter.x-brickCenter.x, ballCenter.y-brickCenter.y);

            if (ball.getShape().getGlobalBounds().findIntersection(brick.getShape().getGlobalBounds())) {

                float overlapX = (ballSize.x/2 + brickSize.x/2)-abs(deltaBallPos.x);
                float overlapY = (ballSize.y/2 + brickSize.y/2)-abs(deltaBallPos.y);

                if (overlapX < overlapY) {
                    ball.bounce(Surface::WALL);
                }
                else {
                    ball.bounce(Surface::TOP);
                }


                brick.getHit();
            }
        }
        // ↑ ball collision ↑

        // ↓ erase bricks ↓
            bricks.erase(
                std::remove_if(bricks.begin(), bricks.end(),
                    [](const Brick& brick)
                    {return brick.isDestroyed();}),
                    bricks.end());
        // ↑ erase bricks ↑


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

    }

    // ↑ paddle movement ↑

    // ↓ if player wins ↓
    if (state == GameState::WIN) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            resetGame();
        }

    }
    // ↑ if player wins ↑

    // ↓ if player loses ↓

    if (state == GameState::LOSE) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            resetGame();
        }
    // ↑ if player loses ↑

    }



}

void GameManager::render() {
    window.clear();
    if (state == GameState::RUNNING) {
        window.draw(ball.getShape());
        window.draw(paddle.getShape());

        for (const Brick& brick:bricks) {
            window.draw(brick.getShape());
        }
    }

    if (state == GameState::LOSE) {
        window.draw(*loseText);
        window.draw(*restartText);
    }
    if (state == GameState::WIN) {
        window.draw(*winText);
        window.draw(*restartText);
    }
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

void GameManager::initializeBricks(float rowNum, float colNum) {
    for (int row=0;row<rowNum;row++) {
        for (int col=0;col<colNum;col++) {
            float x = 0+col*(100+30);
            float y = 0+row*(50+30);

            bricks.push_back(Brick(x, y));
        }
    }
}

void GameManager::resetGame() {
    ball.reset();
    paddle.reset();
    bricks.clear();
    initializeBricks(5,5);
    state=GameState::RUNNING;
}

