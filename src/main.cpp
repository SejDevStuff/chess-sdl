#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cctype>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <stdint.h>
#include <iostream>
#include <fstream>

#include "inc/pieces.hpp"
#include "inc/global.hpp"

Pieces piecesClass;

const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 450;

bool quit = false;

/*
*   States
*   0 = main menu
*   1 = game
*/
int state = 0;

/*
    0 = empty
    1 = black bishop
    2 = black king
    3 = black knight
    4 = black pawn
    5 = black queen
    6 = black rook
    7 = white bishop 
    8 = white king
    9 = white knight
    10 = white pawn
    11 = white queen
    12 = white rook
*/
int defaultChessPieces[8][8] = {
    {6, 3, 1, 5, 2, 1, 3, 6},
    {4, 4, 4, 4, 4, 4, 4, 4},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {10, 10, 10, 10, 10, 10, 10, 10},
    {12, 9, 7, 11, 8, 7, 9, 12}
};

int lastChessPieceState[8][8];
int savedStates = 0;

int chessPieces[8][8] = {
    {6, 3, 1, 5, 2, 1, 3, 6},
    {4, 4, 4, 4, 4, 4, 4, 4},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {10, 10, 10, 10, 10, 10, 10, 10},
    {12, 9, 7, 11, 8, 7, 9, 12}
};

/*
    0 = cant move there
    1 = can move there
    2 = can move there and there is a piece you can capture
*/
int moves[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int whiteMoves = true;

SDL_Window* mWindow = NULL;
SDL_Surface* mScreenSurface = NULL;
SDL_Renderer* mRenderer = NULL;
SDL_Event e;

bool holdMouseDown = false;

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Failed to init SDL! Error: %s\n", SDL_GetError());
        success = false;
    } else {
        if (TTF_Init() < 0) {
            printf("Failed to init TTF! Error: %s\n", TTF_GetError());
            success = false;
        } else {
            mWindow = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
            if (mWindow == NULL) {
                printf("Could not create window! Error: %s", SDL_GetError());
                success = false;
            } else {
                mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
                if (mRenderer == NULL) {
                    success = false;
                    printf("Failed to create renderer! Error: %s\n", SDL_GetError());
                }
            }
        }
    }
    return success;
}

void close() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;
    mWindow = NULL;
    TTF_Quit();
    SDL_Quit();
}

void drawText(const char* file, int sz, uint8_t r, uint8_t g, uint8_t b, const char* text, int x, int y, int w, int h) {
    TTF_Font* font = TTF_OpenFont(file, sz);
    SDL_Color colour = {r, g, b, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, colour);
    SDL_Texture* msg = SDL_CreateTextureFromSurface(mRenderer, surfaceMessage);
    SDL_Rect messageRect;
    messageRect.x = x;
    messageRect.y = y;
    messageRect.w = w;
    messageRect.h = h;
    SDL_RenderCopy(mRenderer, msg, NULL, &messageRect);
    SDL_DestroyTexture(msg);
    SDL_FreeSurface(surfaceMessage);
    TTF_CloseFont(font);
}

void drawImage(const char* imgPath, int x, int y, int wScale = 1, int hScale = 1) {
    SDL_Texture* img = IMG_LoadTexture(mRenderer, imgPath);
    int w, h;
    SDL_QueryTexture(img, NULL, NULL, &w, &h);
    SDL_Rect imgRect;
    imgRect.x = x;
    imgRect.y = y;
    imgRect.w = w * wScale;
    imgRect.h = h * hScale;
    SDL_RenderCopy(mRenderer, img, NULL, &imgRect);
    SDL_DestroyTexture(img);
}

void mainMenu() {
    SDL_RenderClear(mRenderer);

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                int x = e.button.x;
                int y = e.button.y;
                if ((x > 50) && (x < 50 + 150) && (y > 150) && (y < 150 + 50)) {
                    state = 1;
                }

                if ((x > 50) && (x < 50 + 150) && (y > 200) && (y < 200 + 50)) {
                    quit = true;
                }
            }
        }
    }
    drawText("./assets/semibold.ttf", 48, 255, 255, 255, "Chess Game", 50, 50, 300, 100);

    // buttons
    drawText("./assets/regular.ttf", 24, 255, 255, 255, "Start", 50, 150, 150, 50);
    drawText("./assets/regular.ttf", 24, 255, 255, 255, "Quit", 50, 200, 150, 50);
    
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            chessPieces[a][b] = defaultChessPieces[a][b];
        }
    }

    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            lastChessPieceState[a][b] = chessPieces[a][b];
        }
    }

    savedStates = 0;
    whiteMoves = true;

    SDL_RenderPresent(mRenderer);
}

void calculateMoves(int piece, int x, int y, bool noReset) {
    //reset
    if (!noReset) {
        for (int a = 0; a < 8; a++) {
            for (int b = 0; b < 8; b++) {
                moves[a][b] = 0;
            }
        }
    }

    switch (piece) {
        case 10: { // White pawn
            piecesClass.Pawn(piece, x, y, moves, chessPieces);
            break;
        }
            
        case 4: { // Black pawn
            piecesClass.Pawn(piece, x, y, moves, chessPieces);
            break;
        }
            
        case 8: { // White king
            piecesClass.King(piece, x, y, moves, chessPieces);
            break;
        }

        case 2: { // black king
            piecesClass.King(piece, x, y, moves, chessPieces);
            break;
        }

        case 9: { // white knight
            piecesClass.Knight(piece, x, y, moves, chessPieces);
            break;
        }

        case 3: { // black knight
            piecesClass.Knight(piece, x, y, moves, chessPieces);
            break;
        }
    }
    return;
}

int selPiece = 0, selPieceX = 0, selPieceY = 0;

std::string getFen() {
    std::string fen = "";
    for (int y = 0; y < 8; y++) {
        int blanks = 0;
        for (int x = 0; x < 8; x++) {
            int piece = chessPieces[y][x];
            switch(piece) {
                case 0: {
                    blanks++;
                    break;
                }
                if (blanks > 0) {
                    fen += std::to_string(blanks);
                    blanks = 0;
                }
                case 1: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "b";
                    break;
                }
                case 2: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "k";
                    break;
                }
                case 3: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "n";
                    break;
                }
                case 4: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "p";
                    break;
                }
                case 5: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "q";
                    break;
                }
                case 6: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "r";
                    break;
                }
                case 7: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "B";
                    break;
                }
                case 8: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "K";
                    break;
                }
                case 9: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "N";
                    break;
                }
                case 10: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "P";
                    break;
                }
                case 11: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "Q";
                    break;
                }
                case 12: {
                    if (blanks > 0) {
                        fen += std::to_string(blanks);
                        blanks = 0;
                    }
                    fen += "R";
                    break;
                }
            }
        }
        fen += "/";
        // if (blanks > 0) {
        //     fen += std::to_string(blanks);
        //     blanks = 0;
        // }
    }
    return fen;
}

void game() {
    SDL_RenderClear(mRenderer);
    int mouseX, mouseY;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                holdMouseDown = true;
                mouseX = e.button.x;
                mouseY = e.button.y;
                if ((mouseX > 450) && (mouseX < 450 + 150) && (mouseY > 50) && (mouseY < 50 + 50)) {
                    state = 0;
                }
                if ((mouseX > 450) && (mouseX < 450 + 300) && (mouseY > 300) && (mouseY < 300 + 50)) {
                    std::ofstream outputFile;
                    outputFile.open("match0.txt");
                    outputFile << getFen();
                    outputFile.close();
                }
                if ((mouseX > 450) && (mouseX < 450 + 300) && (mouseY > 0) && (mouseY < 0 + 50)) {
                    if (savedStates > 0) {
                        for (int a = 0; a < 8; a++) {
                            for (int b = 0; b < 8; b++) {
                                chessPieces[a][b] = lastChessPieceState[a][b];
                            }
                        }
                        whiteMoves = !whiteMoves;
                        savedStates = 0;
                    }
                }
                holdMouseDown = true;
            }
        }
        if (e.type == SDL_MOUSEBUTTONUP) {
            holdMouseDown = false;
            mouseX = e.button.x;
            mouseY = e.button.y;
            if ((mouseX > 10 && mouseX < (10 + (8 * 50))) && (mouseY > 10 && mouseY < (10 + (8 * 50)))) {
                for (int cY = 0; cY < 8; cY++) {
                    for (int cX = 0; cX < 8; cX++) {
                        int bX = 10 + (cX * 50);
                        int bY = 10 + (cY * 50);
                        if ((mouseX > bX && mouseX < bX + 50) && (mouseY > bY && mouseY < bY + 50)) {
                            int piece = chessPieces[cY][cX];
                            if (selPiece != 0) {
                                if (moves[cY][cX] == 1 || moves[cY][cX] == 2) {
                                    // save state
                                    for (int a = 0; a < 8; a++) {
                                        for (int b = 0; b < 8; b++) {
                                            lastChessPieceState[a][b] = chessPieces[a][b];
                                        }
                                    }
                                    savedStates = 1;
                                    chessPieces[selPieceY][selPieceX] = 0;
                                    chessPieces[cY][cX] = selPiece;
                                    whiteMoves = !whiteMoves;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (savedStates > 0) {
        drawText("./assets/regular.ttf", 24, 114, 48, 255, "Revert last move", 450, 0, 300, 50);
    }
    drawText("./assets/regular.ttf", 24, 114, 48, 255, "< Back", 450, 50, 150, 50);
    drawText("./assets/regular.ttf", 14, 114, 48, 255, "Write FEN to file", 450, 300, 300, 50);

    if (whiteMoves) {
        drawText("./assets/regular.ttf", 24, 255, 255, 255, "White moves", 450, 200, 150, 50);
    } else {
        drawText("./assets/regular.ttf", 24, 255, 255, 255, "Black moves", 450, 200, 150, 50);
    }

    int cX = 10;
    int cY = 10;

    // board
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if ((y % 2) == 0 && (x % 2) == 0) {
                drawImage("./assets/ChessBoard1.png", cX + (x * 50), cY + (y * 50));
            } else if ((y % 2) != 0 && (x % 2) != 0) {
                drawImage("./assets/ChessBoard1.png", cX + (x * 50), cY + (y * 50));
            } else {
                drawImage("./assets/ChessBoard0.png", cX + (x * 50), cY + (y * 50));
            }
        }
    }

    // pieces
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int piece = chessPieces[y][x];
            switch (piece) {
                case 1:
                    drawImage("./assets/pieces/b_bishop.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 2:
                    drawImage("./assets/pieces/b_king.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 3:
                    drawImage("./assets/pieces/b_knight.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 4:
                    drawImage("./assets/pieces/b_pawn.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 5:
                    drawImage("./assets/pieces/b_queen.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 6:
                    drawImage("./assets/pieces/b_rook.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 7:
                    drawImage("./assets/pieces/w_bishop.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 8:
                    drawImage("./assets/pieces/w_king.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 9:
                    drawImage("./assets/pieces/w_knight.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 10:
                    drawImage("./assets/pieces/w_pawn.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 11:
                    drawImage("./assets/pieces/w_queen.png", cX + (x * 50), cY + (y * 50));
                    break;
                case 12:
                    drawImage("./assets/pieces/w_rook.png", cX + (x * 50), cY + (y * 50));
                    break;
            }
        }
    }

    if (holdMouseDown) {
        if ((mouseX > 10 && mouseX < (10 + (8 * 50))) && (mouseY > 10 && mouseY < (10 + (8 * 50)))) {
            for (int cY = 0; cY < 8; cY++) {
                for (int cX = 0; cX < 8; cX++) {
                    int bX = 10 + (cX * 50);
                    int bY = 10 + (cY * 50);
                    if ((mouseX > bX && mouseX < bX + 50) && (mouseY > bY && mouseY < bY + 50)) {
                        int piece = chessPieces[cY][cX];
                        selPiece = piece;
                        if (piece != 0) {
                            if (whiteMoves && piece < 7) {
                                selPiece = 0;
                            } else if (!whiteMoves && piece > 6) {
                                selPiece = 0;
                            } else {
                                selPieceX = cX;
                                selPieceY = cY;
                                calculateMoves(piece, cX, cY);
                                for (int mY = 0; mY < 8; mY++) {
                                    for (int mX = 0; mX < 8; mX++) {
                                        if (moves[mY][mX] == 1) {
                                            drawImage("./assets/dot.png", 10 + (mX * 50), 10 + (mY * 50));
                                        } else if (moves[mY][mX] == 2) {
                                            drawImage("./assets/captureCircle.png", 10 + (mX * 50), 10 + (mY * 50));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    SDL_RenderPresent(mRenderer);
}

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void loadFen(std::string fen) {
    int x = 0, y = 0;

    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            defaultChessPieces[a][b] = 0;
        }
    }

    for (char& c : fen) {
        std::string s = std::string(1, c);
        if (s == "/") {
            y++;
            x = 0;
            std::cout << "[" << x << "," << y << "]: One line down" << std::endl;
        }
        if (s == "r") {
            defaultChessPieces[y][x] = 6;
            std::cout << "[" << x << "," << y << "]: Black rook" << std::endl;
            x++;
        }
        if (s == "n") {
            defaultChessPieces[y][x] = 3;
            std::cout << "[" << x << "," << y << "]: Black knight" << std::endl;
            x++;
        }
        if (s == "b") {
            defaultChessPieces[y][x] = 1;
            std::cout << "[" << x << "," << y << "]: Black bishop" << std::endl;
            x++;
        }
        if (s == "q") {
            std::cout << "[" << x << "," << y << "]: Black queen" << std::endl;
            defaultChessPieces[y][x] = 5;
            x++;
        }
        if (s == "k") {
            std::cout << "[" << x << "," << y << "]: Black king" << std::endl;
            defaultChessPieces[y][x] = 2;
            x++;
        }
        if (s == "p") {
            std::cout << "[" << x << "," << y << "]: Black pawn" << std::endl;
            defaultChessPieces[y][x] = 4;
            x++;
        }
        if (s == "R") {
            std::cout << "[" << x << "," << y << "]: White rook" << std::endl;
            defaultChessPieces[y][x] = 12;
            x++;
        }
        if (s == "N") {
            std::cout << "[" << x << "," << y << "]: White knight" << std::endl;
            defaultChessPieces[y][x] = 9;
            x++;
        }
        if (s == "B") {
            std::cout << "[" << x << "," << y << "]: White bishop" << std::endl;
            defaultChessPieces[y][x] = 7;
            x++;
        }
        if (s == "Q") {
            std::cout << "[" << x << "," << y << "]: White queen" << std::endl;
            defaultChessPieces[y][x] = 11;
            x++;
        }
        if (s == "K") {
            std::cout << "[" << x << "," << y << "]: White king" << std::endl;
            defaultChessPieces[y][x] = 8;
            x++;

        }
        if (s == "P") {
            std::cout << "[" << x << "," << y << "]: White pawn" << std::endl;
            defaultChessPieces[y][x] = 10;
            x++;
        }
        if (std::isdigit(c)) {
            int d = std::atoi(s.c_str());
            std::cout << "[" << x << "," << y << "]: Skipping " << d << " spaces" << std::endl;
            for (int i = 0; i < d; i++) {
                defaultChessPieces[y][x] = 0;
                x++;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    char buff[100];
	getcwd(buff,sizeof(buff));
	std::cout << "Current directory = " << buff << std::endl;

    if (argc == 2) {
        char* fenString = argv[1];
        std::cout << "Loading custom FEN ..." << std::endl;
        loadFen(fenString);
    }

    if (!init()) {
        printf("Failed to init!");
    } else {
        while (!quit) {
            if (state == 0) {
                mainMenu();
            } else if (state == 1) {
                game();
            }
        }
    }

    close();
    return 0;
}