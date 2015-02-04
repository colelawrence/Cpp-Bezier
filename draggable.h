#include "bezier_utility.h"

class Draggable {
private:
	double x;
	double y;
	double w;
	double h;
public:
	Draggable();
	Draggable(double x, double y, double h, double w);
	bool intersects(double p_x, double p_y);
	void move(double p_x, double p_y);
	Point2D getPosition();
};