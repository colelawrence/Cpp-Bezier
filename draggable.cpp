#include "draggable.h"

void Draggable::move(double dx, double dy) {
	x += dx;
	y += dy;
};

Draggable::Draggable() :
x(0), y(0), w(2.), h(2.)
{};

Draggable::Draggable(double x, double y, double h, double w) :
x(x), y(y), w(w * .5), h(h * .5)
{};

bool Draggable::intersects(double p_x, double p_y) {
	return p_x > x - w &&
		p_x < x + w &&
		p_y > y - h &&
		p_y < y + h;
};

Point2D Draggable::getPosition() {
	return Point2D(x, y);
}