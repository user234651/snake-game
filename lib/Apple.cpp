#include "Apple.hpp"

constexpr int GRID_WIDTH = 1920 / 20;
constexpr int GRID_HEIGHT = 1080 / 20;
constexpr int GRID_SIZE = 20;
const sf::Color APPLE_COLOR = sf::Color::Red;
const sf::Color BORDER_COLOR = sf::Color(93, 216, 228);

static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

Apple::Apple() : pos(GRID_WIDTH/2, GRID_HEIGHT/2) {
    randomizePosition();
}

void Apple::randomizePosition() {
    std::uniform_int_distribution<int> wx(0, GRID_WIDTH - 1);
    std::uniform_int_distribution<int> hy(0, GRID_HEIGHT - 1);
    pos = { wx(rng()), hy(rng()) };
}

const sf::Vector2i& Apple::getPosition() const { return pos; }

void Apple::draw(sf::RenderWindow& window) {
    sf::RectangleShape rect({(float)GRID_SIZE, (float)GRID_SIZE});
    rect.setPosition(sf::Vector2f(pos.x * GRID_SIZE, pos.y * GRID_SIZE));
    rect.setFillColor(APPLE_COLOR);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(BORDER_COLOR);
    window.draw(rect);
}
