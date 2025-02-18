# **==== Main Loop ====**

----

The first lesson showed you how to make an image that stays on the screen for a second, but what if you wanted to leave it up for as long as you wanted and quit only when you told it to quit? For that, we need to have the program check over and over if the user has hit alt-F4 or clicked the [X] button for each frame, and then quit when it sees the key has been pressed.

```
local image = loadImage("res/background.png");
```

Now we will make our main program loop. For this, we are going to use what's called a `while` loop. A `while` takes an argument much like the functions you used before. For each time the loop runs, it will check that argument, and if it's still true, the loop happens, and stops when the argument becomes false. If you were to write `while(true)`, your loop would run forever, since `true` is a constant, and will never change. Move your earlier code into a `while` loop, and use `!getQuit()` as the condition. `!` means "not", and will switch variables between `true` and `false`. It's not quite as simple as that, but that's a good enough explanation for now.

`getQuit()` is a function that checks if the window has been told to close by the system, such as by alt-F4 or when the [X] on the window is clicked.

```
while(!getQuit()){
	drawImage(image, 0, 0);
	update();
};
```

Now our whole program should look like this:

```
local image = loadImage("res/background.png");

while(!getQuit()){
	drawImage(image, 0, 0);

	if(keyPress(k_escape)) quit = true;

	update();
};
```

Run it again. The picture will stay up until you hit alt-F4 or [X] to close it. Remember, you must include `update()` in your main loop. Without it, not only will your program not redraw the screen, it won't listen for keyboard updates, meaning hitting escape won't work.