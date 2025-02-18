# **==== Sprites ====**

----

Previously, we were loading a whole image and drawing it to the screen, but what if we want something animated? An array of images would be annoying to work with (though technically doable, and even preferable in some rare cases), but the best way to handle this is a sprite.

A sprite is simply an image consisting of multiple frames used to represent an object or character in cyberspace. The image file that stores a sprites frames is the sprite sheet.

Let's look back on our project's file structure:

```
[project]
	game.brx
	[src]
		main.nut
		assets.nut
	[res]
		ocean.png
		midi.png
```

In `assets.nut`, we're going to load a sprite. Add this call to `newSprite()` into the file:

```
::bgOcean <- loadImage("res/ocean.png");
::sprMidi <- newSprite("res/midi.png", 32, 32, 0, 0, 16, 16)
```

Notice how `ocean` was changed to `bgOcean`? It's a good idea to name your variables in a way that makes their type more easily identified.

The first argument to this function is the file itself. The second and third are the sprite's dimensions. Since Midi fits into a 32x32 pixel square, both are 32. The next two are for the margin, how far the grid starts from the top-left corner, and padding, the space in pixels between frames. These are useful for sheets that include lines drawn between frames. The last two are the X and Y pivots, the point around which the sprite will be flipped, rotated, and/or scaled when transformed, as well as its offset when being drawn. A good way to decide the X value is where the character's feet most often touch the ground, and the Y value is usally best placed at the center or bottom, but different sprites can call for different values.