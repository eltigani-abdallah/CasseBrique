#ifndef CASSEBRIQUE_GAMEMANAGER_H
#define CASSEBRIQUE_GAMEMANAGER_H
#include "./Paddle.h"
#include "./Ball.h"
#include "./Brick.h"
#include "./GameState.h"
#include <vector>
#include <SFML/System/Clock.hpp>
#include <algorithm>

/**
 * Game Manager, takes care of physics, drawing, winning, losing, everything
 */
class GameManager {
public:
    /**
     * constructor for the GameManager, takes care of everything needed to play the game
     * @param windowWidth width of the game window
     * @param windowHeight height of the game window
     * @param state GameState enum (RUNNING, WIN, LOSE) for testing purposes. to be removed later
     */
    GameManager(unsigned int windowWidth, unsigned int windowHeight, GameState state);

    /**
     * start the game. simple as that.
     */
    void run();

    /**
     * handle window closing event
     */
    void handleEvents();

    /**
     * handles all the physics of the ball movement and paddle movement, including events when the player wins or loses
     * @param deltaTime game framerate, handled in run(); as an sf::Time object
     */
    void update(float deltaTime);

    /**
     * draw everything on the screen
     */
    void render();

    /**
     * initialize a brick formation for gameplay
     * @param rowNum number of rows
     * @param colNum number of columns
     */
    void initializeBricks(float rowNum, float colNum);

    /**
     * resets all game objects to starting positions and changes the state to RUNNING
     */
    void resetGame();


private:
    sf::RenderWindow window;
    sf::Clock clock;
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;

    //GameState is an enum that contains the following values: (RUNNING, WIN, LOSE)
    GameState state;

    sf::Font font;
    //text to display when player wins, std::optional because sf::Text must be initialized before the constructor, which is impossible since font is loaded in the constructor
    std::optional<sf::Text> winText;
    //text to display when player loses
    std::optional<sf::Text> loseText;
    //text to explain how to restart game
    std::optional<sf::Text> restartText;

};


#endif //CASSEBRIQUE_GAMEMANAGER_H