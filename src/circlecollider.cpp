#include "circlecollider.h"
#include <iostream>

    CircleCollider::CircleCollider(sf::Vector2f pos, float rad, float outline_width, 
                        bool outside_collision, bool inside_collision, int point_count) {
                            this->position = pos;
                            this->radius = rad;
                            this->outline_width = outline_width;
                            this->inside_collision = inside_collision;
                            this->outside_collision = outside_collision;
                            this->point_count = point_count;

                            this->scale = sf::Vector2f(1.0f, 1.0f);
    }

    void CircleCollider::setRadius(float radius) {
        this->radius = radius;
    }

    void CircleCollider::setPosition(sf::Vector2f pos) {
        this->position = pos;
    }
    void CircleCollider::setOutlineWidth(float width) {
        this->outline_width = width;

    }
    void CircleCollider::enableInsideCollisions(bool val) {
        this->inside_collision = val;

    }
    void CircleCollider::enableOutsideCollisions(bool val) {
        this->outside_collision = val;

    }

    void CircleCollider::setColor(sf::Color color) {
        this->color = color;
    }
    // investigate why collision between balls and a circle is off centered
    // magic constatnts are added so that circle would be aligned with the actual 
    // pos and radius of the circle
    void CircleCollider::draw(sf::RenderWindow *window) {
        /*sf::CircleShape circle(this->radius - 15.0f, this->point_count);
        circle.setOrigin(this->radius, this->radius);
        circle.setScale(this->scale.x, this->scale.y);
        circle.setPosition(this->position.x+35.0f, this->position.y+32.0f);
        circle.setFillColor(sf::Color(255,0,0,0));
        circle.setOutlineColor(sf::Color(255,0,0,255));
        circle.setOutlineThickness(this->outline_width);*/

        
        sf::CircleShape circle(this->radius, this->point_count);
        circle.setOrigin(this->radius + this->outline_width, this->radius + this->outline_width);
        circle.setScale(this->scale.x, this->scale.y);
        circle.setPosition(this->position.x, this->position.y);
        circle.setFillColor(this->color);
        circle.setOutlineColor(sf::Color(255,0,0,255));
        circle.setOutlineThickness(this->outline_width);
        window->draw(circle);
    }
    void CircleCollider::apply(CircleObject* obj) {
        if (!this->outside_collision && !this->inside_collision) {
            return;
        }


            // Calculate the distance between the ball and the circle
            sf::Vector2f dist = obj->position - this->position;
            float magnitude = sqrt(dist.x * dist.x + dist.y * dist.y);

            // Check if the ball is inside the collider
            if (this->inside_collision)
            {   
                float delta = this->radius - obj->radius;
                bool ball_colliding_with_circle = magnitude >= delta;
                bool ball_inside_circle = magnitude < this->radius;

                if (ball_colliding_with_circle && (!this->outside_collision || ball_inside_circle))
                {   
                    obj->position += dist / magnitude * (delta - magnitude);
                    return;
                }
            }

            // Check if the ball is outside the collider
            if (this->outside_collision)
            {
                // outline width is only needed to take into account when calculating outside collisions 
                // since SFML setoutlinethickness potrudes thickness outwards by default and increases radius
                float rad_sum = obj->radius + this->radius + (this->outline_width);
                bool ball_colliding_with_circle = magnitude <= rad_sum;
                bool ball_outside_circle = magnitude > this->radius;

                if (ball_colliding_with_circle && (!this->inside_collision || ball_outside_circle))
                {
                    // Calculate the ball overlap (the amount the balls have overlapped)
                    sf::Vector2f overlap = dist / magnitude;
                    float offset = ((obj->radius ) + this->radius + this->outline_width);

                    // Update this balls position (move it to the side)
                    obj->position += (overlap * 0.5f * (offset - magnitude));
                }
            }
    }

void CircleCollider::SetHollowCircle() {
    int rad = (WINDOW_HEIGHT - 250) / 2;
    
}

void CircleCollider::SolveHollowCollisions(CircleObject *obj) {
    // Calculate the distance between the ball and the circle
            sf::Vector2f dist = obj->position - this->position;
            float magnitude = sqrt(dist.x * dist.x + dist.y * dist.y);

            // Check if the ball is inside the collider
            if (this->inside_collision)
            {   
                float delta = this->radius - obj->radius;
                bool ball_colliding_with_circle = magnitude >= delta;
                bool ball_inside_circle = magnitude < this->radius;

                if (ball_colliding_with_circle && (!this->outside_collision || ball_inside_circle))
                {   
                    obj->position += dist / magnitude * (delta - magnitude);
                    return;
                }
            }
}
