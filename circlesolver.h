#pragma once
#ifndef CIRCLESOLVER_H
#define CIRCLESOLVER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

struct CircleObject {
    sf::Vector2f position;
    sf::Vector2f lastPosiiton;
    sf::Vector2f acceleration;
    float radius = 10.0f;
    sf::Color color = sf::Color::White;

    CircleObject(sf::Vector2f position_)
        : position{position_}
    {}
};

class CircleSolver
{
public:
    CircleSolver();
    void AddObject(sf::Vector2f position);
    void Update();
    std::vector<CircleObject> GetObjects();
    void Clear();

private:
    std::vector<CircleObject> objects;
};

#endif // CIRCLESOLVER_H
