#include "api/shapes.hpp"

#include "brux/main.hpp"

#include "brux/shapes.hpp"

namespace BruxAPI {

////////////
// SHAPES //
////////////

bool hitLineLine(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);
	xyPnt d(x3, y3);

	return xyLineLine(&a, &b, &c, &d);
}

bool hitLineCircle(float x0, float y0, float x1, float y1, float x2, float y2, float r) {
	xyPnt a(x0, y0);
	xyPnt b(x1, y1);
	xyPnt c(x2, y2);

	return xyLineCircle(&a, &b, &c, r);
}

bool hitLinePoint(float x0, float y0, float x1, float y1, float x2, float y2) {
	return xyLinePoint(x0, y0, x1, y1, x2, y2);
}

} // namespace BruxAPI
