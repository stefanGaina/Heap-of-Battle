#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   23.07.2023  Gaina Stefan               Initial version.                                           #
# Description: This Makefile is used to generate the game executable.                                 #
#######################################################################################################

CXXFLAGS = -Wall -Werror
LDFLAGS  = -Wl,-rpath='.' -L../vendor/SDL2/lib/       -lSDL2       \
		   -Wl,-rpath='.' -L../vendor/SDL2_image/lib/ -lSDL2_image \
		   -Wl,-rpath='.' -L../vendor/SDL2_mixer/lib/ -lSDL2_mixer \
		   -Wl,-rpath='.' -L../vendor/SDL2_ttf/lib/   -lSDL2_ttf

INCLUDES = -Iinclude/                      \
		   -Iinclude/Common/               \
		   -Iinclude/Main/                 \
		   -Iinclude/Menu/                 \
		   -I../vendor/Plog/include/       \
		   -I../vendor/SDL2/include/       \
		   -I../vendor/SDL2_image/include/ \
		   -I../vendor/SDL2_mixer/include/ \
		   -I../vendor/SDL2_ttf/include/

SOURCES    := $(wildcard $(SRC)/*/*.cpp)
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := Heap-of-Battle.exe

### DEVELOPMENT ###
all: devel_flags build change_executable_icon

### DEVELOPMENT FLAGS ###
devel_flags:
override CXXFLAGS += -DDEVEL_BUILD
override LDFLAGS  += -Wl,-rpath='.' -L../vendor/Plog/lib/ -lPlog

### PRODUCTION ###
release: prod_flags build change_executable_icon

### PRODUCTION FLAGS ###
prod_flags:
#override CXXFLAGS += -DPLOG_STRIP_ALL

### CHANGE EXECUTABLE ICON ###
change_executable_icon:
	../vendor/Icon-Changer/bin/icon-changer.exe ../vendor/Icon-Changer/icon/icon.ico ../Heap-of-Battle/Heap-of-Battle.exe

### BUILD ###
build: | create_dirs $(EXECUTABLE) copy_executable

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	cd $(OBJ) && if not exist "Common" mkdir Common
	cd $(OBJ) && if not exist "Main" mkdir Main
	cd $(OBJ) && if not exist "Menu" mkdir Menu
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
	$(RM) $(OBJ)\Common\*
	$(RM) $(OBJ)\Main\*
	$(RM) $(OBJ)\Menu\*
	$(RM) $(BIN)\*
