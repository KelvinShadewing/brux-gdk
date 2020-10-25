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

::Shape <- class
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

	constructor(_x, _y, _type, w = 1, h = 1, _a = 0)
	{
		x = _x;
		y = _y;
		a = _a;
		t = _type;

		switch(_type)
		{
			case sh.cir:
				r = w;
				break;
			case sh.rec:
				p.push(Point(-w / 2, -h / 2));
				p.push(Point(-w / 2, h / 2));
				p.push(Point(w / 2, h / 2));
				p.push(Point(w / 2, -h / 2));
				break;
		}
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
}