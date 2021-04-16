# <center>**Brux Scripting Reference Manual**</center>
## <center>Graphics</center>



&nbsp;

* <a name="clearScreen"></a>**`clearScreen()`**

  Fills the screen with the set background color.

* <a name="setDrawTarget"></a>**`setDrawTarget( image )`**

  Set an image to be drawn to when using drawing functions. When set to 0, it draws directly to the screen.

* <a name="drawImage"></a>**`drawImage( image, x, y )`**

  Draws a full image at `x`,`y`.

* <a name="setDrawColor"></a>**`setDrawColor( color )`**

  Sets color used in vector and text rendering. If a 24-bit number is used (0xRRGGBB), it will assume full alpha. Different alpha values can be used by setting `color` to a 32-bit number (0xRRGGBBAA).

* <a name="updateScreen"></a>**`updateScreen()`**

  Updates the screen without updating keyboard input.

* <a name="drawRec"></a>**`drawRec( x, y, width, height, solid )`**

  Draws a simple rectangle. If `solid` is true, it will be filled.

* <a name="drawColor"></a>**`drawCircle( x, y, radius, solid )`**

  Draws a circle. If `solid` is true, it will be filled.

* <a name="setBackgroundColor"></a>**`setBackgroundColor( color )`**

  Sets the color used when [`clearScreen()`](#clearScreen) is called.

* <a name="loadImage"></a>**`loadImage( file )`**

  Loads an image and then returns the number for that image.

* <a name="loadImageKeyed"></a>**`loadImageKeyed( file, color )`**

  Same as above, but if an image does not have a transparent background, this can be used to set a color to be made transparent.

* <a name="setScalingFilter"></a>**`setScalingFilter( bool )`**

  If set to true, pixels will be softened when the window is stretched, otherwise, they will remain sharp. This must be set AT THE BEGINNING in order to work properly, as it takes effect when textures are created, not rendered. Padding should also be used in sprites to avoid artifacting.

* >><a name="setBlendMode"></a>**`setBlendMode( mode )`**

  Changes how images are blended when drawing. The default is `bm_norm`, which draws things normally. `bm_add` will add an images pixel color values to where it is drawn, and `bm_sub` will do the opposite. `bm_mult` will multiply the value of a color, with 128 causing no change, 255 bringing any value to full brightness, and 0 bringing any value to black.

* <a name="setFPS"></a>**`setFPS( max, skip, strict )`**

  Sets a range for frames per second. `max` is the highest FPS allowed. XYG will wait if the time between frames is too short to keep the game at a reasonable pace. `skip` is the time between frames allowed before the next one is not drawn. During a skipped frame, no drawing functions aimed at te screen (draw target 0) will be run, and the screen will not be updated. If `strict` is set to true, then *all* drawing functions will be ignored until the speed picks back up. Be careful, as some games may need other surfaces to be updated constantly, such as when lighting up the explored portions of a map.

* <a name="getFPS"></a>**`getFPS()`**

  Returns the FPS determined by the time it took between the most recent update and the one before it. This is the absolute FPS value, and drawing it on screen will probably look very jittery depending on your game, so it's advisable to make a function that tracks the average or can transition smoothly.

* <a name="setWindowTitle"></a>**`setWindowTitle( title )`**

  Changes the title of the window.

* <a name="setResolution"></a>**`setResolution( width, height )`**

  Changes the base resolution of the window. In full screen, this may produce a letterbox if the aspect ratio does not match that of the monitor.
