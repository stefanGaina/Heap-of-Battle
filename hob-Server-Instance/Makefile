#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   26.07.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the server instance.                                 #
#######################################################################################################

CFLAGS = -Wall -Werror
LDFLAGS  = -Wl,-rpath='.' -L../hob-Server/lib/ -lHOB_server \
		   -lws2_32

INCLUDES = -Iinclude/               \
		   -I../hob-Server/include/ \
		   -I../vendor/Plog/include/

SOURCES    := $(wildcard $(SRC)/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := HOB-Server.exe

### DEVELOPMENT ###
all: CFLAGS  += -DDEVEL_BUILD
all: LDFLAGS += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lplog
all: build

### PRODUCTION ###
release: CFLAGS += -O3 -DPLOG_STRIP_ALL -fno-ident
release: build

### BUILD ###
build: | create_dirs $(EXECUTABLE) copy_executable

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(BIN)" mkdir $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

### COPY EXECUTABLE ###
copy_executable:
	copy $(BIN)\$(EXECUTABLE) ..\Heap-of-Battle

### CLEAN ###
clean:
	$(RM) $(OBJ)\*
	$(RM) $(BIN)\*
