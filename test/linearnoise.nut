setResolution(1280, 720)

::hillY <- 240
::surface <- newTexture(screenW(), screenH())
::hillArr <- null
::caveArrPath <- null
::caveArrRadius <- null
::smoothing <- 64
::hillW <- 128
::hillH <- 40
::worldArr <- array(screenW() * screenH(), 0)


::getLimitedNoise <- function(y, limit) { return min(limit, max(-limit, (y + randInt(limit / 2) - randInt(limit)) / 2)) }

::createLine <- function(w, h, s) {
	local newArr = []
	local y = 0
	for(local i = 0; i <= screenW(); i++) {
		y = (w > 0 ? sin(i / w) * 8 : 0) + (y + getLimitedNoise(y, h)) / 2
		if(i == 0) newArr.push(y)
		else {
			newArr.push((y + newArr[i - 1]) / 2)
			newArr[i] = (newArr[i] + newArr[i - 1]) / 2
		}
	}

	for(local i = 0; i < smoothing; i++) {
		for(local j = 1; j < newArr.len(); j++) {
			newArr[j] = (newArr[j] + newArr[j - 1]) / 2
		}
		newArr[0] = (newArr[0] + newArr[newArr.len() - 1]) / 2
	}

	return newArr
}

::updateSurface <- function() {
	setDrawTarget(surface)
	setDrawColor(0xff)
	drawRec(0, 0, screenW(), screenH(), true)

	setDrawColor(0x208040ff)
	
	//Create surface terrain
	hillArr = createLine(hillW, hillH, smoothing)
	for(local i = 1; i <= screenW(); i++) {
		drawLine(i, hillY + hillArr[i], i, screenW())
	}

	//Create caves

	resetDrawTarget()
}

updateSurface()
while(!getQuit()) {
	if(keyPress(k_space)) updateSurface()
	drawImage(surface, 0, 0)
	update()
}