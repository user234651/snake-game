#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <string>

class Snake : public GameObject {
public:
    Snake();
    void reset();
    void move();
    void increaseLength();
    bool collidesWithSelf() const;
    void setNextDirection(const sf::Vector2i& d);
    const sf::Vector2i& getHeadPosition() const;
    const std::vector<sf::Vector2i>& getPositions() const;
    int getRecordLength() const;
    void draw(sf::RenderWindow& window) override;
    const std::string& getTitle() const;

private:
    void updateDirection();
    void updateTitle();

    sf::Color bodyColor;
    std::vector<sf::Vector2i> positions;
    int length;
    int record_length;
    sf::Vector2i direction;
    sf::Vector2i nextDirection;
    std::optional<sf::Vector2i> last;
    std::string title;
};
