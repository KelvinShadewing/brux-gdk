# Installation Instructions

## Building From Source

If you already have a binary package built, skip to the binary install section.

Make sure you have all SDL2 development libraries installed, including image, gfx, mixer, and net. TTF is not used.
You can obtain the SDL2 development libraries for macOS using [Brew](https://brew.sh/).

Download the [Squirrel library](https://squirrel-lang.org)  and compile using Make. It should compile using just a basic GCC install. Place the generated `.a` files into `/usr/lib`. You may need to use `sudo` or a root account to do this. Place the `.h` files into `/usr/include/squirrel3`. Again, you may need to be root.

If you're building for Windows, make sure you have SDL2 configured for MinGW, and use MinGW to build Squirrel, not standard GCC.

If you're building for macOS, compile Squirrel using make then place the generated `.a` files into `/Library/Developer/CommandLineTools/usr/lib/squirrel3`. You will need administrator privileges for this. <br>
Afterwards, place the `.h` files into `/Library/Developer/CommandLineTools/usr/include/squirrel3`. Again, you will also need administator privileges for this.

Go to the `rte` folder and run `make` or `make linux`. The file `brux` should appear in `rte/bin`. To build for Windows, run `make windows`, which should produce `brux.exe` in `rte/bin`. For a MIPS Linux system, use `make gcw0`, provided you have the GCW-Zero toolchain configured. You will need to build Squirrel for that as well.

### Web (Emscripten)
#### Brux
To compile brux for the web, you'll need the Emscripten SDK which can be found [here](https://emscripten.org/docs/getting_started/downloads.html). <br>
Next, you'll need to compile Squirrel from source using Emscripten to generate the necessary library files.
```bash
mkdir build && cd build
emmake cmake ..
emmake make
```
Following this, place the static library (.a file extension for Linux) and headers somewhere you will remember e.g. `~/.local/include/squirrel3` for the headers  and `~/.local/lib/squirrel3` for the static libraries. <br>
Now entering Brux's `rte` folder, run `emmake make web`. <br>
By default, the makefile will include `$HOME/.local/include/squirrel3` and link static libraries from `~/.local/lib/squirrel3` <br>
This can be overriden by compiling using the command `emmake make web EMCINCLUDE="-I(HEADERPATH)" EMCLIBS="(SQUIRREL_LIB_PATH) (SQUIRREL_STD_LIB_PATH)"`.
#### Packaging applications
To package applications into a `.data` file, use file_packager from the Emscripten SDK. <br>
Example command: `file_packager brux.data --exclude \*.data --exclude \*.sh --preload .@/bin > game.js`

## Installing From Binary

If you have successfully built Brux, or have downloaded the nightly build, follow the instructions for your operating system.

### Linux

Place `brux` into any folder you please. If you put it anywhere other than `/usr/bin`, open a terminal in the folder and run `sudo ln -s <full path to Brux> /usr/bin/brux`. You will now be able to run Brux from the terminal. To load games with a click, use the included `.sh` file to launch them, or associate `.brx` files with Brux.

### Windows

Place `brux.exe` anywhere and associate `.brx` files with it.

### Mac

Place `brux` into `/Library/Developer/CommandLineTools/bin` or `/Library/Developer/CommandLineTools/usr/bin` so you can use Brux via the command line.

### Web

Simply have your server run in the same directory as Brux's HTML file. <br>
You may want to rename `brux.html` to `index.html` so the server automatically points to it.