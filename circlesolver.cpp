#include "circlesolver.h"

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
        obj.lastPosiiton = obj.position;
        obj.position.x += obj.velocity.x;
        float currentTime = seconds - obj.timeAlive;
        sf::Vector2f velocity = obj.acceleration * currentTime;
        obj.position += velocity;
    }
}

std::vector<CircleObject> CircleSolver::GetObjects() {
    return objects;
}

void CircleSolver::Clear() {
    objects.clear();
}
