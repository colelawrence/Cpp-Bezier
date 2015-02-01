#include <cstring>
#include <cmath>
#include "bezier_utility.h"


Point2D::Point2D():
	X(0),
	Y(0) {}

Point2D::Point2D(double X, double Y):
	X(X),
	Y(Y) {}

void Point2D::set(double X_p, double Y_p) {
	X = X_p;
	Y = Y_p;
}

void Point2D::set(Point2D* point_p) {
	X = (*point_p).X;
	Y = (*point_p).Y;
}

BezierBase::BezierBase(int values_length):
	values_length(values_length){}

BezierBase::~BezierBase(){
	delete[] temp_space;
}

double* BezierBase::interp (double t, double* values) {
	memcpy(temp_space, values, temp_space_bytes);
	for (int length = values_length - 1; length > 0; --length){
		for (int i = 0; i < length; i++) {
			temp_space[i] -= (temp_space[i] - temp_space[i+1]) * t;
		}
	}
	return temp_space;
}

double BezierCurve2D::calc_dist (double x1, double x2, double y1, double y2) {
	x1 -= x2;
	x1 *= x1;
	y1 -= y2;
	y1 *= y1;
	return std::sqrt(x1 + y1);
}

Point2D* BezierCurve2D::linear_raster (double* values, int max_results, double goal_dist, double tolerance) {
	Point2D* results = new Point2D[max_results];
	double last_result_t, last_result_v;
	// first value is always 0
	last_result_t = 0;
	last_result_v = *interp(last_result_t, values);
	for (int results_total = 0; results_total < max_results; ++results_total) { // for the amount of results
		double t, dist, v;
		double t_low = last_result_t;
		double t_high = 1; // find a way to approx based on previous
		for (int max_iterations = 128; max_iterations > 0; --max_iterations) { // attempt to find next point
			t = (t_high + t_low) / 2;
			v = *interp(t, values);
			dist = std::abs(last_result_v - v);
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
		last_result_v = v;
		last_result_t = t;
		Point2D* point = getT(t);
		results[results_total].set(point);
		delete point;
	}
	return results;
}
BezierCurve2D::BezierCurve2D(double* x_values, double* y_values, int values_length):
	BezierBase(values_length),
	Xs(x_values),
	Ys(y_values) {
	temp_space = new double[values_length];
	temp_space_bytes = values_length * sizeof(*temp_space);
}

Point2D* BezierCurve2D::rasterize (double goal_dist, int max_results, double tolerance) {
	Point2D* results = new Point2D[max_results];
	double last_result_t, last_result_x, last_result_y;
	// first value is always 0
	last_result_t = 0;
	last_result_x = *interp(last_result_t, Xs);
	last_result_y = *interp(last_result_t, Ys);
	for (int results_total = 0; results_total < max_results; ++results_total) { // for the amount of results
		double t, dist, x, y;
		double t_low = last_result_t;
		double t_high = 1; // find a way to approx based on previous
		for (int max_iterations = 128; max_iterations > 0; --max_iterations) { // attempt to find next point
			t = (t_high + t_low) / 2;
			x = *interp(t, Xs);
			y = *interp(t, Ys);
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
		results[results_total].set(x, y);
	}
	return results;
}

Point2D* BezierCurve2D::rasterizeToX (int max_results, double goal_dist, double tolerance) {
	return linear_raster(Xs, max_results, goal_dist, tolerance);
}

Point2D* BezierCurve2D::rasterizeToY (int max_results, double goal_dist, double tolerance) {
	return linear_raster(Ys, max_results, goal_dist, tolerance);
}

Point2D* BezierCurve2D::getT (double t) {
	double x = *interp(t, Xs);
	double y = *interp(t, Ys);
	return new Point2D(x, y);
}

double BezierCurve2D::measure (double segment_dist, double tolerance) {
	double total_length = 0;
	double last_result_t, last_result_x, last_result_y;
	// first value is always 0
	last_result_t = 0;
	last_result_x = *interp(last_result_t, Xs);
	last_result_y = *interp(last_result_t, Ys);
	for (int max_iterations = 128; max_iterations > 0; --max_iterations) { // just in case, limit
		double t, dist, x, y;
		double t_low = last_result_t;
		double t_high = 1; // find a way to approx based on previous
		for (int max_iterations = 128; max_iterations > 0; --max_iterations) { // attempt to find next point
			t = (t_high + t_low) / 2;
			x = *interp(t, Xs);
			y = *interp(t, Ys);
			dist = calc_dist(last_result_x, x, last_result_y, y);
			if (dist < segment_dist - tolerance) { // dist is too low, increase t
				t_low = t;
				t = (t_high + t) / 2;
			} else if (dist > segment_dist + tolerance) { // dist is too high, decrease t
				t_high = t;
				t = (t_low + t) / 2;
			} else { // dist is just right
				break;
			}
		}
		last_result_x = x;
		last_result_y = y;
		last_result_t = t;
		if (t > 1) {
			break; // end loop
		} else {
			total_length += dist;
		}
	}
	return total_length;
}
