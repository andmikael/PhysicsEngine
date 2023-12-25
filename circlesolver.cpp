#include "circlesolver.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>
#include <cstdlib>

CircleSolver::CircleSolver()
{
    objects = std::vector<std::unique_ptr<CircleObject>>();
}

void CircleSolver::AddObject(sf::Vector2f position) {
    objects.push_back(std::make_unique<CircleObject>(position));
}

void CircleSolver::Update(float seconds) {
    check(seconds);
    uint64_t objects_size = objects.size();
    int lb = 8, ub = 40;
    for (uint64_t i{0}; i < objects_size; i++ ) {
        float r = (float)((rand() % (ub-lb+1)) +lb);
        if (objects[i]->timeAlive > r) {
            objects.erase(objects.begin() + i);
            objects_size = objects.size();
            i--;
        }
    }

    const uint64_t objects_size2 = objects.size();
    for (uint64_t i{0}; i < objects_size2; i++ ) {
        CheckBorderCollision(objects[i]);
        updatePosition(objects[i], seconds);
        addAcceleration(objects[i]);
        addAge(objects[i], seconds);
    }
}

void CircleSolver::CheckBorderCollision(std::unique_ptr<CircleObject>& obj) {
    if (obj->position.x <= 0) {
        obj->position.x = 0;
        obj->acceleration.x = 1000.0f;
    }

    if (obj->position.x >= 1280 - (obj->radius + obj->radius)) {
        obj->position.x = 1280 - (obj->radius + obj->radius);
        obj->acceleration.x = -1000.0f;
    }

    if (obj->position.y <= 0) {
        obj->position.y = 0;
        obj->acceleration.y = 1000.0f;
    }

    if (obj->position.y >= 720 - (obj->radius + obj->radius)) {
        obj->position.y = 720 - (obj->radius + obj->radius);
        obj->acceleration.y = -1000.0f;
    }
}

void CircleSolver::check(float dt) {
    const float response_coeff = 0.75f;
    const uint64_t objects_count = objects.size();
    for (uint64_t i{0}; i<objects_count; i++) {
        std::unique_ptr<CircleObject>& obj1 = objects[i];
        for (uint64_t k{i+1}; k < objects_count; k++) {
            std::unique_ptr<CircleObject>& obj2 = objects[k];
            const sf::Vector2f v = obj1->position - obj2->position;
            const float dist2 = v.x * v.x + v.y * v.y;
            const float min_dist = obj1->radius + obj2->radius;

            if (dist2 < min_dist * min_dist) {
                const float dist = sqrt(dist2);
                const sf::Vector2f n = v / dist;
                const float obj1_mass_ratio = obj1->radius / (obj1->radius + obj2->radius);
                const float obj2_mass_ratio  = obj2->radius / (obj1->radius + obj2->radius);
                const float delta = 0.5f * response_coeff *(dist - min_dist);

                obj1->position -= n * (obj2_mass_ratio * delta);
                obj2->position += n * (obj1_mass_ratio * delta);
            }
        }
    }
}

void CircleSolver::updatePosition(std::unique_ptr<CircleObject>& obj, float dt) {
    const sf::Vector2f velocity = obj->position - obj->lastPosiiton;
    obj->lastPosiiton = obj->position;
    obj->position = obj->position + velocity + obj->acceleration * dt * dt;
    obj->acceleration = {0.0f, 0.0f};
}

void CircleSolver::addAcceleration(std::unique_ptr<CircleObject>& obj) {
    obj->acceleration.y += 300.0f;
}

void CircleSolver::addAge(std::unique_ptr<CircleObject>& obj, float dt) {
    obj->timeAlive += dt;
}
