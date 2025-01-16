#include "renderer.h"

Renderer::Renderer(sf::RenderTarget& window)
    : window_target{window}
{
}

void Renderer::Render(CircleSolver& obj) {
    const auto& objects = obj.objects;
    for (auto& item : objects) {
        sf::CircleShape circle(item->radius, 32);
        circle.setPosition(item->position.x, item->position.y);
        window_target.draw(circle);
    }
}
