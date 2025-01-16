#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "circlesolver.h"

// forward declaration to avoid circular dependencies
struct CircleObject;

class CircleCollider {
    public:
        sf::Vector2f position;
        sf::Vector2f scale;

        int point_count;
        float outline_width;
        float radius;

        bool inside_collision;
        bool outside_collision;

        CircleCollider(sf::Vector2f pos, float rad, float outline_width, 
                        bool outside_collision, bool inside_collision, int point_count);

        void setRadius(float radius);
        void setPosition(sf::Vector2f pos);
        void setOutlineWidth(float width);
        void enableInsideCollisions(bool val);
        void enableOutsideCollisions(bool val);
        void draw(sf::RenderWindow *window);
        void apply(CircleObject* obj);
};