::sprFont <- newSprite("res/font.png", 6, 8)
::font <- newFont(sprFont, 0, 0, true, 0)
::sprFont2 <- newSprite("res/font2.png", 12, 14)
::font2 <- newFont(sprFont2, 32, 0, true, -4)
::snake <- [[26, 15], [-1, -1], [-1, -1], [-1, -1]]
::snakeDir <- 0 // 0 right, 1 up, 2 left, 3 down
::applex <- randInt(26)
::appley <- randInt(15)
::sprSnake <- newSprite("res/snake.png", 16, 16, 8, 8)
::sprApple <- newSprite("res/apple.png")
::sprBG <- newSprite("res/terrain.png")
::debug <- false

setFPS(60)
setResolution(426, 240)

::gmPlay <- function() {
	//Move snake
	if(getFrames() % max(10 - floor(snake.len() / 8), 1) == 0) {
		//Update tail segments
		for(local i = snake.len() - 1; i > 0; i--) {
			snake[i] = clone(snake[i - 1])
		}

		//Move head
		switch(snakeDir) {
			case 0: //right
				snake[0][0]++
				break
			case 1: //up
				snake[0][1]--
				break
			case 2: //left
				snake[0][0]--
				break
			case 3: //down
				snake[0][1]++
				break
		}

		//Wrap snake around screen
		if(snake[0][0] < 0) snake[0][0] = 25
		if(snake[0][0] > 25) snake[0][0] = 0
		if(snake[0][1] < 0) snake[0][1] = 14
		if(snake[0][1] > 14) snake[0][1] = 0

		//Eat apple
		if(snake[0][0] == applex && snake[0][1] == appley) {
			applex = randInt(26)
			appley = randInt(15)
			snake.push([-1, -1])
		}

		// Check if snake crashed
		for(local i = snake.len() - 1; i > 0; i--) {
			if(i > 1 && snake[0][0] == snake[i][0] && snake[0][1] == snake[i][1])
				gameMode = gmOver
		}
	}

	//Change direction
	if(keyDown(k_left) && snake[0][0] - 1 != snake[1][0])
		snakeDir = 2
	if(keyDown(k_right) && snake[0][0] + 1 != snake[1][0])
		snakeDir = 0
	if(keyDown(k_up) && snake[0][1] - 1 != snake[1][1])
		snakeDir = 1
	if(keyDown(k_down) && snake[0][1] + 1 != snake[1][1])
		snakeDir = 3

	//Draw scene
	for(local i = 0; i < snake.len(); i++)
		drawSprite(sprSnake, i == 0 ? (getFrames() / 10) % 2 : 2, (snake[i][0] * 16) + 8, (snake[i][1] * 16) + 8, i == 0 ? snakeDir * -90 : 0, snakeDir == 2 && i == 0 ? 2 : 0)
	drawSprite(sprApple, 0, applex * 16, appley * 16)
	
	if(debug) {
		local message = "SNAKE POS: (" + snake[0][0] + "," + snake[0][1] + ")"
		message += "\nAPPLE POS: (" + applex + "," + appley + ")"

		drawText(font, 0, 0, message)
	}
}

::gmOver <- function() {
	drawText(font2, 213 - (6 * 4.5), 114, "GAME OVER")

	//Reset game
	if(keyPress(k_space)) {
		snake = [[13, 15], [-1, -1], [-1, -1], [-1, -1]]
		snakeDir = 0 // 0 right, 1 up, 2 left, 3 down
		applex = randInt(26)
		appley = randInt(15)
		gameMode = gmPlay
	}
}

::gameMode <- gmPlay
while(!getQuit()) {
	drawSprite(sprBG, 0, 0, 0)
	if(keyPress(k_f12))
		debug = !debug
	gameMode()
	update()
}