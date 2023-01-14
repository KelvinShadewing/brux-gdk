CXX ?= g++
CXXFLAGS ?= -O2
PKG_CONFIG ?= pkg-config

PKGS = sdl2 SDL2_image SDL2_gfx SDL2_mixer SDL2_net squirrel

CXXFLAGS_PKGS = -I. `$(PKG_CONFIG) --cflags $(PKGS)`

LIBS = -lstdc++ -lm `$(PKG_CONFIG) --libs $(PKGS)`

WINDEFS = -DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__ -D_WIN32 -Wl,-subsystem,windows

WINLIBS = -lstdc++ -lgcc -lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32

SRC = audio.cpp actors.cpp binds.cpp cJSON.c core.cpp fileio.cpp global.cpp graphics.cpp input.cpp main.cpp maths.cpp shapes.cpp sprite.cpp text.cpp

DEPS = audio.h binds.h cJSON.h core.h fileio.h global.h graphics.h input.h main.h maths.h shapes.h sprite.h text.h

OBJ = audio.o actors.o binds.o cJSON.o core.o fileio.o global.o graphics.o input.o main.o maths.o shapes.o sprite.o text.o

linux: bin/brux

windows: bin/brux.exe

gcw0: bin/brux.dge

%.o: %.cpp $(DEPS)
	$(CXX) --std=c++17 $(CXXFLAGS) $(CXXFLAGS_PKGS) -c -o $@ $< $(LIBS)

bin/brux: $(DEPS) $(SRC)
	$(CXX) --std=c++17 $(CXXFLAGS) $(CXXFLAGS_PKGS) -o bin/brux $(SRC) $(LIBS)

bin/brux.exe: $(DEPS) $(SRC)
	x86_64-w64-mingw32-g++-win32 --std=c++17 $(CXXFLAGS) $(CXXFLAGS_PKGS) -o bin/brux.exe $(SRC) -lmingw32  $(LIBS) $(WINDEFS) $(WINLIBS)

bin/brux.dge: $(DEPS) $(SRC)
	mipsel-gcw0-linux-uclibc-g++ --std=c++17 $(CXXFLAGS) $(CXXFLAGS_PKGS) -o bin/brux.dge $(SRC) -mips32 -D_DINGUX -I/opt/gcw0-toolchain/usr/include $(CFLAGS) -L/opt/gcw0-toolchain/usr/lib -L/opt/gcw0-toolchain/usr/lib/gcc/mipsel-gcw0-linux-uclibc/4.9.1 -O2

clean:
	rm -f bin/brux bin/brux.exe bin/brux.dge
	rm -f *.o

debug: $(DEPS)
	g++ -o bin/brux $(SRC) $(CFLAGS) -g