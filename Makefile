# Include/ dir and obj/ dir
IDIR=src
ODIR=obj

# Compiler options and flags
CXX=c++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -IC:/msys64/mingw64/bin/../include/SDL2 -Dmain=SDL_main
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR) `pkg-config --cflags sdl2`
	OUT_EXT=out
endif

ERRFLAGS=-Wall -Wunused-variable -Wextra -Wno-enum-compare -fpermissive

# Put header files here
_DEPS=main.cpp Entity.cpp components/TransformComponent2D.cpp components/SpriteComponent.cpp components/Component.cpp ObjectManager.cpp GameManager.cpp util/graphics.cpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=main.o Entity.o components/TransformComponent2D.o components/SpriteComponent.o components/Component.o ObjectManager.o GameManager.o util/graphics.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=-LC:/msys64/mingw64/bin/../lib -lmingw32 -lSDL2main -lSDL2
else
	LIBS=`pkg-config --libs sdl2`
endif

# Compile .cpp files to .o files
$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) $(ERRFLAGS) -g -ggdb -fdiagnostics-color=always -c -o $@ $< $(LIBS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) $(CXXFLAGS) $(ERRFLAGS) -g -ggdb -fdiagnostics-color=always -o bin/$@.$(OUT_EXT) $^ $(LIBS)
#	 bin/$@.$(OUT_EXT)