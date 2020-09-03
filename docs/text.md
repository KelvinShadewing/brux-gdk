# <center>**Brux Scripting Reference Manual**</center>
## <center>Text</center>



&nbsp;

* <a name="drawtext"></a>**`drawText( x, y, text, font, color, halign, valign );`**

  Draws a string to the current render target using a loaded font. `halign` can be set with `ha_left`, `ha_center`, or `ha_right`, and `valign` can be set with `va_top`, `va_middle`, or `va_bottom`.

* <a name="openfont"></a>**`openFont( file, size );`**

  Loads a font from a `.ttf` file. `size` is in points.

* <a name="closefont"></a>**`closeFont( font );`**

  Removes `font` from memory.
