#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 23.07.2023
# Description: This Makefile is used to generate the game executable.
#######################################################################################################

CFLAGS  = -Wextra -Wall -Werror -Wno-nonnull-compare -fanalyzer -pthread -DSDL_MAIN_HANDLED
LDFLAGS = -Wl,-Bdynamic,-rpath,'$$ORIGIN'/$(LIB) -L../hob-Server/$(LIB)		   -lHOB_server \
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/$(LIB) -L../hob-Game/$(LIB)		   -lHOB_game	\
		  -Wl,-Bdynamic,-rpath,'$$ORIGIN'/$(LIB) -L../vendor/Obfuscator/$(LIB) -lobfuscator \
		  -Wl,-rpath,'$$ORIGIN'/$(LIB),-rpath-link,'../vendor/SDL2/$(LIB)'					\
		  -L../vendor/SDL2/$(LIB) -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

INCLUDES = -Iinclude/Common				  \
		   -Iinclude/Game/Common		  \
		   -Iinclude/Game/Scenario1		  \
		   -Iinclude/Main				  \
		   -Iinclude/Menu				  \
		   -I../hob-Server/include		  \
		   -I../hob-Game/include		  \
		   -I../vendor/Plog/include		  \
		   -I../vendor/Obfuscator/include \
		   -I../vendor/SDL2/include

SOURCES    := $(wildcard $(SRC)/*/*.cpp) $(wildcard $(SRC)/*/*/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := Heap-of-Battle

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD -O0 -g
all: LDFLAGS += -Wl,-Bdynamic,-rpath='$$ORIGIN'/$(LIB) -L../vendor/Plog/$(LIB) -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O2 -DPLOG_STRIP_ALL
release: build

### BUILD ###
build: | create_dirs $(EXECUTABLE)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
	mkdir -p $(OBJ)/Common
	mkdir -p $(OBJ)/Game
	mkdir -p $(OBJ)/Game/Common
	mkdir -p $(OBJ)/Game/Scenario1
	mkdir -p $(OBJ)/Main
	mkdir -p $(OBJ)/Menu
	mkdir -p $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	rm -rf $(OBJ)
	rm -rf $(BIN)

### INSTALL ###
install:
	install $(BIN)/$(EXECUTABLE) ../$(INSTALL_DIRECTORY)

### UNINSTALL ###
uninstall:
	rm -f ../$(INSTALL_DIRECTORY)/$(EXECUTABLE)
