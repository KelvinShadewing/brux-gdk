//////////////////
// POLYGON TEST //
//////////////////

donut("src/shapes.nut");
setResolution(320, 180);

quit <- false;


poly <- Polygon(0.0, 0.0, [[140, 120], [160, 112], [180, 120], [168, 132], [132, 140]]);
pmou <- Polygon(0.0, 0.0, [[0.0, 8.0], [-8.0, 0.0], [0.0, -8.0], [8.0, 0.0]]);

while(!quit)
{
	//Hit test
	setDrawColor(0xf80000ff); //No hit
	pmou.setPos(mouseX(), mouseY(), pmou.a);
	pmou.modPos(0, 0, 1.0);
	if(hitPolyPoly(poly, pmou)) setDrawColor(0x00f800ff); //Hit the poly

	//Draw shapes
	poly.draw();
	pmou.draw();
	//print(jsonWrite(pmou.pc));

	//Update
	if(keyPress(k_escape)) quit = true;
	update();
}

print(jsonWrite(pmou.p));
print(jsonWrite(pmou.pc));