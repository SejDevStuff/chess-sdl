#include "inc/pieces.hpp"
void Pieces::Rook(int piece, int x, int y, int moves[][8], int chessPieces[][8]) {
    int squaresUp = y+1;
    int squaresDown = 8 - y;
    int squaresLeft = x+1;
    int squaresRight = 8 - x;
    
    for (int i = 1; i < squaresUp; i++) {
        int newY = y - i;
        if (chessPieces[newY][x] == 0) {
            moves[newY][x] = 1;
        } else if (piece == 12 && chessPieces[newY][x] < 7) {
            moves[newY][x] = 2;
            break;
        } else if (piece == 6 && chessPieces[newY][x] > 6) {
            moves[newY][x] = 2;
            break;
        } else {
            break;
        }
    }

    for (int i = 1; i < squaresDown; i++) {
        int newY = y + i;
        if (chessPieces[newY][x] == 0) {
            moves[newY][x] = 1;
        } else if (piece == 12 && chessPieces[newY][x] < 7) {
            moves[newY][x] = 2;
            break;
        } else if (piece == 6 && chessPieces[newY][x] > 6) {
            moves[newY][x] = 2;
            break;
        } else {
            break;
        }
    }

    for (int i = 1; i < squaresLeft; i++) {
        int newX = x - i;
        if (chessPieces[y][newX] == 0) {
            moves[y][newX] = 1;
        } else if (piece == 12 && chessPieces[y][newX] < 7) {
            moves[y][newX] = 2;
            break;
        } else if (piece == 6 && chessPieces[y][newX] > 6) {
            moves[y][newX] = 2;
            break;
        } else {
            break;
        }
    }

    for (int i = 1; i < squaresRight; i++) {
        int newX = x + i;
        if (chessPieces[y][newX] == 0) {
            moves[y][newX] = 1;
        } else if (piece == 12 && chessPieces[y][newX] < 7) {
            moves[y][newX] = 2;
            break;
        } else if (piece == 6 && chessPieces[y][newX] > 6) {
            moves[y][newX] = 2;
            break;
        } else {
            break;
        }
    }
}