# <center>**Brux Scripting Reference Manual**</center>
## <center>File I/O</center>



&nbsp;

* <a name="mount"></a>**`mount( string1, string2, bool )`**

  Mounts (adds to the search path) a folder or an archive, referenced by the path `string1`, to the mountpoint `string2`.
  If `bool` is set to `true`, the files being mounted will be prepended on top of the search path, overriding any matching ones.
  Wrapper of [PHYSFS_mount()](https://icculus.org/physfs/docs/html/physfs_8h.html#a8eb320e9af03dcdb4c05bbff3ea604d4).

> **NOTE:**
  To mount to the root of the search path, provide `"/"` as the mountpoint.

* <a name="unmount"></a>**`unmount( string )`**

  Unmounts (removes from the search path) a folder or an archive, referenced by the path `string`.
  Wrapper of [PHYSFS_unmount()](https://icculus.org/physfs/docs/html/physfs_8h.html#aab0e2ba90aa918b2ee1ed7c40293b442).

> **NOTE:**
  This function requires the **real** path to the archive or directory that was mounted, not the path where it is mounted in the search path.

* <a name="fileExists"></a>**`fileExists( name )`**

  Checks if a file exists. Returns bool.

* <a name="fileWrite"></a>**`fileWrite( name, string )`**

  Overwrites a file's contents with a string and saves the result in the write path.

* <a name="fileRead"></a>**`fileRead( name )`**

  Reads the contents of a file and returns them as a string.

* <a name="fileAppend"></a>**`fileAppend( name, string )`**

  Adds a string to the end of a file and saves the result in the write path.

* <a name="fileDelete"></a>**`fileDelete( string )`**

  Deletes a file or directory in the write path.
  Wrapper of [PHYSFS_delete()](https://icculus.org/physfs/docs/html/physfs_8h.html#a27a939bce4c1132bacdfcb3d3cc29e37).

* <a name="jsonRead"></a>**`jsonRead( string )`**

  Turns a piece of JSON code from a string into a table and returns the table.

* <a name="jsonWrite"></a>**`jsonWrite( table )`**

  Turns a table into JSON code and returns it as a string.

*(TIP: Using the JSON functions with reading and writing files is an easy way to save and load game data by storing important variables in a table.)*

* <a name="getdir"></a>**`getdir()`**

  Returns the current working directory as a string.

* <a name="getPrefDir"></a>**`getPrefDir( string, string )`**

  Gets the user-and-app specific path, where files can be written.
  Wrapper of [PHYSFS_getPrefDir()](https://icculus.org/physfs/docs/html/physfs_8h.html#acd87392d234d070695303521bb8052a5).

* <a name="getWriteDir"></a>**`getWriteDir()`**

  Returns the path where file writing is allowed.
  Wrapper of [PHYSFS_getWriteDir()](https://icculus.org/physfs/docs/html/physfs_8h.html#a6533ff91180a4c8abfe24d458f6b9915).

* <a name="setWriteDir"></a>**`setWriteDir( string )`**

  Sets the path where file writing should be allowed. Writing directories are automatically prepended to the root of the search path, overriding any matching files.
  Wrapper of [PHYSFS_setWriteDir()](https://icculus.org/physfs/docs/html/physfs_8h.html#a36c408d40b3a93c8f9fc02a16c02e430).

> **NOTE:**
  The intended usage of this function is by providing the result of `getPrefDir()` as a parameter. This usage allows setting a proper writing directory for the game.
  By default, Brux uses the `brux` (or `brux/brux`) user-and-app specific directory for writing.

* <a name="lsdir"></a>**`lsdir( string )`**

  Returns a list of the directory `string`'s contents as an array.

* <a name="isdir"></a>**`isdir( string )`**

  Returns whether or not `string` is a directory.

* <a name="createDir"></a>**`createDir( string )`**

  Creates a new directory with the name `string` in the write path.
  Wrapper of [PHYSFS_mkdir()](https://icculus.org/physfs/docs/html/physfs_8h.html#ae11fb98bf8c08a2e028f52ac9a728aa9).

* <a name="dostr"></a>**`dostr( string )`**

  Executes `string` as the contents of a function. Remember, this creates a new scope in the place it is called.
