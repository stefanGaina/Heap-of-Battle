#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   29.06.2023  Gaina Stefan               Initial version.                                           #
#   22.12.2023  Gaina Stefan               Ported to Linux.                                           #
# Description: This Makefile is used to generate the server.                                          #
#######################################################################################################

CFLAGS = -Wall -Werror -Wpointer-arith -fPIC

INCLUDES = -Iinclude/                \
		   -I../hob/include/Common/  \
		   -I../vendor/Plog/include/ \
		   -I../vendor/SDL2/include/

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
LIBRARY := libHOB_game.so

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD
all: LDFLAGS += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O3 -DPLOG_STRIP_ALL
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
