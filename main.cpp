#include <SFML/Graphics.hpp>
#include "lib/Snake.hpp"
#include "lib/Apple.hpp"

constexpr int SCREEN_WIDTH  = 1920;
constexpr int SCREEN_HEIGHT = 1080;
constexpr float SPEED = 15.f;
const sf::Color BOARD_BACKGROUND_COLOR = sf::Color::Black;

int main() {
    sf::RenderWindow window(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "Змейка");
    window.setFramerateLimit(60);

    Snake snake;
    Apple apple;

    // --- Шрифт и текст ---
    sf::Font font;
    if (!font.openFromFile("../assets/LiberationSans-Regular.ttf")) return -1;
    sf::Text infoText(font, "", 24);
    infoText.setFillColor(sf::Color::White);
    infoText.setPosition({10.f, 10.f});

    sf::Clock clock;
    float timePerMove = 1.f / SPEED;
    float accumulator = 0.f;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (auto* key = event->getIf<sf::Event::KeyPressed>()) {
                using K = sf::Keyboard::Key;
                switch (key->code) {
                    case K::Escape: window.close(); break;
                    case K::Up:    snake.setNextDirection({0,-1}); break;
                    case K::Down:  snake.setNextDirection({0,1}); break;
                    case K::Left:  snake.setNextDirection({-1,0}); break;
                    case K::Right: snake.setNextDirection({1,0}); break;
                    default: break;
                }
            }
        }

        float dt = clock.restart().asSeconds();
        accumulator += dt;

        while (accumulator >= timePerMove) {
            accumulator -= timePerMove;
            snake.move();

            if (snake.getHeadPosition() == apple.getPosition()) {
                snake.increaseLength();
                do apple.randomizePosition();
                while (std::find(snake.getPositions().begin(), snake.getPositions().end(), apple.getPosition()) != snake.getPositions().end());
            }

            if (snake.collidesWithSelf()) {
                snake.reset();
                do apple.randomizePosition();
                while (std::find(snake.getPositions().begin(), snake.getPositions().end(), apple.getPosition()) != snake.getPositions().end());
            }

            window.setTitle(snake.getTitle());
        }

        infoText.setString(
            "Length: " + std::to_string(snake.getPositions().size()) +
            " | Record: " + std::to_string(snake.getRecordLength())
        );

        window.clear(BOARD_BACKGROUND_COLOR);
        apple.draw(window);
        snake.draw(window);
        window.draw(infoText);
        window.display();
    }
}
