# chess-sdl
A chess game made in SDL2. This is a game I made so I can learn SDL2 and Chess at once.

## ⚠️ Warnings
- The game isn't finished
- Features such as "en passant" and "castling" are not implemented yet
- It's very buggy
- It's not pretty. I didn't really care about aesthetics, I just wanted to learn how to use SDL and the algorithms behind chess.

## 🔧 Building project
I'm too dumb to use makefiles, so if you're on MacOS or Linux, run ``build.sh`` in ``src/``, it will make a file called ``main`` in the root of the project directory.
If you're on Windows, well... good luck?

## 📷 Screenshots
![image](https://user-images.githubusercontent.com/60989665/161995137-02a6081f-722c-4b01-b916-11ac7e044aa9.png)

## FEN strings
This program uses a slightly modified version of [FEN strings](https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation) to store and retrieve data about where chess pieces are on the board.
It only uses the highlighted part of a typical FEN string to keep things simple:

![image](https://user-images.githubusercontent.com/60989665/161995831-fbeb26b9-36ce-4454-823e-14b6cb767444.png)

The FEN string implementation was originally meant for debugging purposes, 
but if you have an ongoing match you would like to save and continue later on, you can do so by clicking on "Write FEN  to file". Doing so writes the FEN string of the current chess game to a file called ``match0.txt`` in the current directory of the program.

To load a FEN string, just pass it as a commandline argument when starting the program: ``./main rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR``, if no argument is passed, the program defaults to the default starting position in chess.

**Disclaimer**: The FEN string does not save the active colour (i.e: what colour moves next), so the program will always default to white moving first.

The FEN string loaded when you run the program will remain the default arrangement of pieces until you restart the program (i.e: clicking back and then clicking start will reload the original FEN string passed to the program), this was because it was originally meant so you can try out different moves in certain conditions
