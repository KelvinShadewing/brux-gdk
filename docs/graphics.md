# <center>**Brux Scripting Reference Manual**</center>
## <center>Graphics</center>



&nbsp;

* <a name="clearScreen"></a>**`clearScreen()`**

  Fills the screen with the set background color.

* <a name="setDrawTarget"></a>**`setDrawTarget( image )`**

  Set an image to be drawn to when using drawing functions. When set to 0, it draws directly to the screen. It can be loaded with `loadImage` or created with `newTexture`.

* <a name="drawImage"></a>**`drawImage( image, x, y )`**

  Draws a full image at `x`,`y`.

* <a name="setDrawColor"></a>**`setDrawColor( color )`**

  Sets color used in vector and text rendering. If a 24-bit number is used (0xRRGGBB), it will assume full alpha. Different alpha values can be used by setting `color` to a 32-bit number (0xRRGGBBAA).

* <a name="drawRec"></a>**`drawRec( x, y, width, height, solid )`**

  Draws a simple rectangle. If `solid` is true, it will be filled.

* <a name="drawCircle"></a>**`drawCircle( x, y, radius, solid )`**

  Draws a circle. If `solid` is true, it will be filled.

* <a name="setBackgroundColor"></a>**`setBackgroundColor( color )`**

  Sets the color used when [`clearScreen()`](#clearScreen) is called.

* <a name="loadImage"></a>**`loadImage( file )`**

  Loads an image and then returns the number for that image.

* <a name="loadImageKeyed"></a>**`loadImageKeyed( file, color )`**

  Same as above, but if an image does not have a transparent background, this can be used to set a color to be made transparent.

* <a name="setScalingFilter"></a>**`setScalingFilter( bool )`**

  If set to true, pixels will be softened when the window is stretched, otherwise, they will remain sharp. This must be set AT THE BEGINNING in order to work properly, as it takes effect when textures are created, not rendered. Padding should also be used in sprites to avoid artifacting.

* <a name="setResolution"></a>**`setResolution( width, height )`**

  Changes the base resolution of the window. In full screen, this may produce a letterbox if the aspect ratio does not match that of the monitor.

* <a name="screenW"></a>**`screenW()`**

  Returns the width of the game's internal resolution.

* <a name="screenH"></a>**`screenH()`**

  Returns the height of the game's internal resolution.

* <a name="displayW"></a>**`displayW()`**

  Returns the width of the hardware's display resolution.

* <a name="displayH"></a>**`displayH()`**

  Returns the height of the hardware's display resolution.

* <a name="newTexture"></a>**`newTexture( width, height )`**

  Creates a new texture that can be used as a render target, and then returns the ID to be used with `setDrawTarget`.

* <a name="drawLine"></a>**`drawLine( x1, y1, x2, y2 )`**

  Draws a line between two points using the color set with `setDrawColor`.

* <a name="drawLineWide"></a>**`drawLine( x1, y1, x2, y2, width )`**

  Draws a line between two points using the color set with `setDrawColor` with a given width.

* <a name="drawPoint"></a>**`drawPoint( x, y )`**

  Draws a point at the given... point.

* <a name="resetDrawTarget"></a>**`resetDrawTarget()`**

  Resets the drawing target to the screen.

* <a name="textureSetBlendMode"></a>**`textureSetBlendMode( texture, mode )`**

  Sets the blend mode for a texture. Supported modes differ by hardware, and fallbacks are determined by SDL.