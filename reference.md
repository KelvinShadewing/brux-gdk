# <center>**XYG Scripting Reference Manual**</center>



&nbsp;

----

## <center>**==== Table of Contents====**</center>

----

* [Main](#main)
* [Graphics](#graphics)
* [Sprites](#sprites)
* [Input](#input)
* [Maths](#maths)
* [Geometry](#geometry)
* [TMX Maps](#tmx)
* [Constants](#constants)

  >>*Notice:* Any function with a double bar in front of its name, like this box, has not yet been implemented/completed, and cannot be used in scripts.



&nbsp;

----

## <a name="main"></a><center>**==== Main ====**</center>

----

* <a name="include"></a>**`include( lib );`**

  Includes a standard XYG library.

* <a name="update"></a>**`update();`**

  Updates screen and input.

* <a name="fileExists"></a>**`fileExists( name );`**

  Checks if a file exists. Returns bool.

* <a name="getOS"></a>**`getOS();`**

  Checks what OS the app is running on. Returns a string.

* <a name="wait"></a>**`wait( ticks );`**

  Waits for `ticks` number of ticks/miliseconds.

* >><a name="donut"></a>**`donut( file );`**

  Loads and runs a script file local to the current game. If ".nut" is not included in the file name given, it will add it automatically.



&nbsp;

----

## <a name="graphics"></a><center>**==== Graphics ====**</center>

----

* <a name="clearScreen"></a>**`clearScreen();`**

  Fills the screen with the set background color.

* <a name="setDrawTarget"></a>**`setDrawTarget( image );`**

  Set an image to be drawn to when using drawing functions. When set to 0, it draws directly to the screen.

* <a name="drawImage"></a>**`drawImage( image, x, y );`**

  Draws a full image at `x`,`y`.

* <a name="setDrawColor"></a>**`setDrawColor( color );`**

  Sets color used in vector and text rendering. If a 24-bit number is used (0xRRGGBB), it will assume full alpha. Different alpha values can be used by setting `color` to a 32-bit number (0xRRGGBBAA).

* <a name="updateScreen"></a>**`updateScreen();`**

  Updates the screen without updating keyboard input.

* <a name="drawRec"></a>**`drawRec( x, y, width, height, solid );`**

  Draws a simple rectangle. If `solid` is true, it will be filled.

* <a name="setBackgroundColor"></a>**`setBackgroundColor( color );`**

  Sets the color used when [`clearScreen()`](#clearScreen) is called.

* <a name="loadImage"></a>**`loadImage( file );`**

  Loads an image and then returns the number for that image.

* <a name="loadImageKeyed"></a>**`loadImageKeyed( file, color );`**

  Same as above, but if an image does not have a transparent background, this can be used to set a color to be made transparent.

* <a name="setScalingFilter"></a>**`setScalingFilter( bool );`**

  If set to true, pixels will be softened when the window is stretched, otherwise, they will remain sharp.

* >><a name="setBlendMode"></a>**`setBlendMode( mode );`**

  Changes how images are blended when drawing. The default is `bm_norm`, which draws things normally. `bm_add` will add an images pixel color values to where it is drawn, and `bm_sub` will do the opposite. `bm_mult` will multiply the value of a color, with 128 causing no change, 255 bringing any value to full brightness, and 0 bringing any value to black.

* >><a name="setFPS"></a>**`setFPS( max, skip, strict );`**

  Sets a range for frames per second. `max` is the highest FPS allowed. XYG will wait if the time between frames is too short to keep the game at a reasonable pace. `skip` is the time between frames allowed before the next one is not drawn. During a skipped frame, no drawing functions aimed at te screen (draw target 0) will be run, and the screen will not be updated. If `strict` is set to true, then *all* drawing functions will be ignored until the speed picks back up. Be careful, as some games may need other surfaces to be updated constantly, such as when lighting up the explored portions of a map.

* >><a name="getFPS"></a>**`getFPS();`**

  Returns the FPS determined by the time it took between the most recent update and the one before it. This is the absolute FPS value, and drawing it on screen will probably look very jittery depending on your game, so it's advisable to make a function that tracks the average or can transition smoothly.



&nbsp;

----

## <a name="sprites"></a><center>**==== Sprites ====**</center>

----

* <a name="newSprite"></a>**`newSprite( file, width, height, margin, padding, pivotX, pivotY, frames );`**

  Creates a new sprite from a grid of frames in an image file. The filename for a sprite is stored internally for use with TMX maps.

  `margin` is the distance between the frames and edges of the image, and `padding` is the space between frames. If [`setScalingFilter()`](#setScalingFilter) has been set to true, a margin and padding of at least 1 should be used to prevent frame bleeding.

  `pivotX` and `pivotY` are the points around which the sprite is rotated and offsets where it will appear when drawn. Margin and padding are not taken into account with these; it only applies to the frame itself.

  If `frames` is set to 0, then all cells of the grid will be used. If the sprite does not fit every possible cell in the grid, then it is best to set this value to the total number of frames.

* <a name="drawSprite"></a>**`drawSprite( sprite, frame, x, y );`**

  Draws a given frame of a sprite to `x`,`y`. If a value above the sprite's maximum frame number or below zero is given, then the value will wrap around.

* <a name="drawSpriteEx"></a>**`drawSpriteEx( sprite, frame, x, y, angle, flip, xscale, yscale, alpha );`**

  Draws a sprite that is also transformed and blended with the given `alpha` value.

* >><a name="deleteSprite"></a>**`deleteSprite( sprite );`**

  Deletes a sprite from memory. If a new sprite is made afterwards, the index of a deleted sprite will be recycled to save memory. Be careful when creating new sprites, as any pointers to the deleted sprite will now point to that one.



&nbsp;

----

## <a name="input"></a><center>**==== Input ====**</center>

----

* <a name="keyDown"></a>**`keyDown( key );`**

  Returns whether or not `key` is currently held.

* <a name="keyPress"></a>**`keyPress( key );`**

  Returns whether or not `key` was just pressed.

* <a name="keyRelease"></a>**`keyRelease( key );`**

  Returns whether or not `key` was just released.

* <a name="mouseX"></a>**`mouseX();`**

  Returns the X coordinate of the mouse.

* <a name="mouseY"></a>**`mouseY();`**

  Returns the Y coordinate of the mouse.

* >><a name="mouseDown"></a>**`mouseDown( button );`**

  Returns whether a given mouse button is currently held. Unlike with key input, mouse input does not use constants because he mouse has only a few buttons.

* >><a name="mousePress"></a>**`mousePress( button );`**

  Returns whether a given mouse button was just pressed.

* >><a name="mouseRelease"></a>**`mouseRelease( button );`**

  Returns whether a given mouse button was just released.



&nbsp;

----

## <a name="maths"></a><center>**==== Maths ====**</center>

----

* <a name="randInt"></a>**`randInt( max );`**

  Returns a random integer between 0 and `max`.

* <a name="randFloat"></a>**`randFloat( max );`**

  Returns a random float between 0 and `max`.

* >><a name="lendirX"></a>**`lendirX( distance, direction );`**

  Returns the X coordinate of a vector.

* >><a name="lendirY"></a>**`lendirY( distance, direction );`**

  Returns the Y coordinate of a vector.

* <a name="distance2"></a>**`distance2( x1, y1, x2, y2 );`**

  Returns the distance between two points in two-dimensional space.

* >><a name="distance3"></a>**`distance3( x1, y1, z1, x2, y2, z2 );`**

  Returns the distance between two points in three-dimensional space.

* <a name="wrap"></a>**`wrap( num, low, high );`**

  Takes `num` and wraps it around so that it is in between `low` and `high`, then returns it as an integer. (C++ does not allow modulus on floating points.)



&nbsp;

----

## <a name="geometry"></a><center>**==== Geometry ====**</center>

----

* >><a name="newLine"></a> **`newLine( x1, y1, x2, y2 );`**

  Creates a new line and returns its number.

* >><a name="newCircle"></a>**`newCircle( x, y, radius );`**

  Creates a new circle and returns its number. Circles cannot have angles applied to them.

* >><a name="newRectangle"></a>**`newRectangle( x, y, width, height, angle );`**

  Creates a new rectangle and returns its number. Because this rectangle can be rotated, its origin will be its center, unlike the top-left corner used in [`drawRec()`](#drawRec).

* >><a name="newTriangle"></a>**`newTriangle( x, y, p1, p2, p3, angle );`**

  Creates a new triangle and returns its number. `p1`, `p2`, and `p3` are the distance of each point from the center. This allows the triangle to have a definite point it can rotate from. At 0 `angle`, the triangle will point up.

* >><a name="newTriAlt"></a>**`newTriAlt( x1, y1, x2, y2, x3, y3 );`**

  Creates a triangle using point coordinates instead of distances. Pivot point will be calculated automatically.

* >><a name="newKite"></a>**`newKite( x, y, width, height );`**

  Creates a kite(/diamond/rhombus) and returns its number.

* >><a name="newPolygon"></a>**`newPolygon( x, y, radius, sides, angle );`**

  Creates a regular polygon with `sides` number of sides, ranging between 3 and 16. Can be rotated, despite using a radius system like circle does. Note that more sides will make it take longer to compute, so it may be best to use a circle if you plan on having more than 8 sides.

* >><a name="startNewBody"></a>**`startNewBody( x, y );`**

  Creates a compound shape. All new shapes created will be made inside the body shape until [`endNewBody()`](#endNewBody) is called. When a body is rotated, all its subshapes will be rotated as well, and will orbit the pivot of the body. `x` and `y` define the body's position in the world; all new shapes will offset their positions around the body's coordinates.

  The function will fail if another new body is already in progress.

* >><a name="endNewBody"></a>**`endNewBody();`**

  Stops building new shapes to the last body created. Returns the number of the body for use. Bodies cannot be scaled.

* >><a name="shapeRot"></a>**`shapeRot( shape, angle );`**

  Sets the angle of a given shape. If the shape is a dot, its coordinates will be rotated around `(0,0)`. Has no effect on circles.

* >><a name="shapePos"></a>**`shapePos( shape, x, y );`**

  Sets the position of a shape.

* >><a name="getShapeX"></a>**`getShapeX( shape );`**

  Returns the X coordinate of a shape.

* >><a name="getShapeY"></a>**`getShapeY( shape );`**

  Returns the Y coordinate of a shape.

* >><a name="shapeSize"></a>**`shapeSize( shape, width, height );`**

  Sets the dimensions of a shape. Does not work on bodies. If used on a circle or polygon, `width` will act as radius. `height` is ignored by circles, and used to change the number of sides for a polygon.

* >><a name="hitTest"></a>**`hitTest( a, b );`**

  Checks for a collision between two shapes. Returns true or false.



&nbsp;

----

## <a name="tmx"></a><center>**==== TMX Maps ====**</center>

----

* >><a name="loadMap"></a>**`loadMap( file );`**

  Loads a .TMX file and returns the index. Each tileset must have a sprite with matching filename loaded already, otherwise no tiles from that set will be drawn. Regular images won't work because they lack the necessary meta data needed by the TMX engine.

* >><a name="gotoMap"></a>**`gotoMap( map );`**

  Changes the active map to `map`. All functions asking for layers will use the active map. The previous actve map will remain in memory until deleted. Things like player positions will need to be  altered manually.

* >><a name="newBodyFromMap"></a>**`newBodyFromMap( layer );`**

  Creates a new body and returns its index. Produces an error if used between [`startNewBody()`](#startNewBody) and [`endNewBody()`](#endNewBody).

* >><a name="drawMap"></a>**`drawMap( layer, x, y );`**

  Draws a layer from the active map to the target surface. If the layer does not exist, nothing will be drawn. For faster rendering, it may be a good idea to keep a small cache of surfaces and draw each layer of your active map on to each surface, and then just draw the whole surface, since `drawMap()` has to go through every individual tile on the layer. `x` and `y` are the offset to draw.

* >><a name="drawMapRegion"></a>**`drawMapRegion( layer, x, y, rx, ry, rw, rh );`**

  Draws just part of a layer. Only tiles intersecting the region will be drawn. Unlike with XYG's collision system, the `rx` and `ry` coordinates mark the top-left corner of the region.

* >><a name="deleteMap"></a>**`deleteMap( map );`**

  Deletes a map from memory. Resources made using the map will not be automatically cleaned up.



&nbsp;

----

## <a name="constants"></a><center>**==== Constants ====**</center>

----

  >A full list of constants can be found in core.nut.

* <a name="conBinary"></a>**Binary**

  To reference a single bit based on its place value, simply prefix a number 1-32 with an underscore. For instance, if you wanted to reference the fourth bit, which has a value of 8, you would simply type `_4`. You can mix bits together with a binary or operator: `|`. For example, to use the first and third bit, you would type `_1 | _3`.

* <a name="conKeys"></a>**Keycodes**

  Constants for keys are assigned to their code on the keyboard. Every key you see (and some you don't) has its own number, and there are over 200 possible  codes for them. For a full list of these keys, check out libxyg.nut, but for commonly-used keys, use the following:

  `k_a` through `k_z` for letters and `k_0` through `k_9` for the top-row numbers. For numpad keys, use `k_num0` through `k_num9`. Function keys use `k_f1` through `k_f24` (though most keyboards only go up to F12).

  Commonly-used special keys include:
  * `k_enter`
  * `k_space`
  * `k_lshift`
  * `k_rshift`
  * `k_lcontrol`
  * `k_rcontrol`
  * `k_lalt`
  * `k_ralt`
  * `k_pgup`
  * `k_pgdn`
  * `k_home`
  * `k_end`