tex <- newTexture(320, 240)
land <- newSprite("res/terrain.png", 800, 800, 0, 0, 400, 400)
midi <- newSprite("res/sprMidiP.png", 32, 32, 0, 0, 16, 32)
ocean <- newSprite("res/ocean.png", 480, 240, 0, 0, 240, 120)
view <- newSpriteFT(tex, 320, 1, 0, 0, 160, 0)

x <- 320
y <- 120

while(!getQuit()) {
	if(keyDown(k_down)) y--
	if(keyDown(k_up)) y++
	if(keyDown(k_left)) x++
	if(keyDown(k_right)) x--

	setDrawTarget(tex)

	clearScreen()
	drawSprite(land, 0, x, y)

	resetDrawTarget()
	drawSprite(ocean, 0, 160, 120)
	for(local i = 0.0; i < 120; i++) drawSpriteEx(view, i, 160, ((i / 120.0) * i) + 128, 0, 0, 0.25 + (((1.0 / 240.0) * i) * 4.0), (i / 120.0) * i, 1)

	update()
}