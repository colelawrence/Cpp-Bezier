
#include <vector>

/*
 * @points should be mutable
 */
double* bezier_interp (double* points, double* temp_space, int temp_space_size, int points_total, double t_step_t) {
	memcpy(temp_space, points, temp_space_size);
	for (int pointsi = points_total; pointsi > 1; --pointsi){
		for (int pointsj = 1; pointsj < pointsi; pointsj++) {
			points[pointsj-1] -= (points[pointsj-1] - points[pointsj]) * t_step_t;
		}
	}
	return points;
}

double* bezier_t (double* numbers, int points_total, int definition) {
	double *result = new double[definition];
	
	double t_step = 1 / ((double) definition - 1);
	double t_step_t;
	double* temp_space = new double[points_total];
	int temp_space_size = sizeof(*temp_space) * points_total;
	for (int t = 0; t < definition; t++) {
		t_step_t = t * t_step;
		result[t] = *bezier_interp(numbers, temp_space, temp_space_size, points_total, t_step_t);
	}
	delete[] temp_space;
	return result;
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
	double* xs = bezier_t(numbers_x, 4, definition);
	double* ys = bezier_t(numbers_y, 4, definition);
	for (int dix = 0; dix < definition; dix++){ std::cout << xs[dix] << "\t"; }
	std::cout << "\n";
	for (int diy = 0; diy < definition; diy++){ std::cout << ys[diy] << "\t"; }
	std::cin.get();
	return 0;
}