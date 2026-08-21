#include <SFML/Graphics.hpp>

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

struct Point
{
    int x, y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

// type alias
using Segment = Point;

class Snake
{
    std::vector<Segment> segments_;

public:
    Snake(int start_x, int start_y)
    {
        segments_.push_back(Segment{start_x, start_y}); // head of snake
        segments_.push_back(Segment{start_x - 1, start_y});
        segments_.push_back(Segment{start_x - 2, start_y});
    }

    void move(Direction direction)
    {
        Segment new_head = segments_.front();

        switch (direction)
        {
        case Direction::Up:
            new_head.y -= 1;
            break;
        case Direction::Down:
            new_head.y += 1;
            break;
        case Direction::Left:
            new_head.x -= 1;
            break;
        case Direction::Right:
            new_head.x += 1;
            break;
        }

        segments_.insert(segments_.begin(), new_head);
        segments_.pop_back();
    }

    const std::vector<Segment>& segments() const
    {
        return segments_;
    }
};

using Apple = Point;

class Board
{
    int width_;
    int height_;
    std::vector<Apple> apples_;

public:
    Board(int width, int height, int apple_count)
        : width_(width)
        , height_(height)
    {
        for (int i = 0; i < apple_count; ++i)
        {
            apples_.push_back(Apple(rand() % width_, rand() % height_));
        }
    }

    void render_snake(sf::RenderWindow& wnd, const Snake& snake)
    {
        const int wnd_width = wnd.getSize().x;
        const int wnd_height = wnd.getSize().y;

        const float segment_width = wnd_width / width_;

        for (const auto& segment : snake.segments())
        {
            sf::RectangleShape rect(sf::Vector2f{segment_width, segment_width});
            rect.setFillColor(sf::Color::Green);
            rect.setPosition({segment_width * segment.x, segment_width * segment.y});
            wnd.draw(rect);
        }
    }

    void render_apples(sf::RenderWindow& wnd)
    {
        const int wnd_width = wnd.getSize().x;
        const int wnd_height = wnd.getSize().y;

        const float apple_width = wnd_width / width_;

        for (const Apple& apple : apples_)
        {
            sf::RectangleShape rect(sf::Vector2f{apple_width, apple_width});
            rect.setFillColor(sf::Color::Red);
            rect.setPosition({apple_width * apple.x, apple_width * apple.y});
            wnd.draw(rect);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");

    Board board(80, 60, 10);
    Snake snake(40, 30);

    sf::Clock clock;
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
        if (elapsed.asMilliseconds() >= 100)
        {
            // drawing snake
            snake.move(current_direction);
            board.render_snake(window, snake);
            board.render_apples(window);

            window.display();
            clock.restart();
        }
    }
}
