#include "snake.hpp"
#include "board.hpp"

#include <algorithm>

Snake::Snake(int start_x, int start_y)
{
    segments_.push_back(Segment{start_x, start_y}); // head of snake
    segments_.push_back(Segment{start_x - 1, start_y});
    segments_.push_back(Segment{start_x - 2, start_y});
}

bool Snake::move(Direction direction, Board& board)
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

    if (board.is_hitting_wall(new_head) || is_eating_self(new_head))
    {
        return false;
    }

    segments_.insert(segments_.begin(), new_head);

    // if the snake did not eat an apple, we need to remove the last segment of the snake
    if (not board.try_eat_apple(new_head))
    {
        segments_.pop_back();
    }

    return true;
}

bool Snake::is_eating_self(Segment new_head)
{
    return std::find(segments_.begin(), segments_.end(), new_head) != segments_.end();
}

const std::vector<Segment>& Snake::segments() const
{
    return segments_;
}