#ifndef BEZIER_UTILITY_H
#define BEZIER_UTILITY_H

class Point2D {
public:
	double X;
	double Y;
	Point2D();
	Point2D(double X, double Y);
	void set(double X_p, double Y_p);
	void set(Point2D* point_p);
};

class BezierBase {
protected:
	int values_length;
	double* temp_space;
	int temp_space_bytes;
	int count;
	double* interp (double t, double* values);
public:
	BezierBase(int values_length);
	~BezierBase();
};

class BezierCurve2D: public BezierBase {
private:
	double* Xs;
	double* Ys;
	double calc_dist (double x1, double x2, double y1, double y2);
	std::vector<Point2D> linear_raster (double* values, int max_results, double goal_dist, double tolerance);
public:
	BezierCurve2D(double* x_values, double* y_values, int values_length);
	std::vector<Point2D> rasterize (int max_results, double goal_dist, double tolerance);
	std::vector<Point2D> rasterizeToX (int max_results, double goal_dist, double tolerance);
	std::vector<Point2D> rasterizeToY (int max_results, double goal_dist, double tolerance);
	Point2D* getT (double t);
	double measure (double segment_dist, double tolerance);
};

#endif