# **XYG Tutorials**



&nbsp;

----

## **==== Table of Contents ====**

----

* [Introduction](#intro)
* [Hello World](#helloWorld)
* [Main Loop](#mainLoop)
* [Multiple Files](#multiFile)



&nbsp;

----

## <a name="intro"></a>**==== Introduction ====**

----

At the time of this writing, XYG is just a simple runtime that only works with one file: test.nut. All your game's code will be put in there for the time being. Later updates will allow XYG to execute precompiled .sq files.



&nbsp;

----

## <a name="helloWorld"></a>**==== Hello World ====**

----

To begin, we are going to load an image and put it on the screen. Unlike other languages, Squirrel does not require code to be in a `main()` function like other C-like languages do, but if you feel it's cleaner, feel free to use one.

Let's start by making a variable to store our image in.

```
local image;
```

In Squirrel, `local` is the keyword used to declare a new variable. We can then assign this variable to any value we want, and even change the type of value at any time. For `image`, we will store a loaded image.

```
local image;
image = loadImage("res/background.png");
```

We're assuming here that your `background.png` file is in a folder called `res` for resources. It's good practice to keep your resources in a separate file so your main, or root, folder does not get cluttered.

We can also assign a value to `image` as soon as it's declared, like so:

```
local image = loadImage("res/background.png");
```

You may be wondering why the file path for background.png uses a forward slash instead of a backslash. Windows is the only OS that uses backslashes for its paths, but it is also compatible with forward slashes, and other operating systems will usually only support forward, so it's best to always use them.

When you call the function `loadImage()`, it *returns* a value, meaning that the point where it was called becomes a value. For instance, if you typed `local x = mouseX();`, and the X position of the mouse was 42, it would be as though the code had been written `local x = 42;`. The semicolon at the end of each line says that the statement has ended and the system can move onto the next piece of code. Some languages will allow a line break to do the same, but if a language supports semicolons, then it's safer to use them. Currently, `image` has been assigned to a number, which is the number of background.png's index in XYG's memory. The image data itself is not stored in the variable. The reason why we don't store actual image data in the variable is so that muliple variables with the same value will not store copies of the image for each one.

Now that we have the image loaded, we can draw it to the screen. The function to do this is `drawImage()`. However, just calling this function will not make the window show the image. We need to call `update()` to make the screen refresh and show its contents. Add these two lines to the end:

```
drawImage(image, 0, 0);
update();
```

Run this code, and what do you see? It just blinked in and out, right? That's because computers take *everything* literally. It loaded the image, drew it, put it on screen, and said "I'm done," and quit. We have to tell it to keep the image up for a while. After `update()`, we use `wait()` to keep things as they are for a while. `wait()` counts how long it should wait in miliseconds, so to wait for a full second, we use a value of 1000. Our code should look like this now:

```
local image = loadImage("res/background.png");
drawImage(image, 0, 0);
update();
wait(1000);
```

And now you've written your first program in XYG! Yeah, it's not that much, but we'll be making more in later tutorials.



&nbsp;

----

## <a name="mainLoop"></a>**==== Main Loop ====**

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



&nbsp;

----

## <a name="multiFile"></a>**==== Multiple Files ====**

----

In previous tutorials, we've been using the `local` keyword to declare variables, but this comes with a limitation: whenever your program goes out of scope, locals are deleted. Normally, this means every time you leave a pair of curly braces, such as variables you'd find contained within a function, but in Squirrel, this also means the end of a file. If your program is all in one file, this isn't an issue, but for larger, more complex programs, having multiple files can help keep your code organized and easier to navigate.

To make a variable persistent between files, you'll have to declare it as a global. To do this, we'll be using the insert operator `<-`. This can be used to insert variables into a scope from outside, ensuring they go where you want them to. For now, we'll be using them to delcare top-level variables as global so they won't disappear when Brux is done reading the file.

Rewrite your script so it looks like this:

```
::image <- loadImage("res/background.png");
::quit <- false;

while(!quit){
	drawImage(image, 0, 0);

	if(keyPress(k_escape)) quit = true;

	update();
	wait(10);
};
```

The double colon `::` is used to specify a scope you want to work with. With nothing before it, it points to the global scope, which is what we'll be focusing on.

If this operator seems a little strange to you, it exists for a special purpose. You see, `=` expects the operand on the left to already exist, whereas `<-` allows you to assign to something that doesn't yet exist. If you were to try `::var = num` without `var` already existing, you'd get an error.

So how do we make Brux run multiple files? Let's make our file structure and find out. In your project's folder, create a subfolder called `src`, and put in empty files for game to run with. Here's our directory layout:

```
[project]
	game.nut
	[src]
		main.nut
		images.nut
	[res]
		background.png
```

`game.nut` is going to be the project's core file. It's the one you'll call Brux to run. Inside, it will be a list of `donut()` calls. `donut()` takes the filename of a `.nut`, `.sq`, or `.brx` file and attempts to run it. Put this code into `game.nut`:

```
donut("src/images.nut");
donut("src/main.nut");

main();
```

The list of `donut()` calls will run every source file in your project. Since they're declaring everything as globals, those declarations will remain in Squirrel's memory until Brux itself closes.

It should be noted that Brux's working directory does not change when you use `donut()`, so you should reference files as you would reach them from your project's root folder, unless you happen to change the working directory manually. So if you had, for instance, a file like `src/images.nut` load a file for sprites in the same folder, you would still call `src/sprites.nut` instead of `sprites.nut`, despite it being in the same folder.

In `src/main.nut`, you'll put this code:

```
::quit <- false;

::main <- function(){
	while(!quit){
		drawImage(image, 0, 0);

		if(keyPress(k_escape)) quit = true;

		update();
		wait(10);
	};
};
```

Functions and classes don't necessarily need the same declaration method as global variables, but it's a good habit to get into to make it clear they're global.

In `src/images.nut`, put this code:

```
::image <- loadImage("res/background.png");
```

Now, with a separate file for loading your images in, you won't have to scroll past that list every time you go to edit your main function.

Remember, the order in which you call `donut()` is very important. If something depends on something else, the thing it depends on should be called first. `images.nut` doesn't reference anything in `main.nut`, so it can be called first.



&nbsp;

----

## <a name="sprites"></a>**==== Sprites ====**

----

Previously, we were loading a whole image and drawing it to the screen, but what if we want something animated? An array of images would be annoying to work with (though technically doable, and even preferable in some rare cases), but the best way to handle this is a sprite.

A sprite is simply an image consisting of multiple frames used to represent an object or character in cyberspace. The image file that stores a sprites frames is the sprite sheet.