# <center>**Brux Scripting Reference Manual**</center>
## <center>Shapes</center>



&nbsp;

* <a name="hitLineLine"></a>**`hitLineLine( x0, y0, x1, y1, x2, y2, x3, y3 )`**

  Checks for a collision between to lines, the first line being the first two coordinate pairs, and the second line being the second two pairs.

* <a name="hitLineCircle"></a>**`hitLineCircle( x0, y0, x1, y1, x2, y2, r )`**

  Checks if a line is colliding with a circle. The third coordinate pair is the circle's center, and `r` is its radius.

* <a name="hitLinePoint"></a>**`hitLinePoint( x0, y0, x1, y1, x2, y2 )`**

  Checks if a point lies on a line. The third coordinate pair is the point.