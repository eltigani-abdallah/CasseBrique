#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <optional>

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1024u, 768u}), "SFML window");

    printf("Blabla\n");
    while (window.isOpen())
    {
        printf("Bonjour\n");
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        // Ici tu peux dessiner des formes, sprites, etc.
        window.display();
    }
    return 0;
}