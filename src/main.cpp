#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include "circlesolver.h"
#include "renderer.h"
#include "constants.h"
#include <cstdlib>
#include "imgui.h"
#include "imgui-SFML.h"
#include "segment.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsEngine", sf::Style::Default, settings);
    window.setFramerateLimit(FRAMERATE);
    bool success = false;
    success = ImGui::SFML::Init(window);
    sf::Clock deltaClock;

    CircleSolver solver;
    SegmentSolver segmentsolver;
    Renderer renderer(window);
    std::vector<CircleCollider *> circleColliders = std::vector<CircleCollider *>();

    sf::Vector2i mousePosition;
    sf::Vector2f coords;

    bool is_pressed = false;
    bool ball_simulation = false;
    bool circle_simulation = true;
    bool cloth_simulation = true;

    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // variables for creating verlet objects of random size
    int lb_rad = 15;
    int ub_rad = 35;
    int lb_color = 20;
    int ub_color = 200;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("controls", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);
        if(ImGui::Button("reset simulation")) {
            if (ball_simulation) {
                solver.deleteObjects();
                for (auto collider : circleColliders) {
                    delete collider;
                }
                circleColliders.clear();
            } else if (cloth_simulation) {
                segmentsolver.ClearRope();
            }
        }

        if (ImGui::Button("cloth simulation") && !cloth_simulation) {
            cloth_simulation = true;
            solver.deleteObjects();
            if (ball_simulation) {
                ball_simulation = false;
            }
        }

        if (ImGui::Button("ball simulation") && !ball_simulation) {
            ball_simulation = true;
            if (cloth_simulation) {
                cloth_simulation = false;
            }
        }
        float x = ImGui::GetCursorPosX();
        float y = ImGui::GetCursorPosY();
        if (ball_simulation) {
            ImGui::SetCursorPos(ImVec2(x+40.0f, y));
            ImGui::Button("circle colliders");
            x = ImGui::GetCursorPosX();
            y = ImGui::GetCursorPosY();
            ImGui::SetCursorPos(ImVec2(x+40.0f, y));
            ImGui::Button("Hollow circle");
        }

        ImGui::End();
        window.clear();

        if (ball_simulation) {
            solver.Update();
            for (auto collider : circleColliders) {
                solver.CheckColliderConstraint(collider);
            }
        } else if (cloth_simulation) {
            segmentsolver.UpdateRope();
            segmentsolver.ApplyLinks();
        }

        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (!is_pressed) {
                is_pressed = true;
                if (ball_simulation) {
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                float rad = float(rand() % (ub_rad - lb_rad + 1)) + lb_rad;
                sf::Color color((rand() % 255), (rand() % 255), (rand() % 255), 255);
                solver.AddObject(coords, rad, color);
                } else if (cloth_simulation) {
                    mousePosition = sf::Mouse::getPosition(window);
                    coords.x = (float)mousePosition.x;
                    coords.y = (float)mousePosition.y;
                    segmentsolver.SpawnStructureCloth(coords, 20, 12, 0, sf::Color::White);
                    /*if (!segmentsolver.GetRopeState()) {
                        segmentsolver.SpawnStructureRope(coords, 20, 25, 8, FIRST, sf::Color(255,255,255,255));
                    } else {
                        segmentsolver.ClearRope();
                        segmentsolver.SpawnStructureRope(coords, 20, 25, 8, FIRST, sf::Color(255,255,255,255));
                    }*/
                }
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
            }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            is_pressed = false;
        }
        if (ball_simulation) {
            renderer.Render(solver);
            for (const auto collider : circleColliders) {
                collider->draw(&window);
            }
        } else if (cloth_simulation) {
            segmentsolver.Draw(window);            
        }

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
