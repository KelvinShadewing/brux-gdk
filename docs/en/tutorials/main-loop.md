# **==== Main Loop ====**

----

The first lesson showed you how to make an image and show it on the screen with `gameRender`.

`gameRender` is a new feature in Brux GDK, and was created to replace the old convention of creating a loop.

The example code you created in the first lesson would look like this in older versions of Brux GDK:

```
local image = loadImage("res/background.png");

while (!getQuit()) {
	drawImage(image, 0, 0);
	update();
}
```

However, the old loop-based method is now deprecated and the handler function method is used instead.

There are 3 handler functions that you can create:

- gameRender is run on each frame for rendering the game, which you've already used in the first lesson.
- gameUpdate is run on each frame for updating the game's current state (e.g physics updates).
- gameExit is run after the game is closed.

You can run `quitGame()` to exit the game. To demonstrate this, let's make it close when we press the escape key.

To check if a key is down, we use `keyDown()`, but if we want to check if a key was just pressed, as opposed to still being held, we use `keyPress()`. Both will work just fine in this situation. The argument it takes is a constant known as a key code. It equals the number used to identify the key on a keyboard. In this case, we use `k_escape`.

To add this to your game, create a new function named `gameUpdate` with the check in it:

```
::gameUpdate <- function () {
	if (keyPress(k_escape)) {
		quitGame()
	}
}
```

Now run it again. The picture will stay up until you hit escape or press the window close button to close it. Remember, you must include `update()` in your main loop. Without it, not only will your program not redraw the screen, it won't listen for keyboard updates, meaning hitting escape won't work.

Your code should now look like this:

```
local image = loadImage("res/background.png");

::gameRender <- function () {
	drawImage(image, 0, 0);
}

::gameUpdate <- function () {
	if (keyPress(k_escape)) {
		quitGame();
	}
}
```