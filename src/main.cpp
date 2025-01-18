#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "circlesolver.h"
#include "renderer.h"
#include "constants.h"
#include <cstdlib>

using namespace std;

int main()
{

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsEngine", sf::Style::Default, settings);
    window.setFramerateLimit(FRAMERATE);

    CircleSolver solver;
    Renderer renderer(window);
    std::vector<CircleCollider *> circleColliders = std::vector<CircleCollider *>();

    sf::Vector2i mousePosition;
    sf::Vector2f coords;

    bool is_pressed = false;

    // variables for creating verlet objects of random size
    int lb_rad = 15;
    int ub_rad = 35;
    int lb_color = 20;
    int ub_color = 200;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        solver.Update();
        for (auto collider : circleColliders) {
            solver.CheckColliderConstraint(collider);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                float rad = float(rand() % (ub_rad - lb_rad + 1)) + lb_rad;
                sf::Color color((rand() % 255), (rand() % 255), (rand() % 255), 255);
                solver.AddObject(coords, rad, color);
            }

        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                CircleCollider* circleCollider = new CircleCollider(coords, 200.0f, 2.5f, true, true, 128);
                circleColliders.push_back(circleCollider);
            }
        } else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
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
