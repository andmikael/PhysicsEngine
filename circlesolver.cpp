#include "circlesolver.h"

CircleSolver::CircleSolver()
{
    objects = std::vector<CircleObject>();
}

void CircleSolver::AddObject(sf::Vector2f position) {
    objects.push_back(CircleObject(position));
}

std::vector<CircleObject> CircleSolver::GetObjects() {
    return objects;
}

void CircleSolver::Clear() {
    objects.clear();
}
