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

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "window", sf::Style::Default, settings);
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
    bool ball_simulation = true;
    bool circle_simulation = true;
    bool cloth_simulation = false;
    bool rope_simulation = false;

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
            } else if (cloth_simulation || rope_simulation) {
                segmentsolver.ClearRope();
            }
        }

        if (ImGui::Button("cloth simulation")) {
            cloth_simulation = true;
            if (ball_simulation) {
                solver.deleteObjects();
                ball_simulation = false;
            }
            if (rope_simulation) {
                segmentsolver.ClearRope();
            }
        }

        if (ImGui::Button("rope simulation")) {
            rope_simulation = true;
            if (ball_simulation) {
                solver.deleteObjects();
                ball_simulation = false;
            }
            if (cloth_simulation) {
                cloth_simulation = false;
                segmentsolver.ClearRope();
            }
        }

        if (ImGui::Button("ball simulation")) {
            ball_simulation = true;
            if (cloth_simulation) {
                cloth_simulation = false;
            }
            if (rope_simulation) {
                rope_simulation = false;
            }
            segmentsolver.ClearRope();
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
        } else if (cloth_simulation || rope_simulation) {
            segmentsolver.UpdateRope();
            segmentsolver.ApplyLinks();
        }
        auto min = ImGui::GetWindowContentRegionMin();
        auto max = ImGui::GetWindowContentRegionMax();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (io.WantCaptureMouse) {
                // main window will not take input when
                // pressing settings window
            } else if (!is_pressed) {
                is_pressed = true;
                mousePosition = sf::Mouse::getPosition(window);
                coords.x = (float)mousePosition.x;
                coords.y = (float)mousePosition.y;
                if (ball_simulation) {
                    float rad = float(rand() % (ub_rad - lb_rad + 1)) + lb_rad;
                    sf::Color color((rand() % 255), (rand() % 255), (rand() % 255), 255);
                    solver.AddObject(coords, rad, color);
                } else if (cloth_simulation) {
                    if (segmentsolver.GetRopeState()) {
                        segmentsolver.ClearRope();
                    }
                    segmentsolver.SpawnStructureCloth(coords, 20, 12, 0, sf::Color::White);
                    
                } else if (rope_simulation) {
                    if (segmentsolver.GetRopeState()) {
                        segmentsolver.ClearRope();
                    }
                    segmentsolver.SpawnStructureRope(coords, 20, 25, 8, FIRST, sf::Color::White);
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
        }
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            is_pressed = false;
        }
        if (ball_simulation) {
            renderer.Render(solver);
            for (const auto collider : circleColliders) {
                collider->draw(&window);
            }
        } else {
            segmentsolver.Draw(window);            
        }

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
