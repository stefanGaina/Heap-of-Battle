#######################################################################################################
# Copyright (C) Heap of Battle 2024
# Author: Gaina Stefan
# Date: 26.07.2023
# Description: This Makefile is used to generate the server instance.
#######################################################################################################

CFLAGS  = -Wextra -Wall -Werror -fanalyzer
LDFLAGS = -Wl,-rpath,'$$ORIGIN'/$(LIB) -L../hob-Server/$(LIB) -lHOB_server

INCLUDES = -Iinclude               \
		   -I../hob-Server/include \
		   -I../vendor/Plog/include

SOURCES    := $(wildcard $(SRC)/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := HOB-Server

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD -O0 -g
all: LDFLAGS += -Wl,-rpath='$$ORIGIN'/$(LIB) -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O2 -DPLOG_STRIP_ALL
release: build

### BUILD ###
build: | create_dirs $(EXECUTABLE)

### CREATE DIRECTORIES ###
create_dirs:
	mkdir -p $(OBJ)
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
