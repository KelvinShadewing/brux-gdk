# <center>**Brux Scripting Reference Manual**</center>
## <center>Sprites</center>



&nbsp;

* <a name="newSprite"></a>**`newSprite( file, width, height, margin, padding, pivotX, pivotY )`**

  Creates a new sprite from a grid of frames in an image file. The filename for a sprite is stored internally for use with [Tiled](https://mapeditor.org) maps.

* <a name="newSprite"></a>**`newSprite( texture, width, height, margin, padding, pivotX, pivotY )`**

  Creates a new sprite, but instead of loading an image file, it uses a previously created texture. This allows you to make sprites you can draw on and edit.

  `margin` is the distance between the frames and edges of the image, and `padding` is the space between frames. If [`setScalingFilter()`](graphics.md#setScalingFilter) has been set to true, a margin and padding of at least 1 should be used to prevent frame bleeding.

  `pivotX` and `pivotY` are the points around which the sprite is rotated and offsets where it will appear when drawn. Margin and padding are not taken into account with these it only applies to the frame itself.

* <a name="drawSprite"></a>**`drawSprite( sprite, frame, x, y )`**

  Draws a given frame of a sprite to `x`,`y`. If a value above the sprite's maximum frame number or below zero is given, then the value will wrap around.

* <a name="drawSpriteEx"></a>**`drawSpriteEx( sprite, frame, x, y, angle, flip, xscale, yscale, alpha )`**

  Draws a sprite that is also transformed and blended with the given `alpha` value. `alpha` should be a float between `0.0` and `1.0`.

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