::lightTrail <- array(32, clone([mouseX(), mouseY()]))

while(!getQuit()) {
	for(local i = 31; i > 0; i--) {
		//Create color
		local r = 255
		local g = max(0, min(255, 128 + (255 - i * 15)))
		local b = max(0, 255 - i * 15)
		setDrawColor((r << 24) | (g << 16) | (b << 8) | max(0, min(255, 255 + (255 - i * 15))))
		drawLineWide(lightTrail[i][0], lightTrail[i][1], lightTrail[i - 1][0], lightTrail[i - 1][1], 4 - (i / 8))
	}
	//Update line coordinates
	for(local i = 31; i > 0; i--) {
		lightTrail[i] = lightTrail[i - 1]
	}
	lightTrail[0] = [mouseX(), mouseY()]
	update()
}