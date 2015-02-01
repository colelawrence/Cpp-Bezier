#include<iostream>
#include <SFML/Graphics.hpp>
#include "bezier_utility.h"

void drawPoint (float x, float y, sf::RenderWindow* window) {
	sf::RectangleShape point(sf::Vector2f(4, 4));
	point.setPosition(x - 2, y - 2);
    (*window).draw(point);
}

void drawPointsOfTs(sf::RenderWindow* window, double* ts, double* xs, double* ys, int numbers_total, int t_count) {
	double* temp_space = new double[numbers_total];
	int temp_space_size = sizeof(*temp_space) * numbers_total;
	double t, x, y;
	for (int step = 0; step < t_count; step++) {
		t = ts[step];
		x = *bezier_interp(xs, temp_space, temp_space_size, numbers_total, t);
		y = *bezier_interp(ys, temp_space, temp_space_size, numbers_total, t);
		drawPoint(float(x), float(y), window);
	}
}

void drawTest3 (sf::RenderWindow* window) {
	// Test code

	double xs[4] = { 400, 400, 400, 400};
	double ys[4] = { 100, 790, 10, 700 };
	int numbers_total = 4;
	int max_results = 200;
	double goal_dist = 12;
	double dist_tolerance = .1;
	double* raster = rasterize_bezier(xs, ys, numbers_total, max_results, goal_dist, dist_tolerance);
	drawPointsOfTs(window, raster, xs, ys, numbers_total, max_results);
	std::cout << measure_bezier(xs, ys, numbers_total, goal_dist, dist_tolerance) << "\n";
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