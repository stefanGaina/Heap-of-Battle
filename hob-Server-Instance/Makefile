#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   26.07.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the server instance.                                 #
#######################################################################################################

CXXFLAGS = -Wall -Werror
LDFLAGS  = -Wl,-rpath='.' -L../hob-Server/lib/ -lHOB_server \
		   -lws2_32

INCLUDES = -Iinclude/               \
		   -I../hob-Server/include/ \
		   -I../vendor/Plog/include/

SOURCES    := $(wildcard $(SRC)/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := HOB-Server.exe

### DEVELOPMENT ###
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
build: | create_dirs $(EXECUTABLE) copy_executable

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(BIN)" mkdir $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BIN)/$@ $^ $(LDFLAGS)

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

### COPY EXECUTABLE ###
copy_executable:
	copy $(BIN)\$(EXECUTABLE) ..\Heap-of-Battle

### CLEAN ###
clean:
	$(RM) $(OBJ)\*
	$(RM) $(BIN)\*
