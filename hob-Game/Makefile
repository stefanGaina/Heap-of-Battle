#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   29.06.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the server.                                          #
#######################################################################################################

CFLAGS = -Wall -Werror -Wpointer-arith -fPIC

INCLUDES = -Iinclude/                \
		   -I../hob/include/Common/  \
		   -I../vendor/Plog/include/ \
		   -I../vendor/SDL2/include/

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
LIBRARY := HOB_game.dll

### DEVELOPMENT ###
all: CFLAGS  += -DDEVEL_BUILD
all: LDFLAGS += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O3 -DPLOG_STRIP_ALL
release: build

### BUILD ###
build: | create_dirs $(LIBRARY) copy_library

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(LIB)" mkdir $(LIB)

### BINARIES ###
$(LIBRARY): $(OBJECTS)
	$(CXX) $(CFLAGS) -shared -o $(LIB)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

### COPY LIBRARY ###
copy_library:
	copy $(LIB)\$(LIBRARY) ..\Heap-of-Battle

### CLEAN ###
clean:
	$(RM) $(OBJ)\*
	$(RM) $(LIB)\*
