
#include <cstring>
#include <tuple>

double* bezier_interp (const double* numbers, double* temp_space, int temp_space_size, int numbers_total, double t_t_step) {
	memcpy(temp_space, numbers, temp_space_size);
	for (int length = numbers_total - 1; length > 0; --length){
		for (int i = 0; i < length; i++) {
			temp_space[i] -= (temp_space[i] - temp_space[i+1]) * t_t_step;
		}
	}
	return temp_space;
}

void bezier_t (double* numbers, int numbers_total, double* result, int definition) {
	double t_step = 1. / (definition - 1);
	double* temp_space = new double[numbers_total];
	int temp_space_size = sizeof(*temp_space) * numbers_total;
	for (int t = 0; t < definition; t++) {
		result[t] = *bezier_interp(numbers, temp_space, temp_space_size, numbers_total, t * t_step);
	}
	delete[] temp_space;
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