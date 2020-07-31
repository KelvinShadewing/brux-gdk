CFLAGS = -I. -lstdc++ -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_mixer -lSDL2_net -lsquirrel -lsqstdlib -lm -lz
SRC = audio.cpp binds.cpp cJSON.c core.cpp fileio.cpp global.cpp graphics.cpp input.cpp main.cpp maths.cpp shapes.cpp sprite.cpp text.cpp
DEPS = audio.h binds.h cJSON.h core.h fileio.h global.h graphics.h input.h main.h maths.h shapes.h sprite.h text.h
OBJ = audio.o binds.o cJSON.o core.o fileio.o global.o graphics.o input.o main.o maths.o shapes.o sprite.o text.o

%.o: %.cpp $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

linux: $(DEPS)
	gcc -o bin/brux $(SRC) $(CFLAGS)

clean:
	rm *.o
