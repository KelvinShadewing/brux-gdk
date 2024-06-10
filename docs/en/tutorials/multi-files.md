# **==== Multiple Files ====**

----

In previous tutorials, we've been using the `local` keyword to declare variables, but this comes with a limitation: whenever your program goes out of scope, locals are deleted. Normally, this means every time you leave a pair of curly braces, such as variables you'd find contained within a function, but in Squirrel, this also means the end of a file. If your program is all in one file, this isn't an issue, but for larger, more complex programs, having multiple files can help keep your code organized and easier to navigate.

To make a variable persistent between files, you'll have to declare it as a global. To do this, we'll be using the insert operator `<-`. This can be used to insert variables into a scope from outside, ensuring they go where you want them to. For now, we'll be using them to delcare top-level variables as global so they won't disappear when Brux is done reading the file.

Rewrite your script so it looks like this:

```
::ocean <- loadImage("res/ocean.png");

while(!getQuit()){
	drawImage(ocean, 0, 0);

	update();
};
```

The double colon `::` is used to specify a scope you want to work with. With nothing before it, it points to the global scope, which is what we'll be focusing on.

If this operator seems a little strange to you, it exists for a special purpose. You see, `=` expects the operand on the left to already exist, whereas `<-` allows you to assign to something that doesn't yet exist. If you were to try `::var = num` without `var` already existing, you'd get an error.

So how do we make Brux run multiple files? Let's make our file structure and find out. In your project's folder, create a subfolder called `src`, and put in empty files for game to run with. Here's our directory layout:

```
[project]
	game.brx
	[src]
		main.nut
		assets.nut
	[res]
		midi.png
```

`game.nut` is going to be the project's core file. It's the one you'll call Brux to run. Inside, it will be a list of `donut()` calls. `donut()` takes the filename of a `.nut`, `.sq`, or `.brx` file and attempts to run it. Put this code into `game.brx`:

```
donut("src/assets.nut");
donut("src/main.nut");

main();
```

The list of `donut()` calls will run every source file in your project. Since they're declaring everything as globals, those declarations will remain in Squirrel's memory until Brux itself closes.

It should be noted that Brux's working directory does not change when you use `donut()`, so you should reference files as you would reach them from your project's root folder, unless you happen to change the working directory manually. So if you had, for instance, a file like `src/assets.nut` load a file for sprites in the same folder, you would still call `src/sprites.nut` instead of `sprites.nut`, despite it being in the same folder.

In `src/main.nut`, you'll put this code:

```
::main <- function(){
	while(!getQuit()){
		drawImage(ocean, 0, 0);

		update();
	};
};
```

Functions and classes don't necessarily need the same declaration method as global variables, but it's a good habit to get into to make it clear they're global.

In `src/assets.nut`, put this code:

```
::ocean <- loadImage("res/ocean.png");
```

Now, with a separate file for loading your images in, you won't have to scroll past that list every time you go to edit your main function.

Remember, the order in which you call `donut()` is very important. If something depends on something else, the thing it depends on should be called first. `assets.nut` doesn't reference anything in `main.nut`, so it can be called first.

## require()

`donut()` is usually good enough for running scripts, but it has one quirk to it: if the file you run produces an error, the game will still attempt to run. This can be difficult to debug, as it can lead to a cascade of errors down the line for you to sift through. This is why we have the `require()` function. It works just like `donut()`, but if it encounters an error in the file, the whole game will quit immediately so that the most recent error is from that file.

Open `game.brx` and replace all `donut()` calls with `require()`, like so:

```
require("src/assets.nut");
require("src/main.nut");

main();
```