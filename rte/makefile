CFLAGS = -I. -lstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lSDL2_net -lsquirrel -lsqstdlib -lm

WINDEFS = -DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__ -D_WIN32

WINLIBS = -lstdc++ -lgcc -lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32

SRC = audio.cpp binds.cpp cJSON.c core.cpp fileio.cpp global.cpp graphics.cpp input.cpp main.cpp maths.cpp shapes.cpp sprite.cpp text.cpp

DEPS = audio.h binds.h cJSON.h core.h fileio.h global.h graphics.h input.h main.h maths.h shapes.h sprite.h text.h

OBJ = audio.o binds.o cJSON.o core.o fileio.o global.o graphics.o input.o main.o maths.o shapes.o sprite.o text.o



%.o: %.cpp $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

linux: $(DEPS)
	gcc -o bin/brux $(SRC) $(CFLAGS)

windows: $(DEPS)
	x86_64-w64-mingw32-gcc-win32 -o bin/brux.exe $(SRC) -lmingw32  $(CFLAGS) $(WINDEFS) $(WINLIBS)

gcw0: $(DEPS)
	mipsel-gcw0-linux-uclibc-g++ -o bin/brux.dge $(SRC) -mips32 -D_DINGUX -I/opt/gcw0-toolchain/usr/include $(CFLAGS) -L/opt/gcw0-toolchain/usr/lib -L/opt/gcw0-toolchain/usr/lib/gcc/mipsel-gcw0-linux-uclibc/4.9.1 -lssp_nonshared -fno-stack-protector

clean:
	rm *.o
