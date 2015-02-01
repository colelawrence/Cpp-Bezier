#include <cstring>
#include <cmath>

double* bezier_interp (const double* numbers, double* temp_space, int temp_space_size, int numbers_total, double t) {
	memcpy(temp_space, numbers, temp_space_size);
	for (int length = numbers_total - 1; length > 0; --length){
		for (int i = 0; i < length; i++) {
			temp_space[i] -= (temp_space[i] - temp_space[i+1]) * t;
		}
	}
	return temp_space;
}

void bezier_t (double* numbers, int numbers_total, double* result, int definition) {
	double t_step = 1. / (definition - 1);
	double* temp_space = new double[numbers_total];
	int temp_space_size = sizeof(*temp_space) * numbers_total;
	for (int step = 0; step < definition; step++) {
		result[step] = *bezier_interp(numbers, temp_space, temp_space_size, numbers_total, step * t_step);
	}
	delete[] temp_space;
}

double calc_dist (double x1, double x2, double y1, double y2) {
	x1 -= x2;
	x1 *= x1;
	y1 -= y2;
	y1 *= y1;
	return std::sqrt(x1 + y1);
}

double* rasterize_bezier (double* x_values, double* y_values, int values_count, int max_results, double goal_dist, double tolerance) {
	double* results_t = new double[max_results];
	double* temp_space = new double[values_count];
	int temp_space_size = sizeof(*temp_space) * values_count;
	double last_result_t, last_result_x, last_result_y;
	// first value is always 0
	last_result_t = 0;
	last_result_x = *bezier_interp(x_values, temp_space, temp_space_size, values_count, last_result_t);
	last_result_y = *bezier_interp(y_values, temp_space, temp_space_size, values_count, last_result_t);
	for (int results_total = 0; results_total < max_results; ++results_total) { // for the amount of results
		double t, dist, x, y;
		double t_low = last_result_t;
		double t_high = 1; // find a way to approx based on previous
		for (int max_iterations = 128; max_iterations > 0; --max_iterations) { // attempt to find next point
			//ax = *bezier_interp(x_values, temp_space, temp_space_size, values_count, a);
			//ay = *bezier_interp(y_values, temp_space, temp_space_size, values_count, a);
			//bx = *bezier_interp(x_values, temp_space, temp_space_size, values_count, b);
			//by = *bezier_interp(y_values, temp_space, temp_space_size, values_count, b);
			t = (t_high + t_low) / 2;
			x = *bezier_interp(x_values, temp_space, temp_space_size, values_count, t);
			y = *bezier_interp(y_values, temp_space, temp_space_size, values_count, t);
			//dista = calc_dist(last_result_x, ax, last_result_y, ay);
			//distb = calc_dist(last_result_x, bx, last_result_y, by);
			dist = calc_dist(last_result_x, x, last_result_y, y);
			if (dist < goal_dist - tolerance) { // dist is too low, increase t
				t_low = t;
				t = (t_high + t) / 2;
			} else if (dist > goal_dist + tolerance) { // dist is too high, decrease t
				t_high = t;
				t = (t_low + t) / 2;
			} else { // dist is just right
				break;
			}
		}
		last_result_x = x;
		last_result_y = y;
		last_result_t = t;
		results_t[results_total] = t;
	}
	delete[] temp_space;
	return results_t;
}

double bisect_to_goal (double* x_values, int numbers_total, double goal) {
	return 0;
}

#include<iostream>
#include <SFML/Graphics.hpp>

void drawPoint (float x, float y, sf::RenderWindow* window) {
	sf::RectangleShape point(sf::Vector2f(3, 3));
	point.setPosition(x - 1.5, y - 1.5);
    (*window).draw(point);
}

void drawTest (sf::RenderWindow* window) {
	// Test code
	
	double xs[4] = { 10, 100, 300, 790 };
	double ys[4] = { 10, 400, 0, 790 };
	int numbers_total = 4;
	int max_results = 200;
	double goal_dist = 6;
	double dist_tolerance = .5;
	double* raster = rasterize_bezier(xs, ys, numbers_total, max_results, goal_dist, dist_tolerance);
	double* temp_space = new double[numbers_total];
	int temp_space_size = sizeof(*temp_space) * numbers_total;
	double t, x, y;
	for (int step = 0; step < max_results; step++) {
		t = raster[step];
		x = *bezier_interp(xs, temp_space, temp_space_size, numbers_total, t);
		y = *bezier_interp(ys, temp_space, temp_space_size, numbers_total, t);
		drawPoint(float(x), float(y), window);
	}
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
		drawTest(&window);
        window.display();
    }

    return 0;
}