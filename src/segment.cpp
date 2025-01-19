#include "segment.h"
#include <iostream>
#include <math.h>

constexpr float substep = 1.0f/FRAMERATE;

void SegmentSolver::SpawnLink(int pos1, int pos2, float distance) {
    segments.push_back((Segment) {
            &objects.at(pos1),
            &objects.at(pos2),
            //&objects[numOfObjects + pos1],
            //&objects[numOfObjects + pos2],
            distance });
        
        this->numOfSegments++;
}

void SegmentSolver::SpawnVerletObject(sf::Vector2f position, float radius, sf::Color color) {
    //if (numObjects >= MAX_OBJECTS) return;
    //VerletObject *ball = &objects[numObjects];
    CircleObject ball(position, radius, color);
    ball.isStatic = false;
    ball.isColliding = true;
    ball.lastPosition = position;
    ball.acceleration = GRAVITY;
    objects.push_back(ball);
    numOfObjects++;
}

void SegmentSolver::SpawnVerletObjectStatic(sf::Vector2f position, float radius, sf::Color color) {
    //if (numObjects >= MAX_OBJECTS) return;
    //VerletObject *ball = &objects[numObjects];
    CircleObject ball(position, radius, color);
    ball.isStatic = true;
    ball.isColliding = true;
    ball.lastPosition = position;
    ball.acceleration = GRAVITY;
    objects.push_back(ball);
    numOfObjects++;
}

void SegmentSolver::SpawnStructureRope(sf::Vector2f pos, int numJoints, float distance,
        float radius, Anchoring anchoring, sf::Color color) {
    //if (numOfObjects + numJoints >= MAX_OBJECTS) return;
    //if (numLinks + numJoints - 1 >= MAX_LINKS) return;
    // joints are too big
    if (radius > distance/2) return;

    // spawning objects for rope
    if (anchoring == FIRST || anchoring == BOTH) {
        SpawnVerletObjectStatic(pos, radius, color);
    }
    else {
        SpawnVerletObject(pos, radius, color);
    }
    for (int i = 1; i < numJoints - 1; i++) {
        SpawnVerletObject((sf::Vector2f){ pos.x + i*distance, pos.y }, radius, color);
    }
    if (anchoring == LAST || anchoring == BOTH) {
        SpawnVerletObjectStatic(
                (sf::Vector2f){ pos.x + (numJoints - 1)*distance, pos.y },
                radius, color);
    }
    else {
        SpawnVerletObject(
                (sf::Vector2f){ pos.x + (numJoints - 1)*distance, pos.y },
                radius, color);
    }

    // creating links
    for (int i = 0; i < numJoints - 1; i++) {
        SpawnLink(i, i + 1, distance);
    }
}

void SegmentSolver::Draw(sf::RenderWindow& window) {
    //for (int i = 0; i < numOfSegments; i++) {
    //    DrawLineEx(links[i].object1->currentPos, links[i].object2->currentPos, 2.0f,
    //            (Color){ g_red, g_green, g_blue, 255 });
    //}
    
    for (auto &obj : objects) {
        sf::CircleShape circle(obj.radius, 32);
        circle.setOrigin(obj.radius, obj.radius);
        circle.setPosition(obj.position);
        //circle.setFillColor(obj.color);
        window.draw(circle);
    }

    for (auto &segment : segments) {
        sf::Vertex line[2];
        line[0].position = segment.obj1->position;
        line[1].position = segment.obj2->position;
        window.draw(line, 2, sf::Lines);
    }
}

void SegmentSolver::UpdateRope() {
    for (auto &obj : objects) {
        if(!obj.isStatic)  {
            obj.acceleration += GRAVITY;
            obj.velocity = obj.position - obj.lastPosition;
            obj.lastPosition = obj.position;
            obj.position = obj.position + obj.velocity + obj.acceleration * substep * substep;
            obj.acceleration = {};
        }
    }
}

void SegmentSolver::ApplyLinks() {
    for (auto & segment : segments) {
        CircleObject *obj1 = segment.obj1;
        CircleObject *obj2 = segment.obj2;

        sf::Vector2f axis = obj1->position - obj2->position;
        float distance = sqrt(axis.x * axis.x + axis.y * axis.y);
        sf::Vector2 n = {axis.x / distance, axis.y / distance};
        float delta = segment.target_distance - distance;

        if (delta < 0) {
            if (!obj1->isStatic) {
                obj1->position.x += 0.5f*delta*n.x;
                obj1->position.y += 0.5f*delta*n.y;
            }
            if (!obj2->isStatic) {
                obj2->position.x -= 0.5f*delta*n.x;
                obj2->position.y -= 0.5f*delta*n.y;
            }
        }
    }
}

bool SegmentSolver::GetRopeState() {
    if (numOfObjects != 0) {
        return true;
    }
    return false;
}

void SegmentSolver::ClearRope() {
    segments.clear();
    objects.clear();
    numOfObjects = 0;
    numOfSegments = 0;
}