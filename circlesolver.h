#pragma once
#ifndef CIRCLESOLVER_H
#define CIRCLESOLVER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

struct CircleObject {
    sf::Vector2f position;
    sf::Vector2f lastPosiiton;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    float radius = 10.0f;
    sf::Color color = sf::Color::White;
    float weight = 1.0f;
    float timeAlive = 0.0f;

    CircleObject(sf::Vector2f position_)
        : position{position_}
        , acceleration{sf::Vector2f{0.0f, 9.81f}}
        , velocity{sf::Vector2f{0.0f, 1.0f}}
    {}
};

class CircleSolver
{
public:
    CircleSolver();
    void AddObject(sf::Vector2f position);
    void Update(float seconds);
    std::vector<CircleObject> GetObjects();
    void Clear();

private:
    std::vector<CircleObject> objects;
};

#endif // CIRCLESOLVER_H
