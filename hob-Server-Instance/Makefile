#######################################################################################################
# Copyright (C) Heap of Battle 2024                                                                   #
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   26.07.2023  Gaina Stefan               Initial version.                                           #
#   21.12.2023  Gaina Stefan               Ported to Linux.                                           #
# Description: This Makefile is used to generate the server instance.                                 #
#######################################################################################################

CFLAGS  = -Wall -Werror
LDFLAGS = -Wl,-rpath,'$$ORIGIN'/$(LIB) -L../hob-Server/$(LIB) -lHOB_server

INCLUDES = -Iinclude               \
		   -I../hob-Server/include \
		   -I../vendor/Plog/include

SOURCES    := $(wildcard $(SRC)/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := HOB-Server

### DEVELOPMENT ###
all: CFLAGS  += `pkg-config --cflags glib-2.0` -DDEVEL_BUILD
all: LDFLAGS += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O3 -DPLOG_STRIP_ALL -fno-ident
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
