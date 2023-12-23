#pragma once
#ifndef CIRCLESOLVER_H
#define CIRCLESOLVER_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>

const float GRAVITY = 9.81f;
const float AIR_FRICTION = 0.5f;

struct CircleObject {
    sf::Vector2f position;
    sf::Vector2f lastPosiiton;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;
    float radius = 10.0f;
    sf::Color color = sf::Color::White;
    float weight = 1.0f;
    float timeAlive = 0.0f;
    float inertia = 0.5*weight*pow(radius, 2);
    float angle;
    float angularVelocity;
    sf::Vector2f Force;
    float torque;

    CircleObject(sf::Vector2f position_)
        : position{position_}
        , acceleration{sf::Vector2f{0.0f, 0.0f}}
        , Force{sf::Vector2{0.0f, 0.0f}}
        , velocity{sf::Vector2f{0.0f, 1.0f}}
        , angle{0.0f}
        , angularVelocity{0.0f}

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
    void computeForce(CircleObject& obj);
    void CheckBorderCollision(CircleObject& obj);

private:
    std::vector<CircleObject> objects;
};

#endif // CIRCLESOLVER_H
