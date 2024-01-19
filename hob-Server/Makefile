#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   29.06.2023  Gaina Stefan               Initial version.                                           #
#   21.12.2023  Gaina Stefan               Ported to Linux.                                           #
#   19.01.2024  Gaina Stefan               Updated flags.                                             #
# Description: This Makefile is used to generate the server.                                          #
#######################################################################################################

CFLAGS = -Wextra -Wall -Werror -fPIC

INCLUDES = -Iinclude             \
		   -I../hob/include/Main \
		   -I../vendor/Plog/include

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
LIBRARY := libHOB_server.so

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD -g
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
