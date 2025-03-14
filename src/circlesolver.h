#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <math.h>
#include <memory>
#include "constants.h"
#include "time.h"
#include "circlecollider.h"

// forward declaration to avoid circular dependencies
class CircleCollider;

struct AABB {
    sf::Vector2f min;
    sf::Vector2f max;
};

struct CircleObject {

    sf::Vector2f position;
    sf::Vector2f lastPosition;
    sf::Vector2f acceleration;
    sf::Vector2f velocity;

    float start_time;
    float radius;

    bool isStatic;
    bool isColliding;

    sf::Color color;

    CircleObject(sf::Vector2f position_, float radius_, sf::Color color_)
        : position{position_}
        , lastPosition{position_}
        , acceleration{sf::Vector2f(GRAVITY)}
        , radius{radius_}
        , start_time{Time::getTime()}
        , color{color_}
    {}
};

class CircleSolver
{
public:
    void AddObject(sf::Vector2f position, float radius, sf::Color color);
    void Update();
    void CheckColliderConstraint(CircleCollider * collider);
    void CheckConstraint(CircleObject* circleObject);
    void CheckObjectCollision();
    sf::Vector2f calculateVelocity(CircleObject* circleObject);
    sf::Vector2f calculateDisplacement(CircleObject* circleObject, float dt);
    void updatePosition(CircleObject* circleObject);
    void addAcceleration(CircleObject* circleObject, sf::Vector2f acceleration);
    void applyBorders(CircleObject* obj);
    void solveCollision(CircleObject* obj1, CircleObject* obj2);
    void deleteObjects();
    void Attract(sf::Vector2f pos);

    std::vector<CircleObject *> objects = std::vector<CircleObject *>();
    sf::RectangleShape rectangle;
};
