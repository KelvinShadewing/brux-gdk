# <center>**Brux Scripting Reference Manual**</center>
## <center>File I/O</center>



&nbsp;

* <a name="fileExists"></a>**`fileExists( name )`**

  Checks if a file exists. Returns bool.

* <a name="fileWrite"></a>**`fileWrite( name, string )`**

  Overwrites a file's contents with a string.

* <a name="fileRead"></a>**`fileRead( name )`**

  Reads the contents of a file and returns them as a string.

* <a name="fileAppend"></a>**`fileAppend( name, string )`**

  Adds a string to the end of a file.

* <a name="jsonRead"></a>**`jsonRead( string )`**

  Turns a piece of JSON code from a string into a table and returns the table.

* <a name="jsonWrite"></a>**`jsonWrite( table )`**

  Turns a table into JSON code and returns it as a string.

*(TIP: Using the JSON functions with reading and writing files is an easy way to save and load game data by storing important variables in a table.)*

* <a name="getdir"></a>**`getdir()`**

  Returns the current working directory as a string.

* <a name="chdir"></a>**`chdir( string )`**

  Attempts to change the current working directory.

* <a name="lsdir"></a>**`lsdir( string )`**

  Returns a list of the directory `string`'s contents as an array.

* <a name="isdir"></a>**`isdir( string )`**

  Returns whether or not `string` is a directory.

* <a name="dostr"></a>**`dostr( string )`**

  Executes `string` as the contents of a function. Remember, this creates a new scope in the place it is called.