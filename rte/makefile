CFLAGS = -I. -lstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lSDL2_net -lsquirrel -lsqstdlib -lm --std=c++17

EMCFLAGS = -O3 -I/usr/include/squirrel3 -I~/.local/lib/squirrel3/ -I. -lstdc++ -lm --std=c++17 -lidbfs.js

EMPORTFLAGS = -sWASM=1 -sSINGLE_FILE -sFORCE_FILESYSTEM -sASYNCIFY -sALLOW_MEMORY_GROWTH -sEXPORTED_RUNTIME_METHODS=ccall,cwrap -lnodefs.js -sUSE_SDL=2 -sUSE_SDL_GFX=2 -sUSE_SDL_IMAGE=2 -sUSE_SDL_NET=2 -sUSE_SDL_MIXER=2 -sSDL2_IMAGE_FORMATS='["bmp","png","xpm"]'

WINDEFS = -DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__ -D_WIN32 -Wl,-subsystem,windows

WINLIBS = -lstdc++ -lgcc -lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32

SRC = audio.cpp actors.cpp binds.cpp cJSON.c core.cpp fileio.cpp global.cpp graphics.cpp input.cpp main.cpp maths.cpp shapes.cpp sprite.cpp text.cpp

DEPS = audio.h binds.h cJSON.h core.h fileio.h global.h graphics.h input.h main.h maths.h shapes.h sprite.h text.h

OBJ = audio.o actors.o binds.o cJSON.o core.o fileio.o global.o graphics.o input.o main.o maths.o shapes.o sprite.o text.o



%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)

linux: $(DEPS)
	g++ -o bin/brux $(SRC) $(CFLAGS) -O2

windows: $(DEPS)
	x86_64-w64-mingw32-g++-win32 -o bin/brux.exe $(SRC) -lmingw32  $(CFLAGS) $(WINDEFS) $(WINLIBS)

gcw0: $(DEPS)
	mipsel-gcw0-linux-uclibc-g++ -o bin/brux.dge $(SRC) -mips32 -D_DINGUX -I/opt/gcw0-toolchain/usr/include $(CFLAGS) -L/opt/gcw0-toolchain/usr/lib -L/opt/gcw0-toolchain/usr/lib/gcc/mipsel-gcw0-linux-uclibc/4.9.1 -O2

web: $(DEPS)
	em++ -o bin/brux.html $(SRC) ~/.local/lib/squirrel3/libsquirrel.a ~/.local/lib/squirrel3/libsqstdlib.a $(EMCFLAGS) $(EMPORTFLAGS) --exclude-file bin/brux* --preload-file ./@/bin  # What the hiff is this????

clean:
	rm *.o

debug: $(DEPS)
	g++ -o bin/brux $(SRC) $(CFLAGS) -g
