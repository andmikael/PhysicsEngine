#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    constexpr int32_t width = 1280;
    constexpr int32_t height = 720;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(width, height), "PhysicsEngine", sf::Style::Default, settings);

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    return 0;
}
