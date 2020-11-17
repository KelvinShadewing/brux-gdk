///////////////////
// PLATFORM TEST //
///////////////////

ball <-
{
	x = 120,
	y = 0,
	hspeed = 0,
	vspeed = 0,
	r = 8
}

boxes <-
[
	[100, 64, 140, 72, 0xf80000ff]
]

quit <- false;

while(!quit)
{
	setDrawColor(0x6060ff);
	drawCircle(ball.x, ball.y, ball.r, false);
	if(keyPress(k_escape)) quit = true;
	update();
}