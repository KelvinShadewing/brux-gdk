# <center>**Brux Scripting Reference Manual**</center>
## <center>Tilemaps</center>



&nbsp

**NOTE:** This section is not feature complete, and currently requires `std/tilemap.nut` to be included in your project.

The `Tilemap` is a class that can load maps from Tiled Map Editor in JSON format with CSV data. It is currently compatible with non-animated orthogonal maps and polygon objects.

Maps should have tileset data embedded in them, and have the directory where the map's assets are stored pushed to `searchDir` as a string. Example: `searchDir.push("res");`

* <a name="Tilemap"></a>**`Tilemap( filename )`**
  Loads a map in Tiled JSON CSV format and returns an instance of the Tilemap class.

## Tilemap class functions

**NOTE:** These functions exist within `Tilemap`, and should be called with a map instance. Example:

```
local map = Tilemap("file")

map.drawTiles( x, y, mapx, mapy, mapw, maph, layer )
```

* <a name="drawTiles"></a>**`drawTiles( x, y, mapx, mapy, mapw, maph, layer )`**

  Draws a section of `layer`, identified as a string matching the layer's name. `mapx` and `mapy` are the top left tile to start from, while `mapw` and `maph` are how wide and tall a region to draw from. `x` and `y` determine where on screen to draw the section.

* <a name="drawShapes"></a>**`drawShapes( x, y, layer )`**

  Draws the shapes within an object layer named `layer`. Shapes will automatically be offset by their position in the layer. `x` and `y` determine where to draw the layer as a whole.