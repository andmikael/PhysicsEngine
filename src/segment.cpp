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

void SegmentSolver::SpawnVerletObjectNonColliding(sf::Vector2f position, float radius, sf::Color color) {
    //if (numObjects >= MAX_OBJECTS) return;
    //VerletObject *ball = &objects[numObjects];
    CircleObject ball(position, radius, color);
    ball.position = position;
    ball.lastPosition = position;
    ball.radius = radius;
    ball.color = color;
    ball.isStatic = false;
    ball.isColliding = false;
    objects.push_back(ball);
    numOfObjects++;
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
    applyBorders();
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

int SegmentSolver::XYToNum(int x, int y, int width) {
    return y*width + x;
}

void SegmentSolver::SpawnStructureCloth(sf::Vector2f pos, int numOfSideJoints, float distance, float rad, sf::Color color) {
    for (int i = 0; i < numOfSideJoints; i++) {
        for (int j = 0; j < numOfSideJoints; j++) {
            // anchor the two top corners
            if ((i == 0 && j == 0) || (i == 0 && j == numOfSideJoints - 1)) {
                SpawnVerletObjectStatic(
                        (sf::Vector2f){ pos.x + j*distance - 5, pos.y + i*distance },
                        rad, color);
            }
            else {
                SpawnVerletObjectNonColliding(
                        (sf::Vector2f){ pos.x + j*distance, pos.y + i*distance },
                        rad, color);
            }
        }
    }
    for (int i = 0; i < numOfSideJoints; i++) {
        for (int j = 0; j < numOfSideJoints; j++) {
            if (i < numOfSideJoints - 1) {
                SpawnLink(
                        XYToNum(i, j, numOfSideJoints),
                        XYToNum(i + 1, j, numOfSideJoints),
                        distance);
            }
            if (j < numOfSideJoints - 1) {
                SpawnLink(
                        XYToNum(i, j, numOfSideJoints),
                        XYToNum(i, j + 1, numOfSideJoints),
                        distance);
            }
        }
    }
}

void SegmentSolver::applyBorders() {

    for (auto& obj : objects) {
        const float margin = MARGIN_WIDTH + obj.radius;
        sf::Vector2f collision_normal = {0.0f, 0.0f};

        // object hits the right border
        if (obj.position.x + obj.radius >= WINDOW_WIDTH) {
            collision_normal -= {obj.position.x - WINDOW_WIDTH + obj.radius, 0.0f};

        // object hits the left border
        } else if (obj.position.x < obj.radius) {
            collision_normal -= {obj.position.x - obj.radius, 0.0f};

        }

        // object hits the bottom border
        if (obj.position.y + obj.radius >= WINDOW_HEIGHT) {
            collision_normal -= {0.0f, obj.position.y - WINDOW_HEIGHT + obj.radius};

        // object hits the top border
        } else if (obj.position.y < obj.radius) {
                collision_normal += {0.0f, obj.radius};
        }

        // changes how elastic border collisions are; higher values means more rigid collisions
        obj.position += collision_normal * RESPONSE_COEF;
    }
  }

  void SegmentSolver::Attract(sf::Vector2f pos)
  {
        for (auto& obj: objects) {
        sf::Vector2f vec = pos - obj.position;
        obj.acceleration = {10*vec.x, 10*vec.y};
    }
  }
