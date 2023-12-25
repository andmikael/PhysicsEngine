#pragma once
#ifndef CIRCLESOLVER_H
#define CIRCLESOLVER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

const float GRAVITY = 9.81f;
const float AIR_FRICTION = 0.5f;

struct AABB {
    sf::Vector2f min;
    sf::Vector2f max;
};

struct CircleObject {
    sf::Vector2f position;
    sf::Vector2f lastPosiiton;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    float radius = 20.0f;
    sf::Color color = sf::Color::White;
    float timeAlive = 0.0f;

    CircleObject(sf::Vector2f position_)
        : position{position_}
        , lastPosiiton{position_}
        , acceleration{sf::Vector2f{0.0f, 0.0f}}
        , velocity{sf::Vector2f{0.0f, 0.0f}}
    {}
};

class CircleSolver
{
public:
    CircleSolver();
    void AddObject(sf::Vector2f position);
    void Update(float seconds);
    void CheckBorderCollision(std::unique_ptr<CircleObject>& obj);
    void check(float seconds);
    void updatePosition(std::unique_ptr<CircleObject>& obj, float dt);
    void addAcceleration(std::unique_ptr<CircleObject>& obj);
    void addAge(std::unique_ptr<CircleObject>& obj, float dt);

    std::vector<std::unique_ptr<CircleObject>> objects;
};

#endif // CIRCLESOLVER_H
