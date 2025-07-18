// Test app for FLOP rendering

::imgTerrain <- loadImage("res/terrain.png");
::sprFont <- newSprite("res/font.png", 6, 8);
::font <- newFont(sprFont, 0, 0, true, 0);

local x = 0;
local y = 0;
local a = 0;
local n = 1;
local f = 1000;
local v = 90;

while(!getQuit()) {
	
	// Draw the terrain with FLOP rendering
	flopDraw(imgTerrain, 0, 0, screenW(), screenH(), x, y, a, n, f, v, 1.0);
	drawText(font, 0, 0, "X: " + x + "\nY: " + y + "\nAngle: " + a + "\nNear: " + n + "\nFar: " + f + "\nFOV: " + v + "\nFPS: " + getFPS());
	
	// Move camera
	if(keyDown(k_left))
		a--;
	if(keyDown(k_right))
		a++;
	if(keyDown(k_up)) {
		x += lendirX(1, a);
		y += lendirY(1, a);
	}
	if(keyDown(k_down)) {
		x -= lendirX(1, a);
		y -= lendirY(1, a);
	}

	//Adjust near and far planes
	if(keyDown(k_q)) {
		n += 1;
		if(n > f - 1) n = f - 1; // Ensure near plane is less than far plane
	}
	if(keyDown(k_a)) {
		n -= 1;
		if(n < 1) n = 1; // Ensure near plane is at least 1
	}
	if(keyDown(k_w)) {
		f += 1;
		if(f > 10000) f = 10000; // Cap far plane distance
	}
	if(keyDown(k_s)) {
		f -= 1;
		if(f <= n) f = n + 1; // Ensure far plane is greater than near plane
	}

	//Adjust field of view
	if(keyDown(k_e)) {
		v += 1;
		if(v > 180) v = 180; // Cap FOV at 180
	}
	if(keyDown(k_d)) {
		v -= 1;
		if(v < 1) v = 1; // Ensure FOV is at least 1
	}
	
	// Render the frame
	update();
}