#include <cstring>

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

// Provide a certain amount of values and approximate spacing between. (for creating )
void rasterize_bezier_to_waveform (double* x_values, double* y_values, int numbers_total, double* results, int definition) {
	double step_x = (x_values[0] - x_values[numbers_total-1]) / definition;
	double tolerance = 0.05 * step_x; // precision in percent
	results[0] = y_values[0];
	double goal_x = x_values[0]; // changes with each step
	double* temp_space = new double[numbers_total];
	int temp_space_size = sizeof(*temp_space) * numbers_total;
	for (int step = 1; step < definition; ++step) {
		goal_x += step_x; // Set a goal for ourself
		double test;
		double t = 0;
		double dt = .5;
		double dt_total = 0;
		double last_low_t = t;
		double last_high_t = t;
		while (true) { // Bisection TODO
			test = *bezier_interp(x_values, temp_space, temp_space_size, numbers_total, t);
			if (test > goal_x + tolerance)
				if (test > last_high_t)
					dt *= -2;
				else
					dt *= .5;
		}
	}
}

#include<iostream>

int main() {
	double numbers_x[] = {
		0, 0, 4, 4
	};
	double numbers_y[] = {
		0, 4, 4, 0
	};
	int definition = 8;
	double* xs = new double[definition];
	bezier_t(numbers_x, 4, xs, definition);
	double* ys = new double[definition];
	bezier_t(numbers_y, 4, ys, definition);
	for (int dix = 0; dix < definition; dix++){ std::cout << xs[dix] << "\t"; }
	std::cout << "\n";
	for (int diy = 0; diy < definition; diy++){ std::cout << ys[diy] << "\t"; }
	delete[] xs;
	delete[] ys;
	std::cin.get();
	return 0;
}