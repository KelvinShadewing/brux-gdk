# <center>**Brux Scripting Reference Manual**</center>
## <center>Input</center>



&nbsp

* <a name="keyDown"></a>**`keyDown( key )`**

  Returns whether or not `key` is currently held.

* <a name="keyPress"></a>**`keyPress( key )`**

  Returns whether or not `key` was just pressed.

* <a name="keyRelease"></a>**`keyRelease( key )`**

  Returns whether or not `key` was just released.

* <a name="mouseX"></a>**`mouseX()`**

  Returns the X coordinate of the mouse.

* <a name="mouseY"></a>**`mouseY()`**

  Returns the Y coordinate of the mouse.

* <a name="mouseDown"></a>**`mouseDown( button )`**

  Returns whether a given mouse button is currently held. Unlike with key input, mouse input does not use constants because he mouse has only a few buttons.

* <a name="mousePress"></a>**`mousePress( button )`**

  Returns whether a given mouse button was just pressed.

* <a name="mouseRelease"></a>**`mouseRelease( button )`**

  Returns whether a given mouse button was just released.

* <a name="getQuit"></a>**`getQuit()`**

  Returns if the exit button on the window or the OS's exit shortcut has been pressed.

* <a name="getPads"></a>**`getPads()`**

  Returns number of gamepads detected.

* <a name="padX"></a>**`padX( id )`**

  Returns position of X axis on pad numbered `id`.

* <a name="padY"></a>**`padY( id )`**

  Returns position of Y axis on pad numbered `id`.

* <a name="padZ"></a>**`padZ( id )`**

  Returns position of Z axis on pad numbered `id`.

  * <a name="padH"></a>**`padH( id )`**

  Returns position of 'horizontal' axis on pad numbered `id`.

* <a name="padV"></a>**`padV( id )`**

  Returns position of 'vertical' axis on pad numbered `id`.

* <a name="padR"></a>**`padR( id )`**

  Returns position of right trigger on pad numbered `id`.

* <a name="padL"></a>**`padL( id )`**

  Returns position of left trigger on pad numbered `id`.

* <a name="padAxis"></a>**`padAxis( id, axis )`**

  Returns position of axis numbered `axis` on pad numbered `id`.

* <a name="padHatPress"></a>**`padHatPress( id, direction )`**

  Returns whether a given direction on the gamepad's hat is pressed. See [constants](constants.md#joystick) for directions.

* <a name="padHatRelease"></a>**`padHatRelease( id, direction )`**

  Returns whether a given direction on the gamepad's hat is released. See [constants](constants.md#joystick) for directions.

* <a name="padHatDown"></a>**`padHatDown( id, direction )`**

  Returns whether a given direction on the gamepad's hat is being held. See [constants](constants.md#joystick) for directions.

* <a name="padButtonPress"></a>**`padButtonPress( id, button )`**

  Returns if a gamepad's button numbered `button` is pressed.

* <a name="padButtonRelease"></a>**`padButtonRelease( id, button )`**

  Returns if a gamepad's button numbered `button` is released.

* <a name="padButtonDown"></a>**`padButtonDown( id, button )`**

  Returns if a gamepad's button numbered `button` is held.