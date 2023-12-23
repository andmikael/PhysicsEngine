#include "circlesolver.h"
#include <iostream>

CircleSolver::CircleSolver()
{
    objects = std::vector<CircleObject>();
}

void CircleSolver::AddObject(sf::Vector2f position) {
    objects.push_back(CircleObject(position));
}

void CircleSolver::Update(float seconds) {
    for (auto& obj : objects) {
        if (obj.timeAlive == 0.0f) {
            obj.timeAlive = seconds;
        }
        computeForce(obj);
        obj.velocity.y += obj.acceleration.y * seconds;
        obj.position.y += obj.velocity.y;
        CheckBorderCollision(obj);
    }
}

std::vector<CircleObject> CircleSolver::GetObjects() {
    return objects;
}

void CircleSolver::Clear() {
    objects.clear();
}

void CircleSolver::computeForce(CircleObject& obj) {
    if (obj.Force == sf::Vector2f{0.0f, 0.0f}) {
        // free falling object
        obj.Force.y = obj.acceleration.y * obj.weight;
        obj.acceleration.y = GRAVITY * obj.weight;
    }
}

void CircleSolver::CheckBorderCollision(CircleObject& obj) {
    if (obj.position.y >= 700) {
        obj.velocity.y -= 0.75f;
        obj.velocity.y *= -1.0f;
    }

    if (obj.position.y <= 0) {
        obj.velocity.y *= -1.0f;
    }
}
