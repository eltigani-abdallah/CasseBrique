#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1024u, 768u}), "SFML window");

    printf("Blabla\n");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        // Ici tu peux dessiner des formes, sprites, etc.
        sf::Font font;
        if (!font.openFromFile("asset/font/arial.ttf"))
        {
            std::cerr << "Échec de chargement de la police: asset/font/arial.ttf\n";
            return 1;
        }

        sf::Text playButton(font, "Jouer");
        playButton.setCharacterSize(40);
        playButton.setPosition(playButton.getPosition() + sf::Vector2f{0.f, 200.f});

        sf::Text quitButton(font, "Quitter");
        quitButton.setCharacterSize(40);
        quitButton.setPosition(quitButton.getPosition() + sf::Vector2f{0.f, 300.f});

        window.draw(playButton);
        window.draw(quitButton);
        window.display();
    }
    return 0;
}