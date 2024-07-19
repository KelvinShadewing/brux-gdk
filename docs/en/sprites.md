# <center>**Brux Scripting Reference Manual**</center>
## <center>Sprites</center>



&nbsp;

* <a name="newSprite"></a>**`newSprite( file, width = 0, height = 0, pivotX = 0, pivotY = 0, margin = 0, padding = 0 )`**

  Creates a new sprite from a grid of frames in an image file. The filename for a sprite is stored internally for use with [Tiled](https://mapeditor.org) maps.

* <a name="newSpriteFT"></a>**`newSpriteFT( texture, width = 0, height = 0, pivotX = 0, pivotY = 0, margin = 0, padding = 0 )`**

  Creates a new sprite, but instead of loading an image file, it uses a previously created texture. This allows you to make sprites you can draw on and edit.

  `margin` is the distance between the frames and edges of the image, and `padding` is the space between frames. If [`setScalingFilter()`](graphics.md#setScalingFilter) has been set to true, a margin and padding of at least 1 should be used to prevent frame bleeding.

  `pivotX` and `pivotY` are the points around which the sprite is rotated and offsets where it will appear when drawn. Margin and padding are not taken into account with these it only applies to the frame itself.

  If `width` and/or `height` are left at zero, then the entire respective width or height will be used. This is useful for when you want to use an entire image as a single frame and still have certain sprite-related functions available.

* <a name="drawSprite"></a>**`drawSprite( sprite, frame, x, y, angle = 0, flip = 0, xscale = 1.0, yscale = 1.0, alpha = 1.0, color = 0xffffffff )`**

  Draws a given frame of a sprite to `x`,`y`. If a value above the sprite's maximum frame number or below zero is given, then the value will wrap around. Sprites can also be transformed and blended with the given `alpha` value. `alpha` should be a float between `0.0` and `1.0`. You can also use `color` to modulate the texture (think Game Maker's color blending).

* <a name="deleteSprite"></a>**`deleteSprite( sprite )`**

  Deletes a sprite from memory. If a new sprite is made afterwards, the index of a deleted sprite will be recycled to save memory. Be careful when creating new sprites, as any pointers to the deleted sprite will now point to that one.

* <a name="findSprite"></a>**`findSprite( filename )`**

  Searches through loaded sprites to find one that was loaded from the filename given as an argument. Path is ignored. Returns the index of the first match found, or -1 if no match is found.

* <a name="spriteName"></a>**`spriteName( id )`**

  Returns the filename of a sprite with the given ID. Returns "N/A" if the sprite does not exist.

* <a name="spriteW"></a>**`spriteW( id )`**

  Returns the frame width of a sprite. Returns 0 if the sprite does not exist.

* <a name="spriteH"></a>**`spriteH( id )`**

  Returns the frame height of a sprite. Returns 0 if the sprite does not exist.

* <a name="replaceSprite"></a>**`replaceSprite( sprite, file, width, height, margin, padding, pivotX, pivotY )`**

  Replaces `sprite` with a new file without having to create a new sprite index.

* <a name="spriteSetBlendMode"></a>**`spriteSetBlendMode( sprite, mode )`**

  Sets the blend mode for a sprite. Supported modes differ by hardware, and fallbacks are determined by SDL.