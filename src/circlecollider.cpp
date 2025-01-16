#include "circlecollider.h"

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
    void CircleCollider::draw(sf::RenderWindow *window) {
        sf::CircleShape circle(this->radius);
        circle.setOrigin(this->radius, this->radius);
        circle.setScale(this->scale.x, this->scale.y);
        circle.setPosition(this->position);
        circle.setFillColor(sf::Color(255,0,0,0));
        circle.setOutlineColor(sf::Color(255,0,0,255));
        circle.setOutlineThickness(this->outline_width);
        circle.setPointCount(this->point_count);
        window->draw(circle);
    }
    void CircleCollider::apply() {

    }
