#ifndef BEZIER_UTILITY_H
#define BEZIER_UTILITY_H

double* rasterize_bezier (double* x_values, double* y_values, int values_count, int max_results, double goal_dist, double tolerance);
double* rasterize_linear_bezier (double* values, int values_count, int max_results, double goal_dist, double tolerance);
double* bezier_interp (const double* numbers, double* temp_space, int temp_space_size, int numbers_total, double t);
 
#endif