setResolution(426, 240)

::hilly <- 0
::surface <- newTexture(screenW(), screenH())
::hillarr <- null
::smoothing <- 16
::hillw <- 32


::getLimitedNoise <- function(y, limit) { return min(limit, max(-limit, (y + randInt(limit / 2) - randInt(limit)) / 2)) }

::updateSurface <- function() {
	setDrawTarget(surface)
	setDrawColor(0xff)
	drawRec(0, 0, screenW(), screenH(), true)
	hilly = 0

	setDrawColor(0xffffffff)
	hillarr = []
	for(local i = 0; i <= screenW(); i++) {
		hilly = (hillw > 0 ? sin(i / hillw) * 8 : 0) + (hilly + getLimitedNoise(hilly, 128)) / 2
		if(i == 0) hillarr.push(hilly)
		else {
			hillarr.push((hilly + hillarr[i - 1]) / 2)
			hillarr[i] = (hillarr[i] + hillarr[i - 1]) / 2
		}
	}

	for(local i = 0; i < smoothing; i++) {
		for(local j = 1; j < hillarr.len(); j++) {
			hillarr[j] = (hillarr[j] + hillarr[j - 1]) / 2
		}
		hillarr[0] = (hillarr[0] + hillarr[hillarr.len() - 1]) / 2
	}

	for(local i = 1; i <= screenW(); i++) {
		drawLine(i, 120 + hillarr[i], i - 1, 120 + hillarr[i - 1])
	}

	resetDrawTarget()
}

updateSurface()
while(!getQuit()) {
	if(keyPress(k_space)) updateSurface()
	drawImage(surface, 0, 0)
	update()
}