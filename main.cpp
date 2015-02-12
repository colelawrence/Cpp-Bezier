#include "draggable.h"
#include<iostream>
#include<vector>
#include <SFML/Graphics.hpp>
#include "bezier_utility.h"
#include "point.h"

void drawPoint (sf::RenderWindow* window, const Point2D &point, int size = 4) {
	sf::RectangleShape drawPoint(sf::Vector2f(size, size));
	drawPoint.setPosition(float(point.x) - .5 * size, float(point.y) - .5 * size);
    (*window).draw(drawPoint);
}

void drawPoints (sf::RenderWindow* window, const std::vector<Point2D> &points) {
	for (int i = 0; i < points.size(); i++) {
		drawPoint(window, points.at(i));
	}
}

void drawTest3 (sf::RenderWindow* window,const std::vector<Draggable> &control_points ) {
	// Test code

	int size = control_points.size();
	double* xs = new double(size);
	double* ys = new double(size);
	for (int i = 0; i < size; ++i) {
		xs[i] = control_points.at(i).x;
		ys[i] = control_points.at(i).y;
	}
	BezierCurve2D bezier(xs, ys, size);
	int max_results = 200;
	double goal_dist = 12;
	double dist_tolerance = .1;
	std::vector<Point2D> raster = bezier.rasterizeToX(max_results, goal_dist, dist_tolerance);
	drawPoints(window, raster);
	//std::cout << bezier.measure(goal_dist, dist_tolerance) << "\n";
}

void drawControls(sf::RenderWindow* window, const std::vector<Draggable> &control_points) {
	for (int i = 0; i < control_points.size(); i++)
		drawPoint(window, control_points.at(i), 8);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bezier test");
    //sf::CircleShape shape(3.f);
	//shape.setFillColor(sf::Color::White);

	int last_position_x;
	int last_position_y;
	std::vector<Draggable> control_points;
	control_points.emplace_back(10, 100, false);
	control_points.emplace_back(700, 790);
	control_points.emplace_back(100, 10);
	control_points.emplace_back(790, 700, false);

	bool active_dragging = false;
	Draggable *active_control_point;
	active_control_point = NULL;
    while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape) window.close();

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				if (active_control_point == NULL)
				{
					last_position_x = event.mouseButton.x;
					last_position_y = event.mouseButton.y;
					for (int i = 0; i < control_points.size(); i++)
					{
						if (control_points.at(i).intersects(last_position_x, last_position_y))
						{
							active_control_point = &control_points.at(i);
							break;
						}
					}
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (active_control_point != NULL) {
						int dx = last_position_x - event.mouseMove.x;
						int dy = last_position_y - event.mouseMove.y;
						last_position_x = event.mouseMove.x;
						last_position_y = event.mouseMove.y;
						(*active_control_point).move(-dx, -dy);
					}
				} else
				{
					active_control_point = NULL;
				}
			}
		}
		window.clear();
		drawControls(&window, control_points);
		drawTest3(&window, control_points);
		window.display();
	}
	//*/
	
	return 0;
}
//*/