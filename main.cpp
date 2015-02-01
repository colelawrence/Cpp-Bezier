#include<iostream>
#include <SFML/Graphics.hpp>
#include "bezier_utility.h"

void drawPoint (sf::RenderWindow* window, Point2D* point) {
	sf::RectangleShape drawPoint(sf::Vector2f(4, 4));
	drawPoint.setPosition(float((*point).X) - 2, float((*point).Y) - 2);
    (*window).draw(drawPoint);
}

void drawPoints (sf::RenderWindow* window, Point2D* points, int points_length) {
	for (int i = 0; i < points_length; i++) {
		drawPoint(window, &points[i]);
	}
}

void drawTest3 (sf::RenderWindow* window) {
	// Test code

	double xs[4] = { 400, 700, 100, 400};
	double ys[4] = { 100, 790, 10, 700 };
	BezierCurve2D* bezier = new BezierCurve2D(xs, ys, 4);
	int max_results = 200;
	double goal_dist = 12;
	double dist_tolerance = .1;
	Point2D* raster = (*bezier).rasterize(max_results, goal_dist, dist_tolerance);
	drawPoints(window, raster, max_results);
	delete[] raster;
	std::cout << (*bezier).measure(goal_dist, dist_tolerance) << "\n";
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bezier test");
    //sf::CircleShape shape(3.f);
	//shape.setFillColor(sf::Color::White);

	window.clear();
	drawTest3(&window);
    window.display();
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	return 0;
}