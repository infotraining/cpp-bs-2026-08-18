#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "snake.hpp"

using Apple = Point;

/*******
 * Apple apple(10, 20);
 * apple.x = 30;
 *
 * Apple apple2(30, 20);
 *
 * if (apple == apple2) {
 *   // do something
 * }
 *******/

class Board
{
    int width_;
    int height_;
    std::vector<Apple> apples_;

public:
    Board(int width, int height, int apple_count);
    void add_new_apple();
    bool try_eat_apple(Apple apple_to_eat);
    void render_snake(sf::RenderWindow& wnd, const Snake& snake);
    void render_apples(sf::RenderWindow& wnd);
};