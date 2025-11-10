#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <sstream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PADDLE_WIDTH = 100.0f;
const float PADDLE_HEIGHT = 20.0f;
const float BALL_RADIUS = 10.0f;
const float PADDLE_SPEED = 400.0f;
const float BALL_SPEED = 300.0f;
const int BRICK_ROWS = 5;
const int BRICK_COLS = 10;
const float BRICK_WIDTH = 75.0f;
const float BRICK_HEIGHT = 30.0f;

class Paddle {
public:
    sf::RectangleShape shape;
    
    Paddle(float x, float y) {
        shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::White);
    }
    
    void move(float dx, float dt) {
        shape.move(dx * dt, 0);
        float x = shape.getPosition().x;
        if (x < 0) shape.setPosition(0, shape.getPosition().y);
        if (x + PADDLE_WIDTH > WINDOW_WIDTH) 
            shape.setPosition(WINDOW_WIDTH - PADDLE_WIDTH, shape.getPosition().y);
    }
    
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

class Ball {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    
    Ball(float x, float y) {
        shape.setRadius(BALL_RADIUS);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Yellow);
        velocity = sf::Vector2f(BALL_SPEED * 0.7f, -BALL_SPEED);
    }
    
    void update(float dt) {
        shape.move(velocity * dt);
        
        // Rebond sur les côtés
        if (shape.getPosition().x <= 0 || 
            shape.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH) {
            velocity.x = -velocity.x;
        }
        
        // Rebond sur le haut
        if (shape.getPosition().y <= 0) {
            velocity.y = -velocity.y;
        }
    }
    
    bool isOutOfBounds() const {
        return shape.getPosition().y > WINDOW_HEIGHT;
    }
    
    void reset(float x, float y) {
        shape.setPosition(x, y);
        velocity = sf::Vector2f(BALL_SPEED * 0.7f, -BALL_SPEED);
    }
    
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

class Brick {
public:
    sf::RectangleShape shape;
    bool destroyed;
    
    Brick(float x, float y, sf::Color color) {
        shape.setSize(sf::Vector2f(BRICK_WIDTH - 2, BRICK_HEIGHT - 2));
        shape.setPosition(x, y);
        shape.setFillColor(color);
        destroyed = false;
    }
    
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Casse-Briques");
    window.setFramerateLimit(60);
    
    // Initialisation
    Paddle paddle(WINDOW_WIDTH / 2 - PADDLE_WIDTH / 2, WINDOW_HEIGHT - 50);
    Ball ball(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2);
    
    // Création des briques
    std::vector<Brick> bricks;
    sf::Color colors[] = {sf::Color::Red, sf::Color::Magenta, sf::Color::Yellow, 
                          sf::Color::Green, sf::Color::Cyan};
    
    for (int row = 0; row < BRICK_ROWS; ++row) {
        for (int col = 0; col < BRICK_COLS; ++col) {
            float x = col * BRICK_WIDTH + 10;
            float y = row * BRICK_HEIGHT + 50;
            bricks.push_back(Brick(x, y, colors[row % 5]));
        }
    }
    
    int score = 0;
    int lives = 3;
    bool gameOver = false;
    bool victory = false;
    
    sf::Font font;
      if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text livesText;
    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(700, 10);

    sf::Text endText;
    endText.setFont(font);
    endText.setCharacterSize(36);
    endText.setFillColor(sf::Color::Yellow);
    endText.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50);

    sf::Clock clock;

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        if (!gameOver && !victory) {
            // Déplacement de la raquette
            float dx = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                dx = -PADDLE_SPEED;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                dx = PADDLE_SPEED;

            paddle.move(dx, dt);
            ball.update(dt);

            // Collision balle / raquette
            if (ball.getBounds().intersects(paddle.getBounds())) {
                ball.velocity.y = -std::abs(ball.velocity.y);
                float overlap = (ball.shape.getPosition().x + BALL_RADIUS) - 
                                (paddle.shape.getPosition().x + PADDLE_WIDTH / 2);
                ball.velocity.x = overlap * 5; // Angle de rebond variable
            }

            // Collision balle / briques
            for (auto& brick : bricks) {
                if (!brick.destroyed && ball.getBounds().intersects(brick.getBounds())) {
                    brick.destroyed = true;
                    score += 10;
                    ball.velocity.y = -ball.velocity.y;
                    break;
                }
            }

            // Supprimer les briques détruites
            bricks.erase(std::remove_if(bricks.begin(), bricks.end(),
                                        [](const Brick& b){ return b.destroyed; }),
                         bricks.end());

            // Vérifier la victoire
            if (bricks.empty()) {
                victory = true;
            }

            // Vérifier la perte de la balle
            if (ball.isOutOfBounds()) {
                lives--;
                if (lives <= 0) {
                    gameOver = true;
                } else {
                    ball.reset(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2);
                }
            }

            // Mettre à jour le texte
            std::ostringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

            std::ostringstream ss2;
            ss2 << "Vies: " << lives;
            livesText.setString(ss2.str());
        }

        // Rendu
        window.clear();

        window.draw(paddle.shape);
        window.draw(ball.shape);
        for (auto& brick : bricks) {
            if (!brick.destroyed)
                window.draw(brick.shape);
        }

        window.draw(scoreText);
        window.draw(livesText);

        if (gameOver) {
            endText.setString("GAME OVER !");
            window.draw(endText);
        } else if (victory) {
            endText.setString("VICTOIRE !");
            window.draw(endText);
        }

        window.display();
    }

    return 0;
}
