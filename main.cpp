#include "draggable.h"
#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include "bezier_utility.h"

void drawPoint (sf::RenderWindow* window, const Point2D &point) {
	sf::RectangleShape drawPoint(sf::Vector2f(4, 4));
	drawPoint.setPosition(float(point.x) - 2, float(point.y) - 2);
    (*window).draw(drawPoint);
}

void drawPoints (sf::RenderWindow* window, const std::vector<Point2D> &points) {
	for (int i = 0; i < points.size(); i++) {
		drawPoint(window, points.at(i));
	}
}

void drawTest3 (sf::RenderWindow* window,const std::vector<Draggable> &control_points ) {
	// Test code

	double xs[4] = { 400, 700, 100, 400};
	double ys[4] = { 100, 790, 10, 700 };
	BezierCurve2D* bezier = new BezierCurve2D(xs, ys, 4);
	int max_results = 200;
	double goal_dist = 12;
	double dist_tolerance = .1;
	std::vector<Point2D> raster = (*bezier).rasterize(max_results, goal_dist, dist_tolerance);
	drawPoints(window, raster);
	std::cout << (*bezier).measure(goal_dist, dist_tolerance) << "\n";
	delete bezier;
}

void drawControls(sf::RenderWindow* window, std::vector<Draggable> control_points) {
	for (int i = 0; i < control_points.size(); i++)
	{
		drawPoint(window, control_points.at(i).getPosition());
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bezier test");
    //sf::CircleShape shape(3.f);
	//shape.setFillColor(sf::Color::White);

	Point2D last_position;
	std::vector<Draggable> control_points;
	control_points.emplace_back(400, 100);
	control_points.emplace_back(700, 790);
	control_points.emplace_back(100, 10);
	control_points.emplace_back(400, 700);

	bool active_dragging = false;
	Draggable* active_control_point;
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				last_position.x = double(event.mouseButton.x);
				last_position.y = double(event.mouseButton.y);
				for (int i = 0; i < control_points.size(); i++)
				{
					if (control_points.at(i).intersects(last_position.x, last_position.y))
					{
						active_control_point = &control_points.at(i);
						active_dragging = true;
						break;
					}
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (active_dragging)
					{
						double dx = last_position.x - event.mouseMove.x;
						double dy = last_position.y - event.mouseMove.y;
					}
				} else
				{
					active_dragging = false;
				}
			}
		}
		window.clear();
		drawControls(&window, control_points);
		drawTest3(&window, control_points);
		window.display();
	}
	
	return 0;
}
//*/