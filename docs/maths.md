# <center>**Brux Scripting Reference Manual**</center>
## <center>Maths</center>



&nbsp;

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
