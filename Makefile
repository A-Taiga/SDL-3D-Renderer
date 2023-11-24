
CXXFLAGS = `pkg-config --libs --cflags sdl2`
CC = clang++ -std=c++20 -g -Wall -Wextra -pedantic -Wshadow -I /usr/local/include

OBJDIR = obj/
SRCDIR = src/
VPATH = src: obj:

objects = main.o window.o shapes.o
exeName = sdl-3D

all: $(exeName)

$(exeName): $(objects)
	$(CC) $^ -o $@ $(CXXFLAGS)

$(OBJDIR)main.o: main.cpp window.hpp shapes.hpp
	$(CC) -c -o $@ $<

$(OBJDIR)window.o: window.cpp
	$(CC) -c -o $@ $<

$(OBJDIR)shapes.o: shapes.cpp 
	$(CC) -c -o $@ $<


.PHONY: clean run
clean:
	-rm $(OBJDIR)*.o $(exeName)
run:
	./$(exeName)