# Include/ dir and obj/ dir
IDIR=src
ODIR=obj

# Compiler options and flags
CXX=g++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -Llib/
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR) `pkg-config --cflags raylib`
	OUT_EXT=out
endif

ERRFLAGS=-Wall -Wunused-variable -Wextra -Wno-enum-compare -fpermissive

# Put header files here
_DEPS=main.cpp Entity.cpp components/TransformComponent2D.cpp ObjectManager.cpp GameManager.cpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=main.o Entity.o components/TransformComponent2D.o ObjectManager.o GameManager.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=`pkg-config --libs raylib` -lopengl32 -lgdi32 -lwinmm
else
	LIBS=`pkg-config --libs raylib` -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compile .cpp files to .o files
$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) -g -ggdb -fdiagnostics-color=always -c -o $@ $< $(CXXFLAGS) $(ERRFLAGS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) -g -ggdb -fdiagnostics-color=always -o bin/$@.$(OUT_EXT) $^ $(CXXFLAGS) $(ERRFLAGS) $(LIBS)
#	 bin/$@.$(OUT_EXT)