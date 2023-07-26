#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   29.06.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the server.                                          #
#######################################################################################################

CFLAGS = -Wall -Werror -Wpointer-arith -fPIC

INCLUDES = -Iinclude/               \
		   -I../hob/include/Main/   \
		   -I../vendor/Plog/include/

LDFLAGS  = -lws2_32

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
LIBRARY := HOB_server.dll

all: devel_flags build

### DEVELOPMENT FLAGS ###
devel_flags:
override CXXFLAGS += -DDEVEL_BUILD
override LDFLAGS  += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lPlog

### PRODUCTION ###
release: prod_flags build

### PRODUCTION FLAGS ###
prod_flags:
#override CXXFLAGS += -DPLOG_STRIP_ALL

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
