# **Brux Game Engine**

&nbsp;

## **License**

All code is available under the GNU General [Public License v3](https://www.gnu.org/licenses/gpl-3.0.en.html).

### **Introduction**

 Brux (formerly known as XYG) is an open-source, cross-platform, runtime-based game development kit using the Squirrel language. The aim is to make development both easy and versatile, allowing games to be written by hand in a simple text editor or made in an IDE similar to Game Maker, and to allow games to be ported with little to no modification to the code, offering a "build once, run everywhere" development process.

Developers using Brux may freely make games without any need for paid license or royalties. Anyone willing to donate may visit my **[Patreon](http://www.patreon.com/kelvin)** or my **[Ko-Fi](http://www.ko-fi.com/kelvinshadewing)**.

### Dependencies

* SDL2
* SDL2_image
* SDL2_mixer
* SDL2_net
* SDL2_gfx
* [Squirrel](http://http://squirrel-lang.org/)
* TinyXML2 (included in source)

### To Do (Runtime)

- [X] Sprite loading and rendering
- [X] Sound loading and playing
- [X] Bitmap monospace text
- [X] Keyboard and mouse inut
- [X] Table saving/loading as JSON file
- [ ] Bitmap dynamic text
- [ ] FPS management
- [X] Gamepad input
- [ ] JSON map loading and rendering
- [ ] Collision geometry
- [ ] Chipmunk physics engine
- [ ] Create compiled format to contain multiple source files in one (will also be included in squake)

**Fixes needed:**

- [ ] Sprites do not pivot correctly when scaled and rotated at the same time
- [ ] setDrawColor() crashes the engine

### To Do (Editor)

* Everything (I haven't planned everything needed yet. I'll wait until the RE grows some more.)

### Change Log

* **0.0.4**
  * Added basic joystick support
  * Added Xinput mapping for Linux
  * Fixed `getdir()` on Windows
  * `test.nut` features keyboard/mouse (F1) and gamepad (F2) testing modes
  * Added basic geometry rendering
  * Divided reference docs into multiple files
  * Started writing tutorials

* **0.0.3**
  * Added monospace bitmap font support
  * Added support for importing/exporting tables as JSON files

* **0.0.2**
  * Finished framerate cap (framerates between 30 and 300 are distinctly different!)
  * Fixed audio bug where loadMusic() would return a sound index instead of music

* **0.0.1**
  * Added change log
  * Features existing before change log:
    * Keyboard and mouse input
	* Sprite loading and rendering
	* Sound and music
	* Run games by associating .nut and .sq files with Brux
	* Text rendering
