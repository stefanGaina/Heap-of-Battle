Heap-of-Battle is open to contributors. All you need to do is:  
<ol>
<li>Dependencies:</li>  
<ul>
<li>For compilation you need g++ and make installed (glib in case of debug builds).</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Debian commands: sudo apt install build-essential  <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;sudo apt install libglib2.0-dev  
<li>For running the unit tests you need gcov and perl installed.</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Debian command: sudo apt install perl  
<li>For running the automated tests you need bash and perl installed.</li>  
<li>For generating the documentation you need doxygen installed.</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Debian command: sudo apt install doxygen  
<li>For formatting the code you need clang-format installed.</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Debian command: sudo apt install clang-format  
</ul>
<li> Build:</li>  
<ul>
<li>Debug build: make</li>  
<li>The documentation is present in docs/html/index.html.</li>  
&nbsp;&nbsp;&nbsp;&nbsp;To only generate documentation run: make doxygen  
<li>The binaries are present in Heap-of-Battle.</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Run Heap-of-Battle.sh to start the game.  
<li>For patches open a Pull Request. Check if there are any available Issues, see the TODO section in  <br>
the documentation or suggest changes. </li>  
</ul>
</ol>
  
Basic introduction into the code:  
<ol>
<li>Directories:</li>
<ul>
<li>hob</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Executable where the graphical interface and inputs of the game are handled.  
<li>hob-Game</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Library where the logical layers of the in-game maps is.  
<li>hob-Server</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Library where the server is, loaded by the game in the case of LAN.  
<li>hob-Server-Instance</li>  
&nbsp;&nbsp;&nbsp;&nbsp;Executable loading the server and hosting the game.  
</ul>
<li>Key methods:</li>
<ul>
<li>Entry point</li>  
&nbsp;&nbsp;&nbsp;&nbsp;hob/src/Main/hob_Main.cpp that runs hob/src/Main/hob_Game.cpp  <br>
&nbsp;&nbsp;&nbsp;&nbsp;this file initializes everything (Plog - logging library, SDL2 - library  <br>
&nbsp;&nbsp;&nbsp;&nbsp;that abstracts the window creation, user inputs, sounds, etc.).  
<li>Main game loop</li>  
&nbsp;&nbsp;&nbsp;&nbsp;hob/src/Main/hob_Game.cpp: Game::sceneLoop() runs instances of classes that  <br>
&nbsp;&nbsp;&nbsp;&nbsp;extend hob/include/Common/hob_Loop.hpp that when are finished lead to other scenes.  
<li>Scene loop</li>  
&nbsp;&nbsp;&nbsp;&nbsp;classes that extend hob/include/Common/hob_Loop.hpp need to implement draw() and handleEvent().  <br>
&nbsp;&nbsp;&nbsp;&nbsp;In the first methods that draw textures to the screen are called (this is called 60 times per  <br>
&nbsp;&nbsp;&nbsp;&nbsp;second if possible) and the second is called when a user input is avaialbe.  
<li>Utilitary classes</li>  
&nbsp;&nbsp;&nbsp;&nbsp;hob/include/Common/hob_TextureInitializer.hpp initializes textures and draws them to the screen.  <br>
&nbsp;&nbsp;&nbsp;&nbsp;hob/include/Common/hob_SoundInitializer.hpp initializes sounds and plays them.  <br>
&nbsp;&nbsp;&nbsp;&nbsp;hob/include/Game/Common this is where the classes that are used by the game scenes.  
</ul>
</ol>
  
For any questions feel free to contact me at stefan.gaina01@gmail.com.  
