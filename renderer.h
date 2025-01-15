#pragma once
#include <SFML/Graphics.hpp>
#include "circlesolver.h"


class Renderer
{
public:
    Renderer(sf::RenderTarget& window);

    void Render(CircleSolver& obj);

private:
    sf::RenderTarget& window_target;
};