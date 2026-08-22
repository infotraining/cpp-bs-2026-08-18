#include "snake.hpp"
#include "board.hpp"

Snake::Snake(int start_x, int start_y)
{
    segments_.push_back(Segment{start_x, start_y}); // head of snake
    segments_.push_back(Segment{start_x - 1, start_y});
    segments_.push_back(Segment{start_x - 2, start_y});
}

void Snake::move(Direction direction, Board& board)
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

    // new head of snake is calculated, and we need to add it to the front of the segments vector
    segments_.insert(segments_.begin(), new_head);

    // if the snake did not eat an apple, we need to remove the last segment of the snake
    if (not board.try_eat_apple(new_head))
    {
        segments_.pop_back();
    }
}

const std::vector<Segment>& Snake::segments() const
{
    return segments_;
}