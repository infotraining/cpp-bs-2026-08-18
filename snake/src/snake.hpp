#pragma once

#include <vector>


enum class Direction {
    Up,
    Down,
    Left,
    Right
};

struct Point
{
    int x, y;

    Point(int x, int y)
        : x(x)
        , y(y)
    {
    }

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

/*******
 * Point pt1(10, 20);
 * pt1.x = 30;
 *
 * Point pt2(30, 20);
 *
 * if (pt1 == pt2) {
 *   // do something
 * }
 *******/

// type alias
using Segment = Point;

/***********
 * Segment seg(10, 20);
 * seg.x = 30;
 * Segment seg2(30, 20);
 * if (seg == seg2) {
 *   // do something
 * }
 ***********/

class Board;

class Snake
{
    std::vector<Segment> segments_;
    bool is_eating_self(Segment new_head);

public:
    Snake(int start_x, int start_y);
    bool move(Direction direction, Board& board);
    const std::vector<Segment>& segments() const;
};