setResolution(320, 180)

::sprTerrain <- newSprite("res/terrain.png", 800, 800, 0, 0, 400, 400)
::sprLight <- newSprite("res/lightball.png", 128, 128, 0, 0, 64, 64)

spriteSetBlendMode(sprLight, bm_add)

::texAmbient <- newTexture(800, 800)

textureSetBlendMode(texAmbient, bm_sub)

setDrawColor(0x204080ff)

while(!keyPress(k_escape) && !getQuit()) {
	setDrawTarget(texAmbient)
	drawRec(0, 0, 800, 800, true)
	drawSprite(sprLight, 0, mouseX(), mouseY())
	drawSprite(sprLight, 0, 160, 90)
	resetDrawTarget()

	drawSprite(sprTerrain, 0, 0, 0)
	drawImage(texAmbient, 0, 0)

	update()
}