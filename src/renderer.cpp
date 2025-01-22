#include "renderer.h"
#include <iostream>

Renderer::Renderer(sf::RenderTarget& window)
    : window_target{window}
{
}

void Renderer::Render(CircleSolver& obj) {
    const auto& objects = obj.objects;
    for (auto& item : objects) {
        sf::CircleShape circle(item->radius, 32);
        circle.setOrigin(item->radius, item->radius);
        circle.setPosition(item->position.x, item->position.y);
        circle.setFillColor(item->color);
        window_target.draw(obj.rectangle);
        window_target.draw(circle);
    }
}
