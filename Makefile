# Include/ dir and obj/ dir
IDIR=src
ODIR=obj

# Compiler options and flags
CXX=g++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -Iinclude/ -Llib/
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR)
	OUT_EXT=out
endif

ERRFLAGS=-Wall -Wunused-variable -Wextra -Wno-enum-compare

# Put header files here
_DEPS=main.cpp DrawableManager.cpp GameManager.cpp Sprite.cpp \
imgui/imgui_demo.cpp imgui/imgui_draw.cpp \
imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui.cpp imgui/rlImGui.cpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=main.o DrawableManager.o GameManager.o Sprite.o \
imgui/imgui_demo.o imgui/imgui_draw.o \
imgui/imgui_tables.o imgui/imgui_widgets.o imgui/imgui.o imgui/rlImGui.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
else
	LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compile .cpp files to .o files
$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) -g -ggdb -fdiagnostics-color=always -c -o $@ $< $(CXXFLAGS) $(ERRFLAGS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) -g -ggdb -fdiagnostics-color=always -o bin/$@.$(OUT_EXT) $^ $(CXXFLAGS) $(ERRFLAGS) $(LIBS)
#	 bin/$@.$(OUT_EXT)