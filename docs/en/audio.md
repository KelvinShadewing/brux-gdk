# <center>**Brux Scripting Reference Manual**</center>
## <center>Audio</center>



&nbsp;

* <a name="loadsound"></a>**`loadSound( file )`**

  Loads a new sound from `file` and returns the index.

* <a name="loadmusic"></a>**`loadMusic( file )`**

  Loads a new track from `file` and returns the index.

* <a name="playsound"></a>**`playSound( sound, loops )`**

  Plays a sound that repeats as many times as defined by `loops`.  
  
  If `-1` is used, the sound will loop until stopped. Returns the channel number of the sound being played. If looping, the return value should be stored in order to stop it later.

* <a name="playmusic"></a>**`playMusic( music, loops )`**

  Plays a music track and repeats as many times as `loops` says.  
  
  Unlike with sound, it does not return a channel since only one music track can play at once.

* <a name="deletesound"></a>**`deleteSound( sound )`**

  Unloads the specified sound file.

* <a name="deletemusic"></a>**`deleteMusic( music )`**

  Unloads the specified music track.

* <a name="checksound"></a>**`checkSound( channel )`**

  Checks if a sound is currently playing on the given `channel`.

* <a name="checkmusic"></a>**`checkMusic()`**

  Checks if music is currently playing.

* <a name="stopsound"></a>**`stopSound( sound )`**

  Stops the audio playing with a given ID.

* <a name="stopchannel"></a>**`stopChannel( channel )`**

  Stops the audio playing on a given channel. Use `-1` to stop all channels.

* <a name="stopmusic"></a>**`stopMusic()`**

  Stops the currently playing music.

* <a name="setmaxchannels"></a>**`setMaxChannels( integer )`**

  Sets the maximum number of audio channels that can be playing at once. Useful for saving memory.

* <a name="pausemusic"></a>**`pauseMusic()`**

  Pauses the current music.

* <a name="resumemusic"></a>**`resumeMusic()`**

  Resumes the current music.

* <a name="musicpaused"></a>**`musicPaused()`**

  Checks whether the music is paused.

* <a name="fademusic"></a>**`fadeMusic( time )`**

  Fades out the currently playing mysic over `time` number of seconds.

* <a name="setMusicVolume"></a>**`setMusicVolume( volume )`**

  Sets the volume for music. Volume is an integer between 0 and 128.

* <a name="setSoundVolume"></a>**`setSoundVolume( volume )`**

  Sets the volume for sounds. Volume is an integer between 0 and 128.

* <a name="getMusicVolume"></a>**`getMusicVolume()`**

  Returns the current music volume with an integer between 0 and 128.

* <a name="getSoundVolume"></a>**`getSoundVolume()`**

  Returns the current sound volume with an integer between 0 and 128.

* <a name="getAudioDriver"></a>**`getAudioDriver()`**

  Returns the name of the currently active audio driver.  

  If no audio driver is present, this will return the string `None`.  
  
  Note that `None` actually is an audio driver (see `src/audio/audio_none.cpp`), but it does not actually handle audio and is only used as a fallback.

* <a name="isAudioAvailable"></a>**`isAudioAvailable()`**

  Checks if audio playback is currently available.  

  Note that this function's implementation currently does not check that the audio stack is working, it only checks that a real audio driver (not the fallback `None` driver, which doesn't actually handle audio) is present.