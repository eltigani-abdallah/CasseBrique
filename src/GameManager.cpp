#include "GameManager.h"

GameManager::GameManager(unsigned int windowWidth, unsigned int windowHeight, GameState state)
    : window(sf::VideoMode({windowWidth, windowHeight}),"CassarBrique"),
    paddle(windowWidth, windowHeight),
    state(state),
    generator(std::random_device{}()),hpDistribution(1,4)
    { //initialize members that must be initialized before object construction


    window.setFramerateLimit(60); //framerate limiter so the game doesn't go too fast

    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    initializeBricks(5,5);

    font.openFromFile("../asset/font/arial.ttf"); //open font from the path specified

    // ↓ winText manipulation ↓
    winText.emplace(font); //emplace is used to place the newly created sf::Text into std::optional
    winText->setCharacterSize(30);
    winText->setString("VICTORY");
    sf::FloatRect winTextBounds = winText->getLocalBounds();
    winText->setOrigin(winTextBounds.getCenter());
    winText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2));
    // ↑ winText manipulation ↑


    // ↓ loseText manipulation ↓
    loseText.emplace(font);
    loseText->setCharacterSize(30);
    loseText->setString("GAME OVER");
    sf::FloatRect loseTextBounds = loseText->getLocalBounds();
    loseText->setOrigin(loseTextBounds.getCenter());
    loseText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2-30));
    // ↑ loseTextManipulation ↑

    // ↓ pauseText manipulation ↓
    pauseText.emplace(font);
    pauseText->setCharacterSize(30);
    pauseText->setString("PAUSE");
    sf::FloatRect pauseTextBounds = pauseText->getLocalBounds();
    pauseText->setOrigin(pauseTextBounds.getCenter());
    pauseText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2-60));
    // ↑ pauseTextManipulation ↑




    // ↓ restartText manipulation ↓
    restartText.emplace(font);
    restartText->setCharacterSize(15);
    restartText->setString("Press [Space] to restart");
    sf::FloatRect restartTextBounds = restartText->getLocalBounds();
    restartText->setOrigin(restartTextBounds.getCenter());
    restartText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2+30));
    // ↑ restartText manipulation ↑

    // ↓ titleText manipulation ↓
    titleText.emplace(font);
    titleText->setCharacterSize(50);
    titleText->setString("CASSAR BRIQUE");
    sf::FloatRect titleTextBounds = titleText->getLocalBounds();
    titleText->setOrigin(titleTextBounds.getCenter());
    titleText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2-100));
    // ↑ titleText manipulation ↑

    // ↓ score manipulation ↓
    scoreText.emplace(font);
    score = 0;
    scoreText->setCharacterSize(30);
    scoreText->setString("Score: " + std::to_string(score));
    sf::FloatRect scoreBounds=scoreText->getLocalBounds();
    scoreText->setOrigin(scoreBounds.getCenter());
    scoreText->setPosition(sf::Vector2f(scoreBounds.getCenter().x,scoreBounds.getCenter().y));
    // ↑ score manipulation ↑

    // ↓ lives manipulation ↓
    livesText.emplace(font);
    lives = 3;
    livesText->setCharacterSize(30);
    livesText->setString("Lives: " + std::to_string(lives));
    sf::FloatRect livesTextBounds =livesText->getLocalBounds();
    livesText->setOrigin(livesTextBounds.getCenter());
    livesText->setPosition(sf::Vector2f(windowWidth-livesTextBounds.getCenter().x,livesTextBounds.getCenter().y));
    // ↑ lives manipultion ↑

    // ↓ menu buttons ↓
    startButton.emplace("START", font, 30,
        sf::Vector2f(windowWidth / 2, windowHeight / 2),
    sf::Color::White, sf::Color::Green);

    quitButton.emplace("QUIT", font, 30,
        sf::Vector2f(windowWidth / 2, windowHeight / 2 + 100),
        sf::Color::White, sf::Color::Red);
    // ↑ menu buttons ↑



}

void GameManager::handleEvents() {
    while (const std::optional event =window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void GameManager::update(float deltaTime) {

    if (state==GameState::CANNON) {
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition());
        sf::Vector2f cannonPos=paddle.getPosition();

        float dx = mousePosition.x - cannonPos.x;
        float dy = mousePosition.y - cannonPos.y;
        sf::Angle angle = sf::degrees(std::atan2(dy, dx));

        paddle.getShapeNonConst().setRotation(angle);


    }

    if (state==GameState::MENU) {

        if (startButton->isClicked(window)==true) {
            resetGame();
        }
        if (quitButton->isClicked(window)==true) {
            exit(0);
        }
    }


    if (state==GameState::RUNNING) {
        ball.update(deltaTime);
        sf::Vector2f ballPos= ball.getPosition();
        sf::Vector2f ballSize= ball.getSize();
        sf::Vector2f ballCenter(ballPos.x+ballSize.x/2,ballPos.y+ballSize.y/2); //calculate the center of the ball for collision calculations

        livesText->setString("Lives: " + std::to_string(lives));
        // ↓ check if all bricks are destroyed ↓
        if (bricks.empty()) {
            state=GameState::WIN;
        }
        // ↑ check if all bricks are destroyed ↑

        // ↓ pause the game ↓
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            state=GameState::PAUSE;
        }
        // ↑ pause the game

        // ↓ Ball collision ↓
        if (ballPos.x < 0 || ballPos.x +ballSize.x > window.getSize().x) { // if the ball collides with either wall
            ball.bounce(Surface::WALL);
        }

        if (ballPos.y < 0) { //if the ball is on top of the screen
            ball.bounce(Surface::TOP);
        }


        if (ball.isOutOfBounds(window.getSize().y)) {
            if (lives>0) {
                lives -=1;
                livesText->setString("Lives: " + std::to_string(lives));
                state=GameState::PAUSE;
            } else {
                state=GameState::LOSE;
            }
        }

        if (ball.getShape().getGlobalBounds().findIntersection(paddle.getShape().getGlobalBounds())) { //if the ball hits the paddle
            ball.bounce(Surface::PADDLE);
        }

        for (Brick& brick:bricks) {
            sf::Vector2f brickPos = brick.getPosition();
            sf::Vector2f brickSize = brick.getSize();

            sf::Vector2f brickCenter(brickPos.x+brickSize.x/2,brickPos.y+brickSize.y/2); //calculate brick center to see what direction the ball should go after collision

            sf::Vector2f deltaBallPos(ballCenter.x-brickCenter.x, ballCenter.y-brickCenter.y);

            if (ball.getShape().getGlobalBounds().findIntersection(brick.getShape().getGlobalBounds())) {

                float overlapX = (ballSize.x/2 + brickSize.x/2)-abs(deltaBallPos.x);
                float overlapY = (ballSize.y/2 + brickSize.y/2)-abs(deltaBallPos.y);

                if (overlapX < overlapY) {
                    ball.bounce(Surface::WALL); //bounce(WALL) reverses X velocity so it works here even though it's a brick
                }
                else {
                    ball.bounce(Surface::TOP); //bounce(TOP) reverses Y velocity so it's used here even though we're hitting a brick
                }


                brick.getHit();
                score+=1;
                scoreText->setString("Score: " + std::to_string(score));

            }
        }
        // ↑ ball collision ↑

        // ↓ erase bricks ↓
            bricks.erase(
                std::remove_if(bricks.begin(), bricks.end(),
                    [](const Brick& brick)
                    {return brick.isDestroyed();}), //remove_if moves elements to be removed to the end of the vector and returns an iterator to the erase function to start from
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
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) { // if holding any shift the paddle speed will double
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
            state = GameState::MENU;
        }
    // ↑ if player loses ↑

    }

    // ↓ if game is paused ↓
    if (state == GameState::PAUSE) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            unPause();
        }
    }
    // ↑ if game is paused ↑



}

void GameManager::render() {
    window.clear();

    if (state==GameState::CANNON) {
        window.draw(paddle.getShape());
    }

    if (state==GameState::MENU) {
        window.draw(*titleText);
        window.draw(startButton->getShape());
        window.draw(startButton->getText());

        window.draw(quitButton->getShape());
        window.draw(quitButton->getText());
    }
    if (state == GameState::RUNNING) {
        window.draw(ball.getShape());
        window.draw(paddle.getShape());
        window.draw(*scoreText);
        window.draw(*livesText);

        for (const Brick& brick:bricks) {
            window.draw(brick.getShape());
        }
    }

    if (state == GameState::LOSE) {
        window.draw(*loseText);
        scoreText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2));
        window.draw(*scoreText);
        window.draw(*restartText);
    }
    if (state == GameState::WIN) {
        window.draw(*winText);
        window.draw(*restartText);
    }
    if (state==GameState::PAUSE) {

        scoreText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2));
        livesText->setPosition(sf::Vector2f(windowWidth/2,windowHeight/2-30));
        window.draw(*pauseText);
        window.draw(*scoreText);
        window.draw(*livesText);
        window.draw(*restartText);
    }

    window.display();
}

void GameManager::run() {
    while (window.isOpen()) {

        sf::Time deltaTime = clock.restart();
        handleEvents();


        update(deltaTime.asSeconds()); //use deltaTime as seconds because it's a float
        render();

    }
}

void GameManager::initializeBricks(float rowNum, float colNum) {
    for (int row=0;row<rowNum;row++) {
        for (int col=0;col<colNum;col++) {
            float x = 50+col*(100+30); //starting X position + column *(brick width + gap so bricks don't touch)
            float y = 50+row*(50+30); // starting Y position + column * (brick height + gap so bricks don't touch)

            if (x+100>windowWidth) {
                continue;
            }
            int randomHP = hpDistribution(generator);
            bricks.push_back(Brick(x, y,randomHP));
        }
    }
}

void GameManager::resetGame() {
    ball.reset();
    paddle.reset();
    bricks.clear();

    score = 0;
    lives = 3;

    scoreText->setString("Score: " + std::to_string(0));
    scoreText->setPosition(sf::Vector2f(scoreText->getLocalBounds().getCenter().x,scoreText->getLocalBounds().getCenter().y));

    livesText->setString("Lives: " + std::to_string(3));
    livesText->setPosition(sf::Vector2f(windowWidth-livesText->getLocalBounds().getCenter().x,livesText->getLocalBounds().getCenter().y));

    initializeBricks(5,5);
    state=GameState::RUNNING;
}

void GameManager::unPause() {
    ball.reset();
    paddle.reset();
    scoreText->setPosition(sf::Vector2f(scoreText->getLocalBounds().getCenter().x,scoreText->getLocalBounds().getCenter().y));
    livesText->setPosition(sf::Vector2f(windowWidth-livesText->getLocalBounds().getCenter().x,livesText->getLocalBounds().getCenter().y));

    state=GameState::RUNNING;

}

