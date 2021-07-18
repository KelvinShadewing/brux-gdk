::sprMidi <- newSprite("res/sprMidiP.png", 32, 32, 0, 0, 16, 16, 0)
::sprFont <- newSprite("res/font.png", 6, 8, 0, 0, 0, 0, 0)
::font <- newFont(sprFont, 0, 0, 0, 0)

while(!getQuit()) {
	for(local i = 0; i <= getFrames(); i++) {
		drawSprite(sprMidi, randInt(256), randInt(320), randInt(240))
		if(getFrames() > 0) local blah = abs(getTicks()) / abs(getFrames())
	}
	drawText(font, 0, 0, "FPS: " + getFPS() + "\nSprites: " + getFrames())
	update()
}