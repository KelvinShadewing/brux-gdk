# <center>**Brux Scripting Reference Manual**</center>
## <center>Text</center>



&nbsp;

* <a name="drawtext"></a>**`drawText( font, x, y, text )`**

  Draws a string to the current render target using the selected `font`.

* <a name="newFont"></a>**`newFont( sprite, firstchar, threshold, monospace, kerning )`**

  Creates a bitmap font from a sprite. `firstchar` is usually best set to 33 when using a full ascii sheet. `threshold` is the alpha value used for determining the width of a character for fonts using partial transparency. `monospace` is whether or not the font is monospace, and is currently locked true by default. `kerning` is the space between images, and can be negative to make them closer together.

* <a name="chint"></a>**`chint( char )`**

  Returns the integer equivalent of `char`. Not to be confused with Squirrel's `string.tointeger()`, which attempts to turn a string with a number written out in it into an actual integer.