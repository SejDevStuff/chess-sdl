#include "inc/pieces.hpp"

void Pieces::Pawn(int piece, int x, int y, int moves[][8], int chessPieces[][8]) {
    if (piece == 10) {
        if ((y-1) >= 0) {
            if (chessPieces[y-1][x] == 0) {
                moves[y-1][x] = 1;
            }
            if (y == 6) {
                moves[y-2][x] = 1;
            }
            if ((x-1) >= 0) {
                if (piece == 10 && chessPieces[y-1][x-1] != 0 && chessPieces[y-1][x-1] < 7) {
                    moves[y-1][x-1] = 2;
                }
            }
            if ((x+1) < 8) {
                if (piece == 10 && chessPieces[y-1][x+1] != 0 && chessPieces[y-1][x+1] < 7) {
                    moves[y-1][x+1] = 2;
                }
            }
        }
    } else if (piece == 4) {
        if ((y+1) < 8) {
            if (chessPieces[y+1][x] == 0) {
                moves[y+1][x] = 1;
            }
            if (y == 1) {
                moves[y+2][x] = 1;
            }
            if ((x+1) < 8) {
                if (chessPieces[y+1][x+1] != 0 && chessPieces[y+1][x+1] > 6) {
                    moves[y+1][x+1] = 2;
                }
            }
            if ((x-1) >= 0) {
                if (chessPieces[y+1][x-1] != 0 && chessPieces[y+1][x-1] > 6) {
                    moves[y+1][x-1] = 2;
                }
            }
        }
    }
}