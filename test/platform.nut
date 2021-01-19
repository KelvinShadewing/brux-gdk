///////////////////
// PLATFORM TEST //
///////////////////

setResolution(320, 180);

ball <-
{
	x = 120.0,
	y = 0.0,
	hspeed = 0.0,
	vspeed = 1.0,
	r = 8,
	c = 30
};

boxes <-
[
	{
		x = 100,
		y = 72,
		w = 140,
		h = 48
	},
	{
		x = 160,
		y = 128,
		w = 200,
		h = 8
	},
	{
		x = 64,
		y = 168,
		w = 80,
		h = 8
	},
	{
		x = 264,
		y = 168,
		w = 96,
		h = 8
	},
	{
		x = 220,
		y = 50,
		w = 16,
		h = 100
	}
];

quit <- false;

placeFree <- function(x, y, r)
{
	//Check ball against each box
	foreach(i in boxes)
	{
		local hx = x;
		local hy = y;

		if(x < i.x - (i.w / 2)) hx = i.x - (i.w / 2);
		else if(x > i.x + (i.w / 2)) hx = i.x + (i.w / 2);
		else hx = x;

		if(y < i.y - (i.h / 2)) hy = i.y - (i.h / 2);
		else if(y > i.y + (i.h / 2)) hy = i.y + (i.h / 2);
		else hy = y;

		if(distance2(x, y, hx, hy) <= r) return false;
	};
	return true;
};

while(!quit)
{
	//Ball physics
	//If ball is in air
	if(placeFree(ball.x, ball.y + 1.0, ball.r))
	{
		ball.vspeed += 0.4;
		ball.c--;
	}
	else
	{ //On ground
		ball.vspeed = 0.0;
		ball.c = 10;
	}

	if(ball.vspeed < 0 && !placeFree(ball.x, ball.y - 1, ball.r)) ball.vspeed = 0;
	//Press jump
	if(keyPress(k_space) && (!placeFree(ball.x, ball.y + 1, ball.r) || ball.c > 0))
	{
		ball.vspeed = -4.0;
		ball.c = 0;
	}

	//Wall jump
	if(placeFree(ball.x, ball.y + 1, ball.r) && keyDown(k_space))
	{
		if(keyPress(k_left) && !placeFree(ball.x + 1, ball.y, ball.r)) //Right wall
		{
			ball.vspeed = -4;
			ball.hspeed = -4;
		}

		if(keyPress(k_right) && !placeFree(ball.x - 1, ball.y, ball.r)) //Left wall
		{
			ball.vspeed = -4;
			ball.hspeed = 4;
		}
	}

	if(ball.hspeed != 0) for(local i = 0; i < abs(floor(ball.hspeed)); i++)
	{
		if(placeFree(ball.x + (ball.hspeed / abs(ball.hspeed)), ball.y, ball.r))
		{
			ball.x += (ball.hspeed / abs(ball.hspeed));
			ball.x = wrap(ball.x, 0, 320);
		}
		else if(placeFree(ball.x + (ball.hspeed / abs(ball.hspeed)), ball.y - 1, ball.r))
		{
			ball.x += (ball.hspeed / abs(ball.hspeed));
			ball.y -= 1;
			ball.x = wrap(ball.x, 0, 320);
		}
		else
		{
			if(ball.hspeed != 0) ball.hspeed -= (ball.hspeed / abs(ball.hspeed));
			break;
		}
	}

	if(ball.vspeed != 0) for(local i = 0; i < abs(floor(ball.vspeed)); i++)
	{
		if(placeFree(ball.x, ball.y + (ball.vspeed / abs(ball.vspeed)), ball.r))
		{
			ball.y += (ball.vspeed / abs(ball.vspeed));
			if(ball.y > 180) ball.y = wrap(ball.y, 0, 180);
		}
		else break;
	}

	if(keyDown(k_left) && ball.hspeed > -4) ball.hspeed -= 0.8;
	if(keyDown(k_right) && ball.hspeed < 4) ball.hspeed += 0.8;
	if(ball.hspeed > 0) ball.hspeed -= 0.3;
	if(ball.hspeed < 0) ball.hspeed += 0.3;
	if(abs(ball.hspeed) < 0.3) ball.hspeed = 0.0;
	if(ball.vspeed > 16) ball.vspeed = 8;

	//Basic stuff
	setDrawColor(0xd0ff);
	drawCircle(ball.x, ball.y, ball.r, true);
	setDrawColor(0x6020ff);
	foreach(i in boxes)
	{
		drawRect(i.x - (i.w / 2), i.y - (i.h / 2), i.w, i.h, true);
	}

	if(keyPress(k_escape)) quit = true;
	update();
}