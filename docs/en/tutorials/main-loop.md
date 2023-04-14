# **==== Main Loop ====**

----

The first lesson showed you how to make an image that stays on the screen for a second, but what if you wanted to leave it up for as long as you wanted and quit only when you told it to quit? For that, we need to have the program check over and over if the user has hit escape for each frame, and then quit when it sees the key has been pressed. For this, we'll need another variable called `quit`. Add it to the list of variables at the top of your program.

```
local image = loadImage("res/background.png");
local quit = false;
```

Now we will make our main program loop. For this, we are going to use what's called a `while` loop. A `while` takes an argument much like the functions you used before. For each time the loop runs, it will check that argument, and if it's still true, the loop happens, and stops when the argument becomes false. If you were to write `while(true)`, your loop would run forever, since `true` is a constant, and will never change. Move your earlier code into a `while` loop, and use `!quit` as the condition. `!` means "not", and will switch variables between `true` and `false`. It's not quite as simple as that, but that's a good enough explanation for now.

```
while(!quit){
	drawImage(image, 0, 0);
	update();
	wait(10);
};
```

As it is now, this loop will still never quit. We need to fix that. It's time to start using the keyboard!

To check if a key is down, we use `keyDown()`, but if we want to check if a key was just pressed, as opposed to still being held, we use `keyPress()`. Both will work just fine in this situation. The argument it takes is a constant known as a key code. It equals the number used to identify the key on a keyboard. In this case, we use `k_escape`. Add this to the end of your loop.

```
	if(keyPress(k_escape)) quit = true;
```

Now our whole program should look like this:

```
local image = loadImage("res/background.png");
local quit = false;

while(!quit){
	drawImage(image, 0, 0);

	if(keyPress(k_escape)) quit = true;

	update();
	wait(10);
};
```

Run it again. The picture will stay up until you hit escape to close it. Remember, you must include `update()` in your main loop. Without it, not only will your program not redraw the screen, it won't listen for keyboard updates, meaning hitting escape won't work.