# <center>**Brux Scripting Reference Manual**</center>
## <center>Input</center>



&nbsp;

* <a name="keyDown"></a>**`keyDown( key )`**

  Returns whether or not `key` is currently held.

* <a name="keyPress"></a>**`keyPress( key )`**

  Returns whether or not `key` was just pressed.

* <a name="keyRelease"></a>**`keyRelease( key )`**

  Returns whether or not `key` was just released.

* <a name="anyKeyPress"></a>**`anyKeyPress()`**

  If any key was pressed on the current frame, this returns the first one detected, otherwise, it returns -1. Useful for remapping controls.

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

* <a name="joyX"></a>**`joyX( id )`**

  Returns position of X axis on pad numbered `id`.

* <a name="joyY"></a>**`joyY( id )`**

  Returns position of Y axis on pad numbered `id`.

* <a name="joyZ"></a>**`joyZ( id )`**

  Returns position of Z axis on pad numbered `id`.

* <a name="joyH"></a>**`joyH( id )`**

  Returns position of 'horizontal' axis on pad numbered `id`.

* <a name="joyV"></a>**`joyV( id )`**

  Returns position of 'vertical' axis on pad numbered `id`.

* <a name="joyR"></a>**`joyR( id )`**

  Returns position of right trigger on pad numbered `id`.

* <a name="joyL"></a>**`joyL( id )`**

  Returns position of left trigger on pad numbered `id`.

* <a name="joyAxis"></a>**`joyAxis( id, axis )`**

  Returns position of axis numbered `axis` on pad numbered `id`.

* <a name="joyHatPress"></a>**`joyHatPress( id, direction )`**

  Returns whether a given direction on the gamepad's hat is pressed. See [constants](constants.md#joystick) for directions.

* <a name="joyHatRelease"></a>**`joyHatRelease( id, direction )`**

  Returns whether a given direction on the gamepad's hat is released. See [constants](constants.md#joystick) for directions.

* <a name="joyHatDown"></a>**`joyHatDown( id, direction )`**

  Returns whether a given direction on the gamepad's hat is being held. See [constants](constants.md#joystick) for directions.

* <a name="joyButtonPress"></a>**`joyButtonPress( id, button )`**

  Returns if a gamepad's button numbered `button` is pressed.

* <a name="joyButtonRelease"></a>**`joyButtonRelease( id, button )`**

  Returns if a gamepad's button numbered `button` is released.

* <a name="joyButtonDown"></a>**`joyButtonDown( id, button )`**

  Returns if a gamepad's button numbered `button` is held.

* <a name="anyJoyPress"></a>**`anyJoyPress( id )`**

  If any button on the gamepad is pressed, it returns the number, otherwise, it returns -1.