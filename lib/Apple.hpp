#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <random>

class Apple : public GameObject {
public:
    Apple();
    void randomizePosition();
    const sf::Vector2i& getPosition() const;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2i pos;
};
