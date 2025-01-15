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

    window.setFramerateLimit(60);

    CircleSolver solver;

    Renderer renderer(window);

    sf::Vector2i mousePosition;
    sf::Vector2f coords;

    sf::Clock clock;
    float prev_time = 0.0f;
    float dt = 0.0f;
    bool is_pressed = false;
    int lb = 15;
    int ub = 35;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }/*
            if (event.type == sf::Event::KeyPressed) {
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
            if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                float rad = float(rand() % (ub - lb + 1)) + lb;
                //float rad = 20;
                solver.AddObject(coords, rad);
            }

        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            is_pressed = false;
            //if (event.mouseButton.button == sf::Mouse::Left && is_pressed == true) {
            //    is_pressed = false;
            //}
        }
        renderer.Render(solver);
        window.display();
    }
    return 0;
}
