////////////
// SHAPES //
////////////

::shape <- {};
::lastshape <- 0;

::Point <- class
{
	x = 0.0;
	y = 0.0;

	function _typeof() { return "point"; }
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
	p = [];
	pc = [];
	t = 0; //0 is polygon, 1 is rectangle

	function addPoint(_x = 0.0, _y = 0.0)
	{
		p.push(Point(_x, _y));
	}

	function updatePoints()
	{
		pc = [];
		if(p.len() > 0) for(local i = 0; i < p.len(); i++)
		{
			local pt = clone(p[i]);
			pt.x += x;
			pt.y += y;
			//Rotate point position here
			pc.push(pt);
		}
	}

	function _typeof(){
		if(t == 1) return "rectangle"
		return "polygon";
	}
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
					break;
				case "ellipse":
					break;
				case "rectangle":
					break;
				case "point":
					return (distance2(a.x, a.y, b.x, b.y) <= a.r);
					break;
				default:
					break;
			}
			break;
		case "polygon":
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
				case "rectangle":
					break;
				case "point":
					break;
				default:
					break;
			}
			break;
		case "line":
			switch(typeof b)
			{
				case "circle":
					break;
				case "polygon":
					break;
				case "line":
					return lineLine(a.x, a.y, a.x2, a.y2, b.x, b.y, b.x2, b.y2);
					break;
				case "ellipse":
					break;
				case "rectangle":
					break;
				case "point":
					break;
				default:
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
				case "rectangle":
					break;
				case "point":
					break;
				default:
					break;
			}
			break;
		case "rectangle":
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
				case "rectangle":
					break;
				case "point":
					break;
				default:
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
					if(a.x >= b.lx && a.x <= b.ux && a.y >= b.ly && a.y <= b.uy)
					{
						//TODO: Precise point in polygon
					} else return false;
					break;
				case "line":
					break;
				case "ellipse":
					break;
				case "rectangle":
					break;
				case "point":
					return (a.x == b.x && a.y == b.y);
					break;
				default:
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

