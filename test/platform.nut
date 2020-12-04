///////////////////
// PLATFORM TEST //
///////////////////

ball <-
{
	x = 120.0,
	y = 0.0,
	hspeed = 0.0,
	vspeed = 1.0,
	r = 8
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

print(placeFree(ball.x, ball.y, ball.r));

while(!quit)
{
	//Ball physics
	if(placeFree(ball.x, ball.y + 1.0, ball.r)) ball.vspeed += 0.5;
	else ball.vspeed = 0.0;

	if(ball.vspeed < 0 && !placeFree(ball.x, ball.y - 1, ball.r)) ball.vspeed = 0;
	if(keyPress(k_space) && !placeFree(ball.x, ball.y + 1, ball.r)) ball.vspeed = -8.0;

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
			ball.y = wrap(ball.y, 0, 320);
		}
		else break;
	}
	if(keyDown(k_left)) ball.hspeed -= 0.5;
	if(keyDown(k_right)) ball.hspeed += 0.5;
	if(ball.hspeed > 0) ball.hspeed -= 0.25;
	if(ball.hspeed < 0) ball.hspeed += 0.25;
	if(ball.vspeed > 16) ball.vspeed = 8;
	

	//Basic stuff
	setDrawColor(0xd0ff);
	drawCircle(ball.x, ball.y, ball.r, true);
	setDrawColor(0x8020ff);
	foreach(i in boxes)
	{
		drawRect(i.x - (i.w / 2), i.y - (i.h / 2), i.w, i.h, true);
	}

	if(keyPress(k_escape)) quit = true;
	update();
}