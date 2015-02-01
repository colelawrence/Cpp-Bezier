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
			t = (t_high + t_low) / 2;
			x = *bezier_interp(x_values, temp_space, temp_space_size, values_count, t);
			y = *bezier_interp(y_values, temp_space, temp_space_size, values_count, t);
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