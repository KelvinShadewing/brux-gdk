setFPS(60)

setResolution(424, 240)

tex <- newTexture(320, 240)
land <- newSprite("res/terrain.png", 800, 800, 0, 0, 400, 400)
midi <- newSprite("res/midi.png", 32, 32, 0, 0, 16, 32)
ocean <- newSprite("res/ocean.png", 480, 240, 0, 0, 240, 120)
view <- newSpriteFT(tex, 3200, 1, 0, 0, 1600, 0)
sprFont <- newSprite("res/font.png", 6, 8, 0, 0, 0, 0)
font <- newFont(sprFont, 0, 0, false, 0)

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
	drawSprite(ocean, 0, 212, 72)
	for(local i = 0.0; i < 120; i++) drawSpriteEx(view, i, 212, i * (i * 0.02) + 78, 0, 0, 0.2 + ((0.2 / 120.0) * (i * (i * 0.01))), (2.0 / 48.0) * (i * (i * 0.1)), 1)
	drawText(font, 0, 0, "FPS: " + getFPS())

	update()
}