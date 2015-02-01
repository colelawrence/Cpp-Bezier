#include<iostream>
#include <SFML/Graphics.hpp>
#include "bezier_utility.h"

void drawPoint (float x, float y, sf::RenderWindow* window) {
	sf::RectangleShape point(sf::Vector2f(3, 3));
	point.setPosition(x - 1.5, y - 1.5);
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

void drawTest1 (sf::RenderWindow* window) {
	// Test code

	double xs[5] = { 10, 100, 800, 300, 790 };
	double ys[5] = { 10, 400, 400, 0, 790 };
	int numbers_total = 5;
	int max_results = 200;
	double goal_dist = 6;
	double dist_tolerance = .5;
	double* raster = rasterize_bezier(xs, ys, numbers_total, max_results, goal_dist, dist_tolerance);
	drawPointsOfTs(window, raster, xs, ys, numbers_total, max_results);
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Bezier test");
    //sf::CircleShape shape(3.f);
	//shape.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		drawTest1(&window);
        window.display();
    }

    return 0;
}