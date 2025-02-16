setResolution(426, 240)

::sprMidi <- newSprite("res/midi.png", 32, 32, 0, 0, 16, 16)
::sprFont <- newSprite("res/font.png", 6, 8, 0, 0, 0, 0)
::font <- newFont(sprFont, 0, 0, false, 0)
::frameHistory <- [
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
]
::frameAvg <- 0

while(!getQuit()) {
	frameHistory[getFrames() % frameHistory.len()] = getFPS()
	for(local i = 0; i < frameHistory.len(); i++)
		frameAvg += frameHistory[i]
	frameAvg /= 60

	for(local i = 0; i <= getFrames(); i++) {
		drawSprite(sprMidi, randInt(256), randInt(426), randInt(240))
		if(getFrames() > 0) local blah = abs(getTicks()) / abs(getFrames())
	}
	drawText(font, 0, 0, "FPS: " + frameAvg + "\nSprites: " + getFrames())
	update()
}