![XYG Studio](http://xygstudio.org/img/logo.png)
## **eXperience Your Game**

&nbsp;

### **License**

All code is available under the GNU General Public License v3

### **Introduction**

XYG Studio is an open-source, cross-platform, runtime-based game development kit using the Squirrel language. The aim is to make development both easy and versatile, allowing games to be written by hand in a simple text editor or made in an IDE similar to Game Maker, and to allow games to be ported with little to no modification to the code, offering a "build once, run everywhere" development process.

Developers using XYG may freely make games without any need for paid license or royalties. Anyone willing to donate may visit my **[Patreon](http://www.patreon.com/kelvin)** or my **[Ko-Fi](http://www.ko-fi.com/kelvinshadewing)**.

### To Do (Runtime)

* FPS management
* Gamepad
* TMX maps
* Collision geometry
* Replace SDL2_ttf with bitmap fonts
* Fixes needed:
  * Sprites do not pivot correctly when scaled and rotated at the same time

### To Do (Editor)

* Everything (I haven't planned everything needed yet. I'll wait until the RE grows some more.)

### Change Log

* **1.0.2**
  * Finished framerate cap (framerates between 30 and 300 are distinctly different!)
  * Fixed audio bug where loadMusic() would return a sound index instead of music

* **1.0.1**
  * Added change log
  * Features existing before change log:
    * Keyboard and mouse input
	* Sprite loading and rendering
	* Sound and music
	* Run games by associating .nut and .sq files with XYG
	* Text rendering