#include "inc/pieces.hpp"

void Pieces::Knight(int piece, int x, int y, int moves[][8], int chessPieces[][8]) {
    if ((y - 2) > 0) {
        if ((x-1) > 0) {
            if (chessPieces[y-2][x-1] == 0) {
                moves[y-2][x-1] = 1;
            } else if (piece == 9 && chessPieces[y-2][x-1] < 7) {
                moves[y-2][x-1] = 2;
            } else if (piece == 3 && chessPieces[y-2][x-1] > 6) {
                moves[y-2][x-1] = 2;
            }
        }
        if ((x+1) < 8) {
            if (chessPieces[y-2][x+1] == 0) {
                moves[y-2][x+1] = 1;
            } else if (piece == 9 && chessPieces[y-2][x+1] < 7) {
                moves[y-2][x+1] = 2;
            } else if (piece == 3 && chessPieces[y-2][x+1] > 6) {
                moves[y-2][x+1] = 2;
            }
        }
    }
    if ((y + 2) < 8) {
        if ((x-1) > 0) {
            if (chessPieces[y+2][x-1] == 0) {
                moves[y+2][x-1] = 1;
            } else if (piece == 9 && chessPieces[y+2][x-1] < 7) {
                moves[y+2][x-1] = 2;
            } else if (piece == 3 && chessPieces[y+2][x-1] > 6) {
                moves[y+2][x-1] = 2;
            }
        }
        if ((x+1) < 8) {
            if (chessPieces[y+2][x+1] == 0) {
                moves[y+2][x+1] = 1;
            } else if (piece == 9 && chessPieces[y+2][x+1] < 7) {
                moves[y+2][x+1] = 2;
            } else if (piece == 3 && chessPieces[y+2][x+1] > 6) {
                moves[y+2][x+1] = 2;
            }
        }
    }

    if ((x - 2) > 0) {
        if ((y-1) > 0) {
            if (chessPieces[y-1][x-2] == 0) {
                moves[y-1][x-2] = 1;
            } else if (piece == 9 && chessPieces[y-1][x-2] < 7) {
                moves[y-1][x-2] = 2;
            } else if (piece == 3 && chessPieces[y-1][x-2] > 6) {
                moves[y-1][x-2] = 2;
            }
        }
        if ((y+1) < 8) {
            if (chessPieces[y+1][x-2] == 0) {
                moves[y+1][x-2] = 1;
            } else if (piece == 9 && chessPieces[y+1][x-2] < 7) {
                moves[y+1][x-2] = 2;
            } else if (piece == 3 && chessPieces[y+1][x-2] > 6) {
                moves[y+1][x-2] = 2;
            }
        }
    }
    if ((x + 2) < 8) {
        if ((y-1) > 0) {
            if (chessPieces[y-1][x+2] == 0) {
                moves[y-1][x+2] = 1;
            } else if (piece == 9 && chessPieces[y-1][x+2] < 7) {
                moves[y-1][x+2] = 2;
            } else if (piece == 3 && chessPieces[y-1][x+2] > 6) {
                moves[y-1][x+2] = 2;
            }
        }
        if ((y+1) < 8) {
            if (chessPieces[y+1][x+2] == 0) {
                moves[y+1][x+2] = 1;
            } else if (piece == 9 && chessPieces[y+1][x+2] < 7) {
                moves[y+1][x+2] = 2;
            } else if (piece == 3 && chessPieces[y+1][x+2] > 6) {
                moves[y+1][x+2] = 2;
            }
        }
    }
}