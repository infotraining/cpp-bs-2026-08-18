#include "board.hpp"
#include "snake.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1600, 1000}), "SFML works!");

    Board board(80, 60, 10);
    Snake snake(40, 30);

    sf::Clock clock;
    sf::Clock apple_clock;
    Direction current_direction = Direction::Right;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const sf::Event::KeyPressed* key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (key_pressed->scancode)
                {
                case sf::Keyboard::Scan::Up:
                    current_direction = Direction::Up;
                    break;
                case sf::Keyboard::Scan::Down:
                    current_direction = Direction::Down;
                    break;
                case sf::Keyboard::Scan::Left:
                    current_direction = Direction::Left;
                    break;
                case sf::Keyboard::Scan::Right:
                    current_direction = Direction::Right;
                    break;
                }
            }
        }

        window.clear();

        auto elapsed = clock.getElapsedTime();

        if (apple_clock.getElapsedTime().asMilliseconds() >= 2000)
        {
            board.add_new_apple();
            apple_clock.restart();
        }

        if (elapsed.asMilliseconds() >= 100)
        {
            // drawing snake
            snake.move(current_direction, board);
            board.render_apples(window);
            board.render_snake(window, snake);

            window.display();
            clock.restart();
        }
    }
}
