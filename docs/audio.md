# <center>**Brux Scripting Reference Manual**</center>
## <center>Audio</center>



&nbsp;

* <a name="loadsound"></a>**`loadSound( file );`**

  Loads a new sound from `file` and returns the index.

* <a name="loadmusic"></a>**`loadMusic( file );`**

  Loads a new track from `file` and returns the index.

* <a name="playsound"></a>**`playSound( sound, loops );`**

  Plays a sound that repeats as many times as defined by `loops`. If `-1` is used, the sound will loop until stopped. Returns the channel number of the sound being played. If looping, the return value should be stored in order to stop it later.

* <a name="playmusic"></a>**`playMusic( music, loops );`**

  Plays a music track and repeats as many times as `loops` says. Unlike with sound, it does not return a channel since only one music track can play at once.

* <a name="deletesound"></a>**`deleteSound( sound );`**

  Unloads the specified sound file.

* <a name="deletemusic"></a>**`deleteMusic( music );`**

  Unloads the specified music track.
