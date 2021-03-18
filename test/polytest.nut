//////////////////
// POLYGON TEST //
//////////////////

donut("src/shapes.nut");
setResolution(320, 180);

quit <- false;


poly <- Polygon(0, 0, [[140, 120], [160, 112], [180, 120], [168, 132], [132, 140]]);
pmou <- Polygon(0, 0, [[0, 4], [-4, 0], [0, -4], [4, 0]]);

while(!quit)
{
	//Hit test
	setDrawColor(0xf80000ff); //No hit
	if(mouseX() >= poly.lx && mouseX() <= poly.ux && mouseY() >= poly.ly && mouseY() <= poly.uy) setDrawColor(0xf800f8ff);//Within bounds
	if(hitPointPoly(mouseX(), mouseY(), poly)) setDrawColor(0x00f800ff); //Hit the poly

	//Draw shapes
	poly.draw();
	drawLine(mouseX() - 4, mouseY(), mouseX() + 4, mouseY());
	drawLine(mouseX(), mouseY() - 4, mouseX(), mouseY() + 4);

	//Update
	if(keyPress(k_escape)) quit = true;
	update();
}
