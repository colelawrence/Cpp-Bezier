#include "draggable.h"

void Draggable::move(int dx, int dy) {
	x += dx;
	y += dy;
};

Draggable::Draggable() :
Point2D(0, 0), w(4), h(4), active(false)
{};

Draggable::Draggable(int x, int y) :
Point2D(x, y), w(4), h(4), active(false)
{};

Draggable::Draggable(int x, int y, int h, int w) :
Point2D(x, y), w(w * .5), h(h * .5), active(false)
{};

bool Draggable::intersects(int p_x, int p_y) const {
	return p_x > x - w &&
		p_x < x + w &&
		p_y > y - h &&
		p_y < y + h;
};
