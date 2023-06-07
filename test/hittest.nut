/*========*\
| HIT TEST |
\*========*/

donut("src/shapes.nut");
setResolution(320, 180);

::a <- Line(160, 90, 160, 90);
::b <- Line(64, 64, 256, 64);
::c <- Circle(0, 0, 16);
::d <- Circle(200, 100, 16);
::quit <- false;

while(!quit)
{
	a.x = mouseX();
	a.y = mouseY();
	c.x = mouseX();
	c.y = mouseY();

	if(hitTest(a, b)) setDrawColor(0xff00ff);
	else setDrawColor(0xff0000ff);

	drawLine(a.x, a.y, a.x2, a.y2);
	drawLine(b.x, b.y, b.x2, b.y2);

	if(hitTest(c, d)) setDrawColor(0xff00ff);
	else setDrawColor(0xff0000ff);

	drawCircle(c.x, c.y, c.r, false);
	drawCircle(d.x, d.y, d.r, false);

	if(hitTest(a, d))
	{
		setDrawColor(0xffff);
		drawLine(a.x, a.y, a.x2, a.y2);
		drawCircle(d.x, d.y, d.r, false);
	}

	if(keyPress(k_escape)) quit = true;
	update();
}