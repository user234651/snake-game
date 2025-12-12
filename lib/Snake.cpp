#include "Snake.hpp"
#include <algorithm>

constexpr int GRID_WIDTH = 1920 / 20;
constexpr int GRID_HEIGHT = 1080 / 20;
constexpr int GRID_SIZE = 20;
const sf::Vector2i UP{0,-1}, DOWN{0,1}, LEFT{-1,0}, RIGHT{1,0};
const sf::Color SNAKE_COLOR = sf::Color::Green;
const sf::Color BOARD_BACKGROUND_COLOR = sf::Color::Black;
const sf::Color BORDER_COLOR = sf::Color(93,216,228);

Snake::Snake() : bodyColor(SNAKE_COLOR), length(1), record_length(1) {
    reset();
}

void Snake::reset() {
    positions.clear();
    positions.push_back({ GRID_WIDTH/2, GRID_HEIGHT/2 });
    length = 1;
    direction = RIGHT;
    nextDirection = {0,0};
    last = std::nullopt;
    updateTitle();
}

void Snake::updateTitle() {
    if (length > record_length) record_length = length;
    title = "Змейка | Длина: " + std::to_string(length) + " | Рекорд: " + std::to_string(record_length);
}

const std::string& Snake::getTitle() const { return title; }

void Snake::setNextDirection(const sf::Vector2i& d) {
    if (d + direction == sf::Vector2i(0,0)) return;
    nextDirection = d;
}

void Snake::updateDirection() {
    if (nextDirection != sf::Vector2i(0,0)) {
        direction = nextDirection;
        nextDirection = {0,0};
    }
}

void Snake::move() {
    updateDirection();
    sf::Vector2i head = positions.front();
    sf::Vector2i newHead = {
        (head.x + direction.x + GRID_WIDTH) % GRID_WIDTH,
        (head.y + direction.y + GRID_HEIGHT) % GRID_HEIGHT
    };

    if (positions.size() > 1) last = positions.back(); else last = std::nullopt;

    positions.insert(positions.begin(), newHead);
    if ((int)positions.size() > length) positions.pop_back();
}

const sf::Vector2i& Snake::getHeadPosition() const { return positions.front(); }

void Snake::increaseLength() {
    ++length;
    updateTitle();
}

bool Snake::collidesWithSelf() const {
    if (positions.size() <= 4) return false;
    const sf::Vector2i& head = positions.front();
    return std::find(positions.begin()+1, positions.end(), head) != positions.end();
}

const std::vector<sf::Vector2i>& Snake::getPositions() const { return positions; }
int Snake::getRecordLength() const { return record_length; }

void Snake::draw(sf::RenderWindow& window) {
    for (const auto& p : positions) {
        sf::RectangleShape rect({(float)GRID_SIZE, (float)GRID_SIZE});
        rect.setPosition(sf::Vector2f(p.x * GRID_SIZE, p.y * GRID_SIZE));
        rect.setFillColor(bodyColor);
        rect.setOutlineThickness(1);
        rect.setOutlineColor(BORDER_COLOR);
        window.draw(rect);
    }

    if (last) {
        sf::RectangleShape rect({(float)GRID_SIZE, (float)GRID_SIZE});
        rect.setPosition(sf::Vector2f(last->x * GRID_SIZE, last->y * GRID_SIZE));
        rect.setFillColor(BOARD_BACKGROUND_COLOR);
        window.draw(rect);
    }
}
