#include "circlesolver.h"
#include <iostream>
#include <memory>
#include <constants.h>
#include <SFML/Window.hpp>

CircleSolver::CircleSolver()
{
    objects = std::vector<std::unique_ptr<CircleObject>>();
}

void CircleSolver::AddObject(sf::Vector2f position, float radius) {
    objects.push_back(std::make_unique<CircleObject>(position, radius));
}

void CircleSolver::Update(float seconds) {
    /*uint64_t objects_size = objects.size();

    // randomized lifetime for objects before they are destroyed
    int lb = 8, ub = 40;
    for (uint64_t i{0}; i < objects_size; i++ ) {
        float r = (float)((rand() % (ub-lb+1)) +lb);
        if (objects[i]->timeAlive > r) {
            objects.erase(objects.begin() + i);
            objects_size = objects.size();
            i--;
        }
    }*/

    CheckObjectCollision();

    const uint64_t objects_size2 = objects.size();
    for (uint64_t i{0}; i < objects_size2; i++ ) {
        updatePosition(objects[i], seconds);
        CheckConstraint(objects[i]);
        addAcceleration(objects[i]);
        addAge(objects[i], seconds);
    }
}

void CircleSolver::CheckConstraint(std::unique_ptr<CircleObject>& obj) {

    if (obj->position.y + obj->radius >= window_height - obj->radius || obj->position.y + obj->radius <= 0) {
        float dist = abs(obj->position.y - obj->lastPosiiton.y);
        float cached_pos_y = obj->position.y;
        obj->position.y = obj->lastPosiiton.y;
        obj->lastPosiiton.y = cached_pos_y;

        // reduce the distance between objects current and last position when it hits a top or bottom border
        // so that objects would "lose energy" and slow down after each bounce
        if (obj->lastPosiiton.y < 0) {
            obj->lastPosiiton.y = obj->lastPosiiton.y + 0.5 * dist;
        } else {
            obj->lastPosiiton.y = obj->lastPosiiton.y - 0.5 * dist;
        }
    }

    if (obj->position.x >= (1200 + obj->radius)) {
        float cached_pos_x = obj->position.x;
        obj->position.x = obj->lastPosiiton.x;
        obj->lastPosiiton.x = cached_pos_x;

    } else if (obj->position.x <= (0 + obj->radius)) {
        float cached_pos_x = obj->position.x;
        obj->position.x = obj->lastPosiiton.x;
        obj->lastPosiiton.x = cached_pos_x;
    }
}

void CircleSolver::CheckObjectCollision() {
    const float response_coeff = 0.75f;
    const uint64_t objects_count = objects.size();
    for (uint64_t i{0}; i<objects_count; i++) {
        std::unique_ptr<CircleObject>& obj1 = objects[i];
        for (uint64_t k{i+1}; k < objects_count; k++) {
            std::unique_ptr<CircleObject>& obj2 = objects[k];

            // calculate the position difference of two object
            const sf::Vector2f v = obj1->position - obj2->position;

            //const float dist2 = v.x * v.x + v.y * v.y;

            // calculate the distance between two points
            const float dist2 = sqrt(v.x * v.x + v.y * v.y);
            // the minimum distance before the two objects touch each other
            const float min_dist = obj1->radius + obj2->radius;

            // check if two objects are touching each other
            if (dist2 < min_dist) {
                const sf::Vector2f n = v / dist2;
                const float obj1_mass_ratio = obj1->radius / (obj1->radius + obj2->radius);
                const float obj2_mass_ratio  = obj2->radius / (obj1->radius + obj2->radius);
                const float delta = 0.5f * response_coeff *(dist2 - min_dist);

                // elastic collition between object 1 and object 2
                // conditional statement is to make sure that objects don't phase through bottom border when two objects
                // collide vertically


                // check if displacement would place obj1 through the floor
                if (obj1->position.y + obj1->radius - n.y * (obj2_mass_ratio * delta) >= window_height) {
                    sf::Vector2f temp = n * (obj2_mass_ratio * delta);
                    temp.y = 0.0f;
                    obj1->position -= temp;
                } else {
                    obj1->position -= n * (obj2_mass_ratio * delta);
                }

                if (obj2->position.y + obj2->radius + n.y * (obj1_mass_ratio * delta) >= window_height) {
                    sf::Vector2f temp = n * (obj1_mass_ratio * delta);
                    temp.y = 0.0f;
                    obj2->position += temp;
                } else {
                    obj2->position += n * (obj1_mass_ratio * delta);
                }
            }
        }
    }
}

// verlet integration
void CircleSolver::updatePosition(std::unique_ptr<CircleObject>& obj, float dt) {
    const sf::Vector2f velocity = obj->position - obj->lastPosiiton;
    obj->lastPosiiton = obj->position;
    obj->position = obj->position + velocity + obj->acceleration * dt * dt;
    obj->acceleration = {};
}

void CircleSolver::addAcceleration(std::unique_ptr<CircleObject>& obj) {
    obj->acceleration += {0.0f, GRAVITY};

}

void CircleSolver::addAge(std::unique_ptr<CircleObject>& obj, float dt) {
    obj->timeAlive += dt;
}
