print("Loading images.");
xySetScalingFilter(1);
local img = xyLoadImage("Midi.png");
local spr = xyNewSprite(img, 32, 32, 1, 1, 16, 16, 0);
local x = 64;
local y = 64;
local quit = false;
local angle = 0;
local flip = 0;
local frame = 0;

print("Beginning loop.");
while(!quit){
	//Set angle
	if(xyKeyPress(sc_a)) angle -= 15;
	if(xyKeyPress(sc_d)) angle += 15;

	//Set frame
	if(xyKeyPress(sc_w)) frame += 1;
	if(xyKeyPress(sc_s)) frame -= 1;
	
	//Set position
	x = xyMouseX();
	y = xyMouseY();

	//Draw sprite
	xyDrawSpriteEx(spr, frame, x, y, angle, 0, 2, 2);

	//Exit program
	if(xyKeyPress(sc_escape)){
		quit = true;
		print("User pressed escape.");
	};
	
	//Update screen
	xyWait(10);
	xyUpdate();
};

print("Ending program.");