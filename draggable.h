#include "bezier_utility.h"

class Draggable: public Point2D {
private:
	int w;
	int h;
public:
	bool active;
	Draggable();
	Draggable(int x, int y);
	Draggable(int x, int y, int h, int w);
	bool intersects(int p_x, int p_y) const;
	void move(int p_x, int p_y);
};