////////////
// SHAPES //
////////////

::shape <- {};
::lastshape <- 0;

::Point <- class
{
	x = 0.0;
	y = 0.0;

	constructor(_x, _y)
	{
		x = _x;
		y = _y;
	}

	function _typeof() { return "point"; }
	function dot(p) { return (x * p.x) + (y* p.y); }
	function rotate(pivx, pivy, angle)
	{
		x -= pivx;
		y -= pivy;

		local theta = angle * (3.14159 / 180);
		local nx = (x * cos(theta)) - (y * sin(theta));
		local ny = (x * sin(theta)) + (y * cos(theta));

		nx += pivx;
		ny += pivy;

		x = nx;
		y = ny;
	}
}

::Shape <- class //Base class for all shapes
{
	x = 0.0;
	y = 0.0;
	a = 0.0;

	//Boundary coordinates
	lx = 0.0;
	ly = 0.0;
	ux = 0.0;
	uy = 0.0;

	constructor(_x, _y)
	{
		x = _x;
		y = _y;
	}

	function updatePoints(){}

	function setPos(_x = 0.0, _y = 0.0, _a = 0.0)
	{
		x = _x;
		y = _y;
		a = _a;
		updatePoints();
	}

	function modPos(_x = 0.0, _y = 0.0, _a = 0.0)
	{
		x += _x;
		y += _y;
		a += _a;
		updatePoints();
	}

	function getA()
	{
		return a;
	}

	function getX()
	{
		return x;
	}

	function getY()
	{
		return y;
	}

	function getW()
	{
		return ux - lx;
	}

	function getH()
	{
		return uy - ly;
	}

	function _typeof(){ return "shape"; }
}

::Circle <- class extends Shape
{
	r = 0.0;
	constructor(_x = 0.0, _y = 0.0, _r = 0.0)
	{
		x = _x;
		y = _y;
		r = _r;
	}

	function _typeof(){ return "circle"; }
}

::Ellipse <- class extends Shape
{
	w = 0.0;
	h = 0.0;

	constructor(_x, _y, _w, _h)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
	}

	function _typeof(){ return "ellipse"; }
}

::Line <- class extends Shape
{
	x2 = 0.0;
	y2 = 0.0;

	constructor(_x, _y, _x2, _y2)
	{
		x = _x.tofloat();
		y = _y.tofloat();
		x2 = _x2.tofloat();
		y2 = _y2.tofloat();
	}

	function _typeof(){ return "line"; }
}

/*
Squares and rectangles will just be polygons generated with specific parameters.
*/

::Polygon <- class extends Shape
{
	a = 0.0;
	p = []; //Original points
	pc = []; //Current points
	t = 0; //0 is polygon, 1 is rectangle

	//Array for keeping track of intersect ranges on x parallels
	//Eases collision detection, overhead if polygons are constantly updating
	xintersects = [];

	function addPoint(_x = 0.0, _y = 0.0)
	{
		p.push([_x, _y]);
		updatePoints();
	}

	function updatePoints()
	{

		pc = [];
		local pt = Point(0, 0);
		if(p.len() > 0)
		{
			for(local i = 0; i < p.len(); i++)
			{
				pt.x = p[i][0] + x;
				pt.y = p[i][1] + y;
				pt.rotate(x, y, a);
				pc.push([pt.x, pt.y]);
			}

			ux = pc[0][0];
			lx = pc[0][0];
			uy = pc[0][1];
			ly = pc[0][1];

			foreach(p in pc)
			{
				if(p[0] > ux) ux = p[0];
				if(p[0] < lx) lx = p[0];
				if(p[1] > uy) uy = p[1];
				if(p[1] < ly) ly = p[1];
			}

			updateIntersects();
		}
	}

	function updateIntersects() {
		xintersects = [];

		local unique_ys, rangesFound, p1, p2, y1, y2;

		// Compile unique Y values
		unique_ys = [];
		foreach(p in pc)
		{
			if ( !unique_ys.find( p[1] ) ) unique_ys.push( p[1] );
		}

		local aux = null;

		unique_ys.sort();
		foreach(uq_y in unique_ys)
		{
			// First iteration only
			if (aux == null)
			{
				// Generate auxiliary table for the intersect -- could be a class
				aux = {
					y1 = uq_y	// lower limit
					y2 = null	// upper limit
					amp = null	// amplitude
					edges = []	// edges intersected at any Y inside this segment
				}

				continue;
			}

			// Subsequent iterations
			if (aux.y2 == null)
			{
				aux.y2 = uq_y;	// upper limit of the segment
				aux.amp = aux.y2 - aux.y1;	// calculate amplitude

				xintersects.push(clone aux);	// copy the table into this property
				aux = {		// and start a new segment
					y1 = uq_y
					y2 = null
					amp = null
					edges = []
				}
			}
		}

		// Sort by lower limit ASC and amplitude DESC
		xintersects.sort(
			function(a, b)
			{
				if (a.y1 < b.y1) return -1;
				if (a.y1 > b.y1) return 1;

				if (a.amp > b.amp) return -1;
				if (a.amp < b.amp) return 1;

				return 0;
			}
		);

		// Analyse every one of the edges and save to intersects
		for(local i = 0; i < pc.len(); i++)
		{
			// Grab two adjacent points
			p1 = pc[i];
			p2 = pc[ (i + 1) % pc.len() ];

			// Make sure that y1 is the lower limit
			y1 = p1[1];
			y2 = p2[1];

			if (y1 > y2)
			{
				aux = y1;

				y1 = y2;
				y2 = aux;


				aux = p1;

				p1 = p2;
				p2 = aux;
			}

			// Look for a segment that shares Y values
			foreach( xint in xintersects )
			{
				if (
					!(
						xint.y1 >= y2 ||
						xint.y2 <= y1
					)
				) xint.edges.push([ p1, p2 ]);
			}
		}
	}

	function getXIntersectsAt(target_y)
	{
		local prev_amp = uy - ly;	// maximum possible amplitude for a segment
		local retval = null;	// default return value

		// Look for a segment that contains this Y value
		foreach(
			xint in xintersects.filter(
				function(i, val) {
					return val.y1 <= target_y && val.y2 >= target_y;
				}
			)
		)
		{
			//Narrow it down
			if (xint.amp < prev_amp) {
				prev_amp = xint.amp;
				retval = xint;
			}
		}

		return retval;
	}

	constructor(_x, _y, _p)
	{
		x = _x;
		y = _y;
		p = _p;

		updatePoints();
	}

	function draw()
	{
		if(pc.len() == 0) return;
		if(pc.len() == 1)
		{
			drawPoint(pc[0][0], pc[0][1]);
			return;
		}

		for(local i = 0; i < pc.len(); i++)
		{
			drawLine(
				pc[i][0],
				pc[i][1],
				pc[(i + 1) % pc.len()][0],
				pc[(i + 1) % pc.len()][1]
			);
		}
	}

	function _typeof(){
		if(t == 1) return "rectangle"
		return "polygon";
	}

	function setPos(_x, _y, _a)
	{
		local needsUpdate = (
			x != _x ||
			y != _y ||
			a != _a
		);

		x = _x;
		y = _y;
		a = _a;

		if (needsUpdate) updatePoints();
	}

	function modPos(_x, _y, _a)
	{
		local needsUpdate = (
			_x != 0 ||
			_y != 0 ||
			_a != 0
		);

		x += _x;
		y += _y;
		a += _a;

		if (needsUpdate) updatePoints();
	}

	function drawPos(_x, _y)
	{
		if(p.len() == 0) return;
		if(p.len() == 1)
		{
			drawPoint(_x + x, _y + y);
			return;
		}

		for(local i = 0; i < p.len(); i++)
		{
			if(i < p.len() - 1) drawLine(p[i][0] + _x + x, p[i][1] + _y + y, p[i + 1][0] + _x + x, p[i + 1][1] + _y + y);
			else drawLine(p[i][0] + _x + x, p[i][1] + _y + y, p[0][0] + _x + x, p[0][1] + _y + y);
		}
	}
}

::hitPointPoly <- function(x, y, p)
{
	//Cases for incomplete polygons
	if(p.pc.len() == 0) return false;
	if(p.pc.len() == 1) return (p.pc[0][0] == x && p.pc[0][1] == y);
	if(p.pc.len() == 2) return hitLinePoint(p.pc[0][0], p.pc[0][1], p.pc[1][0], p.pc[1][1], x, y);

	//Check that point is in bounds
	if(x < p.lx || x > p.ux || y < p.ly || y > p.uy) return false;

	//If so, count how many lines it touches
	local xint = p.getXIntersectsAt(y);	//Get the intersect segment first

	//If no intersects were found, this is either a vertex or a miss
	if (!xint) return p.pc.filter(
		function(i, v) { return abs(v[0] - x) < 1 && abs(v[1] - y) < 1; }
	).len() > 0;

	//Test the edges that are part of this segment only
	local count = 0;
	foreach(edge in xint.edges)
	{
		if (
			hitLineLine(
				// Polygon edge
				edge[0][0], edge[0][1],
				edge[1][0], edge[1][1],

				// Target coordinates to boundary
				x, y,
				p.lx, y
			)
		) count++;
	}

	//Even number of hits means the point is outside
	//I imagine possible but rare cases where this
	//may not be true, but the odds seem extremely
	//low, especially if the shapes have different
	//vectors of motion.
	return (count % 2 == 1);
}

::hitLinePoly <- function(x1, y1, x2, y2, p)
{
	//Test for PointPoly before doing any additional projections
	if (
		hitPointPoly(x1, y1, p) ||
		hitPointPoly(x2, y2, p)
	) return true;
	
	//Neither of the points are a hit, check LineLine against the intersects
	local x_intersect1 = p.getXIntersectsAt(y1);
	local x_intersect2 = p.getXIntersectsAt(y2);

	//No intersects = no hit
	if ( !x_intersect1 && !x_intersect2 ) return false;

	if (x_intersect1)
		foreach(edge in x_intersect1.edges)
			if (
				hitLineLine(
					edge[0][0], edge[0][1],
					edge[1][0], edge[1][1],

					x1, y1,
					x2, y2
				)
			) return true;

	if (x_intersect2)
		foreach(edge in x_intersect2.edges)
			if (
				hitLineLine(
					edge[0][0], edge[0][1],
					edge[1][0], edge[1][1],

					x1, y1,
					x2, y2
				)
			) return true;

	return false;
}

::hitPolyPoly <- function(a, b)
{
	//Process the polygon with less points first
	if (b.pc.len() < a.pc.len()) {
		local aux = a;
		a = b;
		b = aux;
	}

	//Go over each point and take the next to form the edge
	local edge = [];
	for(local i = 0; i < a.pc.len(); i++)
	{
		edge = [
			a.pc[i],
			a.pc[ (i + 1) % a.pc.len() ]	// nifty index wrap
		];

		if (
			hitLinePoly(
				edge[0][0], edge[0][1],
				edge[1][0], edge[1][1],

				b
			)
		) return true;
	}

	for(local i = 0; i < b.pc.len(); i++)
	{
		edge = [
			b.pc[i],
			b.pc[ (i + 1) % b.pc.len() ]
		];

		if (
			hitLinePoly(
				edge[0][0], edge[0][1],
				edge[1][0], edge[1][1],

				a
			)
		) return true;
	}

	return false;
}

::hitTest <- function(a, b)
{
	switch(typeof a)
	{
		case "circle":
			switch(typeof b)
			{
				case "circle":
					return (distance2(a.x, a.y, b.x, b.y) <= a.r + b.r);
					break;
				case "polygon":
					break;
				case "line":
					return hitLineCircle(b.x, b.y, b.x2, b.y2, a.x, a.y, a.r);
					break;
				case "ellipse":
					break;
				case "point":
					return (distance2(a.x, a.y, b.x, b.y) <= a.r);
					break;
				default:
					return false;
					break;
			}
			break;
		case "polygon":
			switch(typeof b)
			{
				case "circle":
					break;
				case "polygon":
					return hitPolyPoly(a, b);
					break;
				case "line":
					break;
				case "ellipse":
					break;
				case "point":
					return hitPointPoly(b.x, b.y, a);
					break;
				default:
					return false;
					break;
			}
			break;
		case "line":
			switch(typeof b)
			{
				case "circle":
					return hitLineCircle(a.x, a.y, a.x2, a.y2, b.x, b.y, b.r);
					break;
				case "polygon":
					break;
				case "line":
					return hitLineLine(a.x, a.y, a.x2, a.y2, b.x, b.y, b.x2, b.y2);
					break;
				case "ellipse":
					break;
				case "point":
					break;
				default:
					return false;
					break;
			}
			break;
		case "ellipse":
			switch(typeof b)
			{
				case "circle":
					break;
				case "polygon":
					break;
				case "line":
					break;
				case "ellipse":
					break;
				case "point":
					break;
				default:
					return false;
					break;
			}
			break;
		case "point":
			switch(typeof b)
			{
				case "circle":
					return (distance2(a.x, a.y, b.x, b.y) <= b.r);
					break;
				case "polygon":
					return hitPointPoly(a.x, a.y, b);
					break;
				case "line":
					break;
				case "ellipse":
					break;
				case "point":
					return (a.x == b.x && a.y == b.y);
					break;
				default:
					return false;
					break;
			}
			break;
		default:
			return false;
			break;
	}

	//If nothing returned
	//For collisions not yet
	//fully programmed
	return false;
}

