#include <SFML/Graphics.hpp>

struct Point
{
    float x, y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }
};

class Circle
{
    Point coord_;
    double radius_;

public:
    Circle(Point coord, double r)
        : coord_(coord)
        , radius_(r)
    { }

    void move(float dx, float dy)
    {
        coord_.x += dx;
        coord_.y += dy;
    }

    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape circle(radius_);
        circle.setPosition(sf::Vector2{coord_.x, coord_.y});
        circle.setFillColor(sf::Color::Green);

        window.draw(circle);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML works!");
	sf::Clock clock;

    Circle c1(Point{200, 100}, 50);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        
		window.clear();

		auto elapsed = clock.getElapsedTime();
		if (elapsed.asMilliseconds() >= 25)
		{
			c1.move(2, 2);
    	    c1.draw(window);
        	window.display();
			clock.restart();
		}
    }
}
