CFLAGS = -Isrc -lstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lSDL2_net -lphysfs -lsquirrel -lsqstdlib -lm --std=c++17

EMCFLAGS = -O3 -I. -lstdc++ -lm --std=c++17

EMPORTFLAGS = -sWASM=1 -sSINGLE_FILE -sFORCE_FILESYSTEM -sASYNCIFY -sALLOW_MEMORY_GROWTH -sUSE_SDL=2 -sUSE_SDL_GFX=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_NET=2 -sUSE_SDL_MIXER=2 -sSDL2_IMAGE_FORMATS='["bmp","png","xpm"]'

WINDEFS = -DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__ -D_WIN32 -Wl,-subsystem,windows

WINLIBS = -lstdc++ -lgcc -lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32

SRC = src/brux/audio.cpp src/brux/actors.cpp src/brux/binds.cpp src/external/cJSON.c src/brux/core.cpp src/brux/fileio.cpp src/brux/global.cpp src/brux/graphics.cpp src/brux/input.cpp src/brux/main.cpp src/brux/maths.cpp src/brux/shapes.cpp src/brux/sprite.cpp src/brux/text.cpp

DEPS = src/brux/audio.hpp src/brux/binds.hpp src/external/cJSON.h src/brux/core.hpp src/brux/fileio.hpp src/brux/global.hpp src/brux/graphics.hpp src/brux/input.hpp src/brux/main.hpp src/brux/maths.hpp src/brux/shapes.hpp src/brux/sprite.hpp src/brux/text.hpp

OBJ = src/brux/audio.o src/brux/actors.o src/brux/binds.o src/external/cJSON.o src/brux/core.o src/brux/fileio.o src/brux/global.o src/brux/graphics.o src/brux/input.o src/brux/main.o src/brux/maths.o src/brux/shapes.o src/brux/sprite.o src/brux/text.o

# TODO: Find a way to make this only run when rule passed in is web
ifndef EMCINCLUDE
#$(warning "EMCINCLUDE not provided, setting default value")
EMCINCLUDE = -I$$HOME/.local/include/squirrel3
endif

ifndef EMCLIBS
#$(warning "EMCLIBS not provided, setting default value")
EMCLIBS = ~/.local/lib/squirrel3/libsquirrel.a ~/.local/lib/squirrel3/libsqstdlib.a
endif

ifndef EMSHELL
EMSHELL = emscripten-minimal.html
endif

%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)

linux: $(DEPS)
	g++ -o bin/brux $(SRC) $(CFLAGS) -O2

windows: $(DEPS)
	x86_64-w64-mingw32-g++-win32 -o bin/brux.exe $(SRC) -lmingw32  $(CFLAGS) $(WINDEFS) $(WINLIBS)

gcw0: $(DEPS)
	mipsel-gcw0-linux-uclibc-g++ -o bin/brux.dge $(SRC) -mips32 -D_DINGUX -I/opt/gcw0-toolchain/usr/include $(CFLAGS) -L/opt/gcw0-toolchain/usr/lib -L/opt/gcw0-toolchain/usr/lib/gcc/mipsel-gcw0-linux-uclibc/4.9.1 -O2

web: $(DEPS)
	file_packager bin/brux.data --exclude bin/brux --exclude bin/brux.html --exclude bin/brux.data --exclude bin/game.js --exclude bin/\*.sh --preload bin@/bin > bin/game.js
	em++ -o bin/brux.html $(SRC) $(EMCLIBS) $(EMCINCLUDE) $(EMCFLAGS) $(EMPORTFLAGS) --shell-file $(EMSHELL)

clean:
	rm *.o

debug: $(DEPS)
	g++ -o bin/brux $(SRC) $(CFLAGS) -g
