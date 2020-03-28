#pragma once

#include <SFML/Graphics.hpp>

class Idrawable {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
};
