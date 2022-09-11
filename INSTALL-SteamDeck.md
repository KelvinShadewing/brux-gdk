# (Potentially Temporary) Install instructions on Steam Deck (with SteamOS Holo)
## Prerequisites
* A steam account
## Notes
* The Steam Deck by default comes with SDL2 but not the extensions.
* If you haven't set a password for the user `deck`, sudo cannot be executed as it will ask for a password. To set a password, run `passwd`.
## Installation from binary
Firstly, go into the `Settings > System` in Gaming Mode and enable developer mode so you can use pacman. <br>
Afterwards, go into Desktop Mode and open Konsole and run the following commands:
```sh
sudo steamos-readonly disable
sudo pacman-key init
sudo pacman-key --populate archlinux && sudo pacman-key --populate holo
```
These commands will let you install software via pacman by disabling the read-only filesystem and getting all trusted keys for archlinux and holo sources. <br>
Next, install the following SDL2 packages: `sdl2_gfx`, `sdl2_image`, `sdl2_mixer` and `sdl2_net`. <br>
You can do this by running `sudo pacman -S sdl2_gfx sdl2_image sdl2_mixer sdl2_net`. <br>
After this, brux should be able to launch.
## Bonus Section: Adding a game made in brux to Steam
Adding a game made in brux to your Steam Library is fairly simple to do. <br>
Go into Dolphin (file browser) and right click and go to `Create New > Link to application`. <br>
Next, go to the application tab on the properties for the new link and set the command to be the path to brux and the path to the game seperated with a space. <br>
Example (with brux in Downloads and with SuperTux Advance (Unstable Branch) in Documents/supertux-advance): `/home/deck/Downloads/brux /home/deck/Documents/supertux-advance/game.brx` <br>
Following this, go into the permissions tab and check `Is Executable` to allow the link to be run. Press OK to save the link. <br>
Now, go into the desktop client for Steam and press `Add A Game > Add a Non-Steam Game` then click browse. Find your link to an application, click open and click Add Selected Program. <br>
Repeat for all games you have downloaded that are made using brux. <br>
Now you can return to gaming mode and play them.
