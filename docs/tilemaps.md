# <center>**Brux Scripting Reference Manual**</center>
## <center>Tilemaps</center>



&nbsp

**NOTE:** This section is not feature complete, and currently requires `std/tilemap.nut` to be included in your project.

The `Tilemap` is a class that can load maps from Tiled Map Editor in JSON format with CSV data. It is currently compatible with non-animated orthogonal maps and polygon objects.

Maps should have tileset data embedded in them, and have the directory where the map's assets are stored pushed to `searchDir` as a string. Example: `searchDir.push("res");`

* <a name="Tilemap"></a>**`Tilemap( filename )`**
  Loads a map in Tiled JSON CSV format and returns an instance of the Tilemap class.

## Tilemap class functions

* <a name="drawTiles"></a>[SYNTAX]
  Draws a section of
