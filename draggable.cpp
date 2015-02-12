#include "draggable.h"

void Draggable::move(int dx, int dy) {
	if (restrictions)
	{
		if (restrictXY)
			x += dx;
		else
			y += dy;
	}
	else
	{
		x += dx;
		y += dy;
	}
};

Draggable::Draggable() :
Point2D(0, 0), w(4), h(4), active(false), restrictions(false), restrictXY(true)
{};

Draggable::Draggable(int x, int y) :
Point2D(x, y), w(4), h(4), active(false), restrictions(false), restrictXY(true)
{};

Draggable::Draggable(int x, int y, bool restrictXY) :
Point2D(x, y), w(4), h(4), active(false), restrictions(true), restrictXY(restrictXY)
{};

Draggable::Draggable(int x, int y, int h, int w) :
Point2D(x, y), w(w * .5), h(h * .5), active(false), restrictions(false), restrictXY(true)
{};

bool Draggable::intersects(int p_x, int p_y) const {
	return p_x > x - w &&
		p_x < x + w &&
		p_y > y - h &&
		p_y < y + h;
};
