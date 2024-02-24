Heap-of-Battle is open to contributors. All you need to do is:
	1. Dependencies:
		- For compilation you need g++ and make installed (glib in case of debug builds).
			Debian commands: sudo apt install build-essential
							 sudo apt install libglib2.0-dev
		- For running the unit tests you need gcov and perl installed.
			Debian command: sudo apt install perl
		- For running the automated tests you need bash and perl installed.
		- For generating the documentation you need doxygen installed.
			Debian command: sudo apt install doxygen
		- For formatting the code you need clang-format installed.
			Debian command: sudo apt install clang-format
	2. Build:
		- Debug build: make
		- The documentation is present in docs/html/index.html.
			to only generate documentation run: make doxygen
		- The binaries are present in Heap-of-Battle
			run Heap-of-Battle.sh to start the game
	3. For patches open a Pull Request. Check if there are any available Issues, see the TODO section in
	the documentation or suggest changes.

Basic introduction into the code:
	1. Directories:
		- hob
			executable where the graphical interface and inputs of the game are handled
		- hob-Game
			library where the logical layers of the in-game maps is
		- hob-Server
			library where the server is, loaded by the game in the case of LAN
		- hob-Server-Instance
			executable loading the server and hosting the game
	2. Key methods:
		- Entry point
			hob/src/Main/hob_Main.cpp that runs hob/src/Main/hob_Game.cpp
			this file initializes everything (Plog - logging library, SDL2 - library
			that abstracts the window creation, user inputs, sounds, etc.).
		- Main game loop
			hob/src/Main/hob_Game.cpp: Game::sceneLoop() runs instances of classes that
			extend hob/include/Common/hob_Loop.hpp that when are finished lead to other scenes.
		- Scene loop
			classes that extend hob/include/Common/hob_Loop.hpp need to implement draw() and handleEvent().
			In the first methods that draw textures to the screen are called (this is called 60 times per
			second if possible) and the second is called when a user input is avaialbe.
		- Utilitary classes
			hob/include/Common/hob_TextureInitializer.hpp initializes textures and draws them to the screen.
			hob/include/Common/hob_SoundInitializer.hpp initializes sounds and plays them.
			hob/include/Game/Common this is where the classes that are used by the game scenes.

For any questions feel free to contact me at stefan.gaina01@gmail.com.