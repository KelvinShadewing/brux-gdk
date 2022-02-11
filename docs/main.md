# <center>**Brux Scripting Reference Manual**</center>
## <center>Main</center>



&nbsp;

* <a name="update"></a>**`update()`**

  Updates screen and input.

* <a name="getOS"></a>**`getOS()`**

  Checks what OS the app is running on. Returns a string.

* <a name="wait"></a>**`wait( ticks )`**

  Waits for `ticks` number of ticks/miliseconds.

* <a name="donut"></a>**`donut( file )`**

  Loads and runs a script file local to the current game. If ".nut" is not included in the file name given, it will add it automatically.

* <a name="getFrames"></a>**`getFrames()`**

  Returns the number of frames that have passed since the game began. Frames are counted by the number of calls to [update()][#update].

* <a name="getTicks"></a>**`getTicks()`**

  Returns the number of ticks that have passed since the game began. Ticks are counted by SDL itself from the point of execution, and increment no matter how long the given frame lasts.

* <a name="getFPS"></a>**`getFPS()`**

  Gets the frames per second based on the length of the last frame.

* <a name="setFPS"></a>**`setFPS( num )`**

  Sets the maximum frame speed. The game will attempt to limit how fast it runs to this speed. Don't set it to 0.

* <a name="setWindowTitle"></a>**`setWindowTitle( string )`**

  Changes the title of the game window. Appears as "Brux GDK" by default.

* <a name="setWindowIcon"></a>**`setWindowIcon( filename )`**

  Changes the window icon to the specified file. It does not need to be preloaded as a sprite or texture.

* <a name="bruxVersion"></a>**`bruxVersion()`**

  Returns the current runtime version as a string.