#pragma once
#ifndef CIRCLESOLVER_H
#define CIRCLESOLVER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

const float GRAVITY = 1000.0f;

struct AABB {
    sf::Vector2f min;
    sf::Vector2f max;
};

struct CircleObject {
    sf::Vector2f position;
    sf::Vector2f lastPosiiton;
    sf::Vector2f acceleration;
    float radius = 20.0f;
    sf::Color color = sf::Color::White;
    float timeAlive = 0.0f;
    bool on_ground = false;

    CircleObject(sf::Vector2f position_, float radius_)
        : position{position_}
        , lastPosiiton{position_}
        , acceleration{sf::Vector2f{50.0f, GRAVITY}}
        , radius{radius_}
    {}
};

class CircleSolver
{
public:
    CircleSolver();
    void AddObject(sf::Vector2f position, float radius);
    void Update(float seconds);
    void CheckConstraint(std::unique_ptr<CircleObject>& obj);
    void CheckObjectCollision();
    void updatePosition(std::unique_ptr<CircleObject>& obj, float dt);
    void addAcceleration(std::unique_ptr<CircleObject>& obj);
    void addAge(std::unique_ptr<CircleObject>& obj, float dt);

    std::vector<std::unique_ptr<CircleObject>> objects;
};

#endif // CIRCLESOLVER_H
