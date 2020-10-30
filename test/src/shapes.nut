////////////
// SHAPES //
////////////

enum sh
{
	cir,
	rec,
	lin,
	pol,
	bod
}

::Point <- class
{
	x = 0;
	y = 0;
}

::Shape <- class //Base class for all shapes
{
	x = 0.0;
	y = 0.0;

	//These points are used for polygonal math
	pd = []; //Point defaults
	pc = []; //Point current

	t = 0;
	r = 0;
	a = 0;

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

	function updatePoints()
	{

	}

	function setPos(_x, _y, _a)
	{
		x = _x;
		y = _y;
		a = _a;
		updatePoints();
	}

	function modPos(_x, _y, _a)
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
}

::Circle <- class extends Shape
{
	r = 0.0;
	constructor(_x, _y, _r)
}