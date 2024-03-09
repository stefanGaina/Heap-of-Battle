#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 29.06.2023
# Description: This Makefile is used to generate the game library.
#######################################################################################################

CFLAGS = -Wextra -Wall -Werror -Wno-nonnull-compare -fanalyzer -fPIC

INCLUDES = -Iinclude                \
		   -I../hob/include/Common  \
		   -I../vendor/Plog/include \
		   -I../vendor/SDL2/include

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
LIBRARY := libHOB_game.so

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD -O0 -g
all: LDFLAGS += -Wl,-rpath='$$ORIGIN'/$(LIB) -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O2 -DPLOG_STRIP_ALL
release: build

### BUILD ###
build: | create_dirs $(LIBRARY)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
	mkdir -p $(LIB)

### BINARIES ###
$(LIBRARY): $(OBJECTS)
	$(CXX) $(CFLAGS) -shared -o $(LIB)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	rm -rf $(OBJ)
	rm -rf $(LIB)

### INSTALL ###
install:
	install $(LIB)/$(LIBRARY) ../$(INSTALL_DIRECTORY)/$(LIB)

### UNINSTALL ###
uninstall:
	rm -f ../$(INSTALL_DIRECTORY)/$(LIB)/$(LIBRARY)
