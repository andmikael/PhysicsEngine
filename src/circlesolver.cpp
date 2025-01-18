#include "circlesolver.h"
#include <iostream>
#include <memory>
#include <SFML/Window.hpp>

// physics are tied to FPS
constexpr float substep = 1.0f/FRAMERATE;

void CircleSolver::AddObject(sf::Vector2f position, float radius) {
    CircleObject* circleObject = new CircleObject(position, radius);
    objects.push_back(circleObject);
}

/*
    Update objects
*/
void CircleSolver::Update() {
    CheckObjectCollision();

    const uint64_t objects_size = objects.size();
    for (uint64_t i{0}; i < objects_size; i++ ) {
        addAcceleration(objects.at(i), GRAVITY);
        updatePosition(objects.at(i));
        CheckConstraint(objects.at(i));
    }
}

void CircleSolver::CheckColliderConstraint(CircleCollider *collider) {
    for (auto obj : objects) {
        collider->apply(obj);
    }
}

/*
    Applies border collisions
*/
void CircleSolver::CheckConstraint(CircleObject* obj) {
    applyBorders(obj);
}

/*
    Iterates over all existing objects and checks for collisions
*/
void CircleSolver::CheckObjectCollision() {

    const float response_coeff = 0.75f;
    const uint64_t objects_count = objects.size();
    for (uint64_t i{0}; i<objects_count; i++) {
        CircleObject* obj1 = objects.at(i);
        for (uint64_t k{i+1}; k < objects_count; k++) {
            CircleObject* obj2 = objects.at(k);
            solveCollision(obj1, obj2);
        }
    }
}

/*
    Calculates objects velocity
*/
sf::Vector2f CircleSolver::calculateVelocity(CircleObject* obj) {
    return obj->position - obj->lastPosiiton;
}

/*
    Calculate objects next position using verlet integration
*/
sf::Vector2f CircleSolver::calculateDisplacement(CircleObject* obj, float dt) {
    //return float(2)*obj->position - obj->lastPosiiton + obj->acceleration*dt*dt;
    
    // temporarily using only x + v + (a*t) instead of 
    // x + v + (a*t²) since then acceleration would have to be a big value
    // to get reasonable acceleration for objects
    //std::cout << dt << std::endl;
    return obj->position + obj->velocity + obj->acceleration * dt * dt;
}

/*
    Updates object position
*/
void CircleSolver::updatePosition(CircleObject* obj) {
    //float dt = Time::getTime() - obj->start_time;
    obj->velocity = calculateVelocity(obj);
    obj->lastPosiiton = obj->position;
    obj->position = calculateDisplacement(obj, substep);
    obj->acceleration = {};
    obj->start_time = Time::getTime();
}

/*
    adds GRAVITY to objects
*/
void CircleSolver::addAcceleration(CircleObject* obj, sf::Vector2f acceleration) {
    obj->acceleration += acceleration;

}

/*
    Apply collisions with borders
*/
void CircleSolver::applyBorders(CircleObject* obj) {

    const float margin = MARGIN_WIDTH + obj->radius;
    sf::Vector2f collision_normal = {0.0f, 0.0f};

    // object hits the right border
    if (obj->position.x + obj->radius >= WINDOW_WIDTH) {
        collision_normal -= {obj->position.x - WINDOW_WIDTH + obj->radius, 0.0f};
    
    // object hits the left border
    } else if (obj->position.x < obj->radius) {
        collision_normal -= {obj->position.x - obj->radius, 0.0f};

    }
    
    // object hits the bottom border
    if (obj->position.y + obj->radius >= WINDOW_HEIGHT) {
        collision_normal -= {0.0f, obj->position.y - WINDOW_HEIGHT + obj->radius};

    // object hits the top border
    } else if (obj->position.y < obj->radius) {
            collision_normal += {0.0f, obj->radius};
    }

    // changes how elastic border collisions are; higher values means more rigid collisions
    obj->position += collision_normal * RESPONSE_COEF;
  }


    /*
        Calcualte collisions between two objects
    */
    void CircleSolver::solveCollision(CircleObject* obj1, CircleObject* obj2) {
    const sf::Vector2f displacement = obj1->position - obj2->position;
    const float square_distance = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
    const float min_distance = obj1->radius + obj2->radius;

    if (square_distance <= min_distance) { // (square_distance < min_distance * min_distance)

        const sf::Vector2f collision_normal = displacement / square_distance;
        obj1->position += collision_normal * 0.5f * (min_distance - square_distance);
        obj2->position -= collision_normal * 0.5f * (min_distance - square_distance);



        /*const float mass_proportion1 = obj1->radius * obj1->radius * obj1->radius;
        const float mass_proportion2 = obj2->radius * obj2->radius * obj2->radius;  
        const float total_mass_proportion = mass_proportion1 + mass_proportion2;    
        const float distance = sqrt(square_distance);   
        const sf::Vector2f collision_normal = displacement / distance;
        const float collision_ratio1 = mass_proportion2 / total_mass_proportion;
        const float collision_ratio2 = mass_proportion1 / total_mass_proportion;
        const float delta = RESPONSE_COEF * (distance - min_distance);

        obj1->position -= 1.0f * collision_normal * (collision_ratio1 * delta);
        obj2->position += 1.0f * collision_normal * (collision_ratio2 * delta);*/




      // elastic or rigid collision to be implemented
      /*if (!object1.fixed && !object2.fixed) {
        object1.curr_position -=
            0.5f * collision_normal * (collision_ratio1 * delta);
        object2.curr_position +=
            0.5f * collision_normal * (collision_ratio2 * delta);
      } else if (object1.fixed && !object2.fixed) {
        object2.curr_position += collision_normal * (collision_ratio1 * delta);
      } else {
        object1.curr_position -= collision_normal * (collision_ratio2 * delta);
      }*/
    }
  }
