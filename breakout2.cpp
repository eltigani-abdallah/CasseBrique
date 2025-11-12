#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <cstdlib>

const int WINDOW_WIDTH = 1010;
const int WINDOW_HEIGHT = 505;
const float PADDLE_WIDTH = 100.0f;
const float PADDLE_HEIGHT = 20.0f;
const float BALL_RADIUS = 10.0f;
const float PADDLE_SPEED = 400.0f;
const float BALL_SPEED = 300.0f;
const int BRICK_ROWS = 5;
const int BRICK_COLS = 10;
const float BRICK_WIDTH = 150.0f;
const float BRICK_HEIGHT = 60.0f;

class Paddle {
public:
    sf::RectangleShape shape;
    Paddle(float x, float y) {
        shape.setSize(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
        shape.setPosition(x, y);
    }
    void move(float dx, float dt) {
        shape.move(dx * dt, 0);
        float x = shape.getPosition().x;
        if (x < 0) shape.setPosition(0, shape.getPosition().y);
        if (x + PADDLE_WIDTH > WINDOW_WIDTH)
            shape.setPosition(WINDOW_WIDTH - PADDLE_WIDTH, shape.getPosition().y);
    }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
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
        if (shape.getPosition().x <= 0 || shape.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH)
            velocity.x = -velocity.x;
        if (shape.getPosition().y <= 0)
            velocity.y = -velocity.y;
    }
    bool isOutOfBounds() const { return shape.getPosition().y > WINDOW_HEIGHT; }
    void reset(float x, float y) {
        shape.setPosition(x, y);
        velocity = sf::Vector2f(BALL_SPEED * 0.7f, -BALL_SPEED);
    }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

class Brick {
public:
    sf::RectangleShape shape;
    bool destroyed = false;
    Brick(float x, float y) { shape.setSize(sf::Vector2f(BRICK_WIDTH, BRICK_HEIGHT)); shape.setPosition(x, y); }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }
};

// Particule pour effet destruction
struct Particle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float lifetime;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Casse-Briques Deluxe");
    window.setFramerateLimit(60);

    // Création raquette et balle
    Paddle paddle(WINDOW_WIDTH/2 - PADDLE_WIDTH/2, WINDOW_HEIGHT-50);
    Ball ball(WINDOW_WIDTH/2 - BALL_RADIUS, WINDOW_HEIGHT/2);

    // Charger textures
    sf::Texture brickTex, paddleTex, bgTex;
    if (!brickTex.loadFromFile("assets/images/brick_texture.png")) return -1;
    if (!paddleTex.loadFromFile("assets/images/paddle_texture.png")) return -1;
    if (!bgTex.loadFromFile("assets/images/background.jpg")) return -1;
    sf::Sprite background(bgTex);

    paddle.shape.setTexture(&paddleTex);
    paddle.shape.setScale(PADDLE_WIDTH / paddleTex.getSize().x, PADDLE_HEIGHT / paddleTex.getSize().y);

    // Créer briques
    std::vector<Brick> bricks;
    for (int r=0;r<BRICK_ROWS;++r)
        for (int c=0;c<BRICK_COLS;++c){
            Brick b(c*BRICK_WIDTH+10, r*BRICK_HEIGHT+50);
            b.shape.setTexture(&brickTex);
            b.shape.setScale(BRICK_WIDTH/brickTex.getSize().x, BRICK_HEIGHT/brickTex.getSize().y);
            bricks.push_back(b);
        }

    // Sons
    sf::SoundBuffer bounceBuf, brickBuf, loseBuf;
    bounceBuf.loadFromFile("assets/sounds/bounce.wav");
    brickBuf.loadFromFile("assets/sounds/brick.wav");
    loseBuf.loadFromFile("assets/sounds/lose.wav");
    sf::Sound bounceSound(bounceBuf), brickSound(brickBuf), loseSound(loseBuf);

    // Texte
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/arial.ttf")) return -1;
    sf::Text scoreText("", font, 20); scoreText.setPosition(10,10);
    sf::Text livesText("", font, 20); livesText.setPosition(700,10);
    sf::Text messageText("", font, 36); messageText.setPosition(WINDOW_WIDTH/2-150,WINDOW_HEIGHT/2-50);

    int score=0, lives=3;
    bool gameOver=false, victory=false;
    sf::Clock clock;
    std::vector<Particle> particles;

    auto resetGame = [&](){
        score=0; lives=3; gameOver=false; victory=false;
        ball.reset(WINDOW_WIDTH/2 - BALL_RADIUS, WINDOW_HEIGHT/2);
        paddle.shape.setPosition(WINDOW_WIDTH/2 - PADDLE_WIDTH/2, WINDOW_HEIGHT-50);
        bricks.clear();
        for (int r=0;r<BRICK_ROWS;++r)
            for (int c=0;c<BRICK_COLS;++c){
                Brick b(c*BRICK_WIDTH+10, r*BRICK_HEIGHT+50);
                b.shape.setTexture(&brickTex);
                b.shape.setScale(BRICK_WIDTH/brickTex.getSize().x, BRICK_HEIGHT/brickTex.getSize().y);
                bricks.push_back(b);
            }
    };

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type==sf::Event::Closed) window.close();

        float dt = clock.restart().asSeconds();

        if(!gameOver && !victory){
            float dx=0;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) dx=-PADDLE_SPEED;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dx=PADDLE_SPEED;
            paddle.move(dx, dt);
            ball.update(dt);

            // Rebond raquette
            if(ball.getBounds().intersects(paddle.getBounds())){
                bounceSound.play();
                float diff = (ball.shape.getPosition().x+BALL_RADIUS - (paddle.shape.getPosition().x+PADDLE_WIDTH/2)) / (PADDLE_WIDTH/2);
                ball.velocity.x = diff * BALL_SPEED;
                ball.velocity.y = -std::abs(ball.velocity.y);
            }

            // Collision briques
            for(auto& b: bricks){
                if(!b.destroyed && ball.getBounds().intersects(b.getBounds())){
                    brickSound.play();
                    b.destroyed=true; score+=10;
                    ball.velocity.y = -ball.velocity.y;
                    // Particules
                    for(int i=0;i<10;++i){
                        Particle p; p.shape.setRadius(2); p.shape.setPosition(b.shape.getPosition());
                        p.shape.setFillColor(sf::Color::White);
                        p.velocity = sf::Vector2f((rand()%200-100)/100.f,(rand()%200-100)/100.f);
                        p.lifetime = 0.5f+(rand()%100)/100.f;
                        particles.push_back(p);
                    }
                    break;
                }
            }
            bricks.erase(std::remove_if(bricks.begin(),bricks.end(),[](Brick& b){return b.destroyed;}),bricks.end());

            if(bricks.empty()) victory=true;
            if(ball.isOutOfBounds()){
                lives--; loseSound.play();
                if(lives<=0) gameOver=true;
                else ball.reset(WINDOW_WIDTH/2-BALL_RADIUS, WINDOW_HEIGHT/2);
            }

            std::ostringstream ss; ss<<"Score: "<<score; scoreText.setString(ss.str());
            std::ostringstream ss2; ss2<<"Vies: "<<lives; livesText.setString(ss2.str());
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
            resetGame();
        }

        // Particules
        for(auto& p: particles){
            p.shape.move(p.velocity*200.f*dt);
            p.lifetime-=dt;
            sf::Color c=p.shape.getFillColor();
            c.a=static_cast<sf::Uint8>(255*std::max(p.lifetime,0.f));
            p.shape.setFillColor(c);
        }
        particles.erase(std::remove_if(particles.begin(),particles.end(),[](Particle& p){return p.lifetime<=0;}),particles.end());

        // Rendu
        window.clear();
        window.draw(background);
        window.draw(paddle.shape);
        window.draw(ball.shape);
        for(auto& b: bricks) if(!b.destroyed) window.draw(b.shape);
        for(auto& p: particles) window.draw(p.shape);
        window.draw(scoreText); window.draw(livesText);

        if(gameOver){ messageText.setString("GAME OVER\nAppuyez sur R pour rejouer"); window.draw(messageText);}
        else if(victory){ messageText.setString("VICTOIRE !\nAppuyez sur R pour rejouer"); window.draw(messageText);}

        window.display();
    }

    return 0;
}
