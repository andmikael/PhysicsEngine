#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "circlesolver.h"
#include "renderer.h"
#include "constants.h"
#include "circlecollider.h"
#include <cstdlib>

using namespace std;

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsEngine", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    CircleSolver solver;
    Renderer renderer(window);
    std::vector<CircleCollider *> circleColliders = std::vector<CircleCollider *>();

    sf::Vector2i mousePosition;
    sf::Vector2f coords;

    bool is_pressed = false;

    // variables for creating verlet objects of random size
    int lb = 15;
    int ub = 35;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        solver.Update();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                //float rad = float(rand() % (ub - lb + 1)) + lb;
                solver.AddObject(coords, 20);
            }

        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                CircleCollider* circleCollider = new CircleCollider(coords, 300.0f, 1.0f, true, true, 128);
                circleColliders.push_back(circleCollider);
            }
        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            is_pressed = false;
        }
        renderer.Render(solver);
        for (const auto collider : circleColliders) {
            collider->draw(&window);
        }
        window.display();
    }
    return 0;
}
