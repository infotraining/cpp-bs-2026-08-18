#include "board.hpp"
#include "snake.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

enum class GameState {
    Menu,
    Play,
    GameOver
};

class SnakeGame
{
    sf::RenderWindow window_;
    Board board_;
    Snake snake_;
    Direction current_direction_;
    sf::Clock clock_;
    sf::Clock apple_clock_;
    GameState state_;
    sf::Font font_;

public:
    SnakeGame()
        : window_(sf::VideoMode({1500, 1000}), "Snake!!!")
        , board_(80, 60, 10)
        , snake_(40, 30)
        , current_direction_(Direction::Right)
        , state_(GameState::Menu)
    {
        if (!font_.openFromFile("C:/Windows/Fonts/arial.ttf"))
            std::cerr << "Failed to load font, text will not be rendered" << std::endl;
    }

    void run()
    {
        while (window_.isOpen())
        {
            process_events();
            update();
            render();
        }
    }

private:
    void start_new_game()
    {
        board_ = Board(75, 50, 10);
        snake_ = Snake(25, 25);
        current_direction_ = Direction::Right;
        clock_.restart();
        apple_clock_.restart();
        state_ = GameState::Play;
    }

    void process_events()
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window_.close();
            else if (const sf::Event::KeyPressed* key_pressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (state_ == GameState::Menu || state_ == GameState::GameOver)
                {
                    if (key_pressed->scancode == sf::Keyboard::Scan::Space)
                        start_new_game();
                }
                else if (state_ == GameState::Play)
                {
                    switch (key_pressed->scancode)
                    {
                    case sf::Keyboard::Scan::Up:
                        current_direction_ = Direction::Up;
                        break;
                    case sf::Keyboard::Scan::Down:
                        current_direction_ = Direction::Down;
                        break;
                    case sf::Keyboard::Scan::Left:
                        current_direction_ = Direction::Left;
                        break;
                    case sf::Keyboard::Scan::Right:
                        current_direction_ = Direction::Right;
                        break;
                    }
                }
            }
        }
    }

    void update()
    {
        if (state_ != GameState::Play)
            return;

        if (apple_clock_.getElapsedTime().asMilliseconds() >= 2000)
        {
            board_.add_new_apple();
            apple_clock_.restart();
        }

        if (clock_.getElapsedTime().asMilliseconds() >= 100)
        {
            if (snake_.move(current_direction_, board_) == false)
            {
                std::cout << "Snake dies!!! Game Over!!!" << std::endl;
                state_ = GameState::GameOver;
            }
            clock_.restart();
        }
    }

    void render()
    {
        switch (state_)
        {
        case GameState::Menu:
            render_menu();
            break;
        case GameState::Play:
            render_play();
            break;
        case GameState::GameOver:
            render_game_over();
            break;
        }

        window_.display();
    }

    void render_menu()
    {
        window_.clear(sf::Color(30, 30, 30));
        render_centered_text("Press Space - Begin Game", sf::Color::Green);
    }

    void render_play()
    {
        window_.clear();

        render_apples();
        render_snake();
    }

    void render_game_over()
    {
        window_.clear(sf::Color(60, 0, 0));
        render_centered_text("Game Over! Press Space - Back to Menu", sf::Color::Red);
    }

    void render_centered_text(const sf::String& string, sf::Color color)
    {
        sf::Text text(font_, string, 40);
        text.setFillColor(color);

        const auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f});
        text.setPosition({static_cast<float>(window_.getSize().x) / 2.f, static_cast<float>(window_.getSize().y) / 2.f});

        window_.draw(text);
    }

    void render_snake()
    {
        const float cell_width = static_cast<float>(window_.getSize().x) / board_.width();

        for (const auto& segment : snake_.segments())
        {
            sf::RectangleShape rectangle(sf::Vector2f(static_cast<float>(cell_width), static_cast<float>(cell_width)));
            rectangle.setPosition({segment.x * cell_width, segment.y * cell_width});
            rectangle.setFillColor(sf::Color::Green);
            window_.draw(rectangle);
        }
    }

    void render_apples()
    {
        const float cell_width = static_cast<float>(window_.getSize().x) / board_.width();
        const float cell_height = static_cast<float>(window_.getSize().y) / board_.height();

        static const sf::Texture apple_texture("apple.png");
        sf::Sprite apple_sprite(apple_texture);

        // uniform scale so the apple's height matches the snake's cell height, enlarged by 50%
        const float scale = 2.0f * cell_height / apple_texture.getSize().y;
        apple_sprite.setScale({scale, scale});
        apple_sprite.setOrigin({apple_texture.getSize().x / 2.f, apple_texture.getSize().y / 2.f});

        for (const auto& apple : board_.apples())
        {
            apple_sprite.setPosition({apple.x * cell_width + cell_width / 2.f, apple.y * cell_height + cell_height / 2.f});
            window_.draw(apple_sprite);
        }
    }
};

int main()
{
    SnakeGame game;
    game.run();
}
