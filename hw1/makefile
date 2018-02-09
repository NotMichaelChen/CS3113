#http://blog.jgc.org/2011/07/gnu-make-recursive-wildcard-function.html
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CC=g++
CFLAGS+=-I/usr/include/SDL2 -Wall -std=c++14
LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lGL -lGLU -lGLEW
VPATH = %.cpp %.o
DEPS = $(call rwildcard,, *.h)
SRC = $(call rwildcard,, *.cpp)
OBJ = $(SRC:.cpp=.o)
DEBUG = -g -O0
OPTIMIZE = -g -O2

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LIBS)

out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	find . -type f -name '*.o' -delete

.PHONY: debug
debug: CFLAGS+=$(DEBUG)
debug: out

.PHONY: debug-o
debug-o: CFLAGS+=$(OPTIMIZE)
debug-o: out
