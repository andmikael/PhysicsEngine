#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <circlesolver.h>
#include <renderer.h>

using namespace std;

int main()
{
    constexpr int32_t width = 1280;
    constexpr int32_t height = 720;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(width, height), "PhysicsEngine", sf::Style::Default, settings);

    window.setFramerateLimit(144);

    CircleSolver solver;

    Renderer renderer(window);

    sf::Vector2i mousePosition;
    sf::Vector2f coords;

    sf::Clock clock;
    float prev_time = 0.0f;
    float dt = 0.0f;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            /*if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scan::R) {
                    solver.Clear();
                    window.clear();
                }
            }*/
        }

        sf::Time time = clock.getElapsedTime();
        float seconds = time.asSeconds();
        if (prev_time == 0.0f) {
            prev_time = seconds;
        }
        dt = seconds - prev_time;
        prev_time = seconds;
        window.clear();
        solver.Update(dt);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePosition = sf::Mouse::getPosition(window);
            coords.x = (float)mousePosition.x;
            coords.y = (float)mousePosition.y;
            std::cout << "X: " << coords.x << ", Y: " << coords.y << std::endl;
            solver.AddObject(coords);

        }
        renderer.Render(solver);
        window.display();
    }
    return 0;
}
