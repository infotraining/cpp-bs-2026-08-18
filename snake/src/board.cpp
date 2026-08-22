#include "board.hpp"

Board::Board(int width, int height, int apple_count)
    : width_(width)
    , height_(height)
{
    for (int i = 0; i < apple_count; ++i)
    {
        apples_.push_back(Apple(rand() % width_, rand() % height_));
    }
}

void Board::render_snake(sf::RenderWindow& wnd, const Snake& snake)
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

void Board::render_apples(sf::RenderWindow& wnd)
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

bool Board::try_eat_apple(Apple apple_to_eat)
{
    for (int i = 0; i < apples_.size(); i++)
    {
        if (apples_[i] == apple_to_eat)
        {
            apples_.erase(apples_.begin() + i); // remove the apple from the board
            add_new_apple(); // add a new apple to the board
            return true;
        }
    }

    return false;
}

void Board::add_new_apple()
{
    int new_x = rand() % width_;
    int new_y = rand() % height_;
    
    apples_.push_back(Apple(new_x, new_y));
}

bool Board::is_hitting_wall(Segment new_head)
{
    return new_head.x < 0 || new_head.x >= width_ || new_head.y < 0 || new_head.y >= height_;
}