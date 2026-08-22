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