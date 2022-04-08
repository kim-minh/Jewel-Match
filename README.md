# Jewel Match
Simple [Bejeweled](http://en.wikipedia.org/wiki/Bejeweled)/Match-3 game written in C++ and [SDL 2.0](http://www.libsdl.org). 

This was built and tested on an **M1 Mac with macOS Monterey**, but should work on other platforms as well.

<img width="912" alt="Jewel Match" src="https://user-images.githubusercontent.com/100175752/162377547-785401ae-42c5-4781-8e48-de26e9242277.png">

## Build Instruction

These instructions are for compilation with [Visual Studio Code](https://code.visualstudio.com/) on **macOS**. You can look for other compile instructions on [Lazy Foo' Productions](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php).

### Prerequisites

- First, install [Homebrew](https://brew.sh) using **Terminal** and follow the instruction:

    	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    
- Then do:
	
    	brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer
    
- After that, clone the repo:

    	git clone https://github.com/kim-minh/Jewel-Match.git
    
### Configure Visual Studio Code: 

- In *tasks.jsons*, add these within *"args"* to build the project:

      "${workspaceFolder}/src/*.cpp",
      "-I/opt/homebrew/include",
      "-I${workspaceFolder}/include",
      "-lSDL2", "-lSDL2main", "-lSDL2_image", "-lSDL2_ttf", "-lSDL2_mixer",
      "-L/opt/homebrew/lib",
      
- In *c_cpp_properties.json*, add these within *"includePath"* for Intellisense to work:

      "/opt/homebrew/include",
      "/opt/homebrew/lib"
      
Finally, **Run Build Task** in the directory of the cloned repo.      
      
## Design Idea

### Game state:

1. Initialize game's resources (texture, audio, ... )
- If unable to initialize, quit program and display error in **Terminal**.
-  Move to state 2.
2. Start screen
  - Board is initialized with random tiles that does not have any existing matches. Board is not drawn yet.
  - Check if there are any possible moves. There is a chance that the board will be generated without any possible moves.
  - If no moves are available, recreate the board.
3. Ready
  - Board is ready to be played (key press)
  - Start timer (Default is 120 seconds)
4. Idle detection
  - Check if there are any matching tiles due to user interaction.
  - Show hint after 10 seconds of idling.
5. Play
  - Select first tile, select second tile.
  - Swap selected tiles. 
  - If there is at least one match, destroy those that matches, else swap back.
6. Drop new tiles from above
  - Drops a single row of new tiles
  - Check the board for matches.
  - If there are matching tiles, destroy those and repeat state 6.
7. Board is now stable
  - Check if there is time left. If not, move to state 8.
  - Check if exist moves to match tiles. If not, randomize the tiles.
  - Go back to state 4.
8. Game over screen
  - Show game over text and final score.
  - Go back to state 3.
      
## Copyrights

Most of this project's assets was taken from [Freegemas](https://github.com/JoseTomasTocino/freegemas/) (GNU GPL v2)   

Background music *Easy Lemon* by [Kevin MacLeod](https://incompetech.com/music/royalty-free/index.html?isrc=USUAN1200076), licensed under [Creative Commons: By Attribution 3.0](https://creativecommons.org/licenses/by/3.0/)

Sound Effects *Game Start* and *Game Over* are from [Freesound](https://freesound.org/), licensed under [Creative Commons: By Attribution 3.0](https://creativecommons.org/licenses/by/3.0/)  

Font *Digital-7* by [Style-7](http://www.styleseven.com/php/get_product.php?product=Digital-7)

The rest of the project is licensed under GPLv3 (see LICENSE)
