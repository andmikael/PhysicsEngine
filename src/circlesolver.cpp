#include "circlesolver.h"
#include <iostream>
#include <memory>
#include <SFML/Window.hpp>

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

            /*// calculate the position difference of two objects
            const sf::Vector2f v = obj1->position - obj2->position;

            // calculate the distance between two points
            const float dist2 = sqrt(v.x * v.x + v.y * v.y) + 1.0e-9f;
            // the minimum distance before the two objects touch each other
            const float min_dist = obj1->radius + obj2->radius;

            // check if two objects are touching each other
            if (dist2 < min_dist) {
                const sf::Vector2f overlap = v / dist2;
                obj1->position += overlap * 0.5f * (min_dist - dist2);
                obj2->position -= overlap * 0.5f * (min_dist - dist2);

            }*/
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
    // temporarily using only x + v + (a*t) instead of 
    // x + v + (a*t²) since then acceleration would have to be a big value
    // to get reasonable acceleration for objects
    return obj->position + obj->velocity + obj->acceleration * dt;
}

/*
    Updates object position
*/
void CircleSolver::updatePosition(CircleObject* obj) {
    float dt = Time::getTime() - obj->start_time;
    obj->velocity = calculateVelocity(obj);
    obj->lastPosiiton = obj->position;
    obj->position = calculateDisplacement(obj, dt);
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

    const float margin = MARGIN_WIDTH + 2*obj->radius;
    sf::Vector2f collision_normal = {0.0f, 0.0f};

    // object hits the right border
    if (obj->position.x > WINDOW_WIDTH - margin) {
      collision_normal += {(obj->position.x - WINDOW_WIDTH + margin), 0.0f};
    
    // object hits the left border
    } //else if (obj->position.x < margin) {
    else if (obj->position.x < 0) {
      collision_normal -= {(-obj->position.x), 0.0f};
    }
    
    // object hits the bottom border
    if (obj->position.y > WINDOW_HEIGHT - margin) {
      collision_normal += {0.0f, (obj->position.y - WINDOW_HEIGHT + margin)};

    // object hits the top border
    } //else if (obj->position.y < margin) {
    // SFML border coodrinates are a bit wack
    else if (obj->position.y < 0) {
      collision_normal -= {0.0f, (-obj->position.y)};
    }

    // changes how elastic border collisions are; higher values means more rigid collisions
    obj->position -= ELASTIC_COEFF * collision_normal * RESPONSE_COEF;
  }


    /*
        Calcualte collisions between two objects
    */
    void CircleSolver::solveCollision(CircleObject* obj1, CircleObject* obj2) {
    const sf::Vector2f displacement = obj1->position - obj2->position;
    const float square_distance = displacement.x * displacement.x + displacement.y * displacement.y;
    const float min_distance = obj1->radius + obj2->radius;

    if (square_distance < min_distance * min_distance) {
        const float mass_proportion1 = obj1->radius * obj1->radius * obj1->radius;
        const float mass_proportion2 = obj2->radius * obj2->radius * obj2->radius;  
        const float total_mass_proportion = mass_proportion1 + mass_proportion2;    
        const float distance = sqrt(square_distance);   
        const sf::Vector2f collision_normal = displacement / distance;
        const float collision_ratio1 = mass_proportion2 / total_mass_proportion;
        const float collision_ratio2 = mass_proportion1 / total_mass_proportion;
        const float delta = RESPONSE_COEF * (distance - min_distance);

        obj1->position -= 0.5f * collision_normal * (collision_ratio1 * delta);
        obj2->position += 0.5f * collision_normal * (collision_ratio2 * delta);

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
