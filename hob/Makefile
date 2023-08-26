#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   23.07.2023  Gaina Stefan               Initial version.                                           #
#   27.07.2023  Gaina Stefan               Added winsock linking.                                     #
#   26.08.2023  Gaina Stefan               Fix gcc depedencies.                                       #
# Description: This Makefile is used to generate the game executable.                                 #
#######################################################################################################

CXXFLAGS = -Wall -Werror
LDFLAGS  = -Wl,-Bdynamic,-rpath='.' -L../hob-Server/lib/        -lHOB_server \
		   -Wl,-Bdynamic,-rpath='.' -L../vendor/Obfuscator/lib/ -lObfuscator \
		   -Wl,-Bdynamic,-rpath='.' -L../vendor/SDL2/lib/       -lSDL2       \
		   -Wl,-Bdynamic,-rpath='.' -L../vendor/SDL2_image/lib/ -lSDL2_image \
		   -Wl,-Bdynamic,-rpath='.' -L../vendor/SDL2_mixer/lib/ -lSDL2_mixer \
		   -Wl,-Bdynamic,-rpath='.' -L../vendor/SDL2_ttf/lib/   -lSDL2_ttf   \
		   -Wl,-Bstatic -lws2_32                                             \
		   -Wl,-Bstatic -lwinpthread                                         \
		   -static -static-libgcc                                            \
		   -static-libstdc++

INCLUDES = -Iinclude/                      \
		   -Iinclude/Common/               \
		   -Iinclude/Game/Common/          \
		   -Iinclude/Game/Scenario1/       \
		   -Iinclude/Main/                 \
		   -Iinclude/Menu/                 \
		   -I../hob-Server/include/        \
		   -I../vendor/Obfuscator/include/ \
		   -I../vendor/Plog/include/       \
		   -I../vendor/SDL2/include/       \
		   -I../vendor/SDL2_image/include/ \
		   -I../vendor/SDL2_mixer/include/ \
		   -I../vendor/SDL2_ttf/include/

SOURCES    := $(wildcard $(SRC)/*/*.cpp) $(wildcard $(SRC)/*/*/*.cpp) 
OBJECTS    := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := Heap-of-Battle.exe

### DEVELOPMENT ###
all: devel_flags build

### DEVELOPMENT FLAGS ###
devel_flags:
override CXXFLAGS += -DDEVEL_BUILD
override LDFLAGS  += -Wl,-Bdynamic,-rpath='.' -L../vendor/Plog/lib/ -lPlog

### PRODUCTION ###
release: prod_flags build

### PRODUCTION FLAGS ###
prod_flags:
#override CXXFLAGS += -DPLOG_STRIP_ALL

### CHANGE EXECUTABLE ICON ###
change_executable_icon:
	../vendor/Icon-Changer/bin/icon-changer.exe ../vendor/Icon-Changer/icon/icon.ico ../Heap-of-Battle/Heap-of-Battle.exe

### BUILD ###
build: | create_dirs $(EXECUTABLE) copy_executable change_executable_icon

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	cd $(OBJ) && if not exist "Common" mkdir Common
	cd $(OBJ) && if not exist "Game" mkdir Game
	cd $(OBJ)\Game && if not exist "Common" mkdir Common
	cd $(OBJ)\Game && if not exist "Scenario1" mkdir Scenario1
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
	$(RM) $(OBJ)\Game\Common\*
	$(RM) $(OBJ)\Game\Scenario1\*
	$(RM) $(BIN)\*
