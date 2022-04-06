#include "inc/pieces.hpp"
#include "inc/global.hpp"

void Pieces::King(int piece, int x, int y, int moves[][8], int chessPieces[][8]) {
    int tempMoves[8][8];
    int tempChessPieces[8][8];
    
    // stores temp moves
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            tempMoves[a][b] = moves[a][b];
        }
    }

    // stores temp chess pieces
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            tempChessPieces[a][b] = chessPieces[a][b];
        }
    }

    // resets moves
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            moves[a][b] = 0;
        }
    }

    // place king in every possible position
    if ((y - 1) >= 0) {
        if (chessPieces[y-1][x] == 0 || chessPieces[y-1][x] < 7) {
            chessPieces[y-1][x] = piece;
        }
        if ((x - 1) >= 0) {
            if (chessPieces[y-1][x-1] == 0 || chessPieces[y-1][x-1] < 7) {
                chessPieces[y-1][x-1] = piece;
            }
        }
        if ((x + 1) < 8) {
            if (chessPieces[y-1][x+1] == 0 || chessPieces[y-1][x+1] < 7) {
                chessPieces[y-1][x+1] = piece;
            }
        }
    }
    if ((x - 1) >= 0) {
        if (chessPieces[y][x-1] == 0 || chessPieces[y][x-1] < 7) {
            chessPieces[y][x-1] = piece;
        }
    }
    if ((x + 1) < 8) {
        if (chessPieces[y][x+1] == 0 || chessPieces[y][x+1] < 7) {
            chessPieces[y][x+1] = piece;
        }
    }
    if ((y + 1) < 8) {
        if (chessPieces[y+1][x] == 0 || chessPieces[y+1][x] < 7) {
            chessPieces[y+1][x] = piece;
        }
        if ((x - 1) >= 0) {
            if (chessPieces[y+1][x-1] == 0 || chessPieces[y+1][x-1] < 7) {
                chessPieces[y+1][x-1] = piece;
            }
        }
        if ((x + 1) < 8) {
            if (chessPieces[y+1][x+1] == 0 || chessPieces[y+1][x+1] < 7) {
                chessPieces[y+1][x+1] = piece;
            }
        }
    }

    // calc move for every opposing piece except other king
    int _calcPieces[5];
    if (piece == 8) {
        _calcPieces[0] = 1;
        _calcPieces[1] = 3;
        _calcPieces[2] = 4;
        _calcPieces[3] = 5;
        _calcPieces[4] = 6;
    } else {
        _calcPieces[0] = 7;
        _calcPieces[1] = 9;
        _calcPieces[2] = 10;
        _calcPieces[3] = 11;
        _calcPieces[4] = 12;
    }
    for (int _cx = 0; _cx < 8; _cx++) {
        for (int _cy = 0; _cy < 8; _cy++) {
            int _p = chessPieces[_cy][_cx];
            for (int _cp : _calcPieces) {
                if (_p == _cp) {
                    calculateMoves(_cp, _cx, _cy, true);
                }
            }
        }
    }

    // reset pieces
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            chessPieces[a][b] = tempChessPieces[a][b];
        }
    }

    if ((y - 1) >= 0) {
        if (chessPieces[y-1][x] == 0 && moves[y-1][x] == 0) {
            tempMoves[y-1][x] = 1;
        } else if (piece == 8 && chessPieces[y-1][x] < 7 && moves[y-1][x] == 0) {
            tempMoves[y-1][x] = 2;
        } else if (piece == 2 && chessPieces[y-1][x] > 6 && moves[y-1][x] == 0) {
            tempMoves[y-1][x] = 2;
        }
        if ((x - 1) >= 0) {
            if (chessPieces[y-1][x-1] == 0 && moves[y-1][x-1] == 0) {
                tempMoves[y-1][x-1] = 1;
            } else if (piece == 8 && chessPieces[y-1][x-1] < 7 && moves[y-1][x-1] == 0) {
                tempMoves[y-1][x-1] = 2;
            } else if (piece == 2 && chessPieces[y-1][x-1] > 6 && moves[y-1][x-1] == 0) {
                tempMoves[y-1][x-1] = 2;
            }
        }
        if ((x + 1) < 8) {
            if (chessPieces[y-1][x+1] == 0 && moves[y-1][x+1] == 0) {
                tempMoves[y-1][x+1] = 1;
            } else if (piece == 8 && chessPieces[y-1][x+1] < 7 && moves[y-1][x+1] == 0) {
                tempMoves[y-1][x+1] = 2;
            } else if (piece == 2 && chessPieces[y-1][x+1] > 6 && moves[y-1][x+1] == 0) {
                tempMoves[y-1][x+1] = 2;
            }
        }
    }
    if ((x - 1) >= 0) {
        if (chessPieces[y][x-1] == 0 && moves[y][x-1] == 0) {
            tempMoves[y][x-1] = 1;
        } else if (piece == 8 && chessPieces[y][x-1] < 7 && moves[y][x-1] == 0) {
            tempMoves[y][x-1] = 2;
        } else if (piece == 2 && chessPieces[y][x-1] > 6 && moves[y][x-1] == 0) {
            tempMoves[y][x-1] = 2;
        }
    }
    if ((x + 1) < 8) {
        if (chessPieces[y][x+1] == 0 && moves[y][x+1] == 0) {
            tempMoves[y][x+1] = 1;
        } else if (piece == 8 && chessPieces[y][x+1] < 7 && moves[y][x+1] == 0) {
            tempMoves[y][x+1] = 2;
        } else if (piece == 2 && chessPieces[y][x+1] > 6 && moves[y][x+1] == 0) {
            tempMoves[y][x+1] = 2;
        }
    }
    if ((y + 1) < 8) {
        if (chessPieces[y+1][x] == 0 && moves[y+1][x] == 0) {
            tempMoves[y+1][x] = 1;
        } else if (piece == 8 && chessPieces[y+1][x] < 7 && moves[y+1][x] == 0) {
            tempMoves[y+1][x] = 2;
        } else if (piece == 2 && chessPieces[y+1][x] > 6 && moves[y+1][x] == 0) {
            tempMoves[y+1][x] = 2;
        }
        if ((x - 1) >= 0) {
            if (chessPieces[y+1][x-1] == 0 && moves[y+1][x-1] == 0) {
                tempMoves[y+1][x-1] = 1;
            } else if (piece == 8 && chessPieces[y+1][x-1] < 7 && moves[y+1][x-1] == 0) {
                tempMoves[y+1][x-1] = 2;
            } else if (piece == 2 && chessPieces[y+1][x-1] > 6 && moves[y+1][x-1] == 0) {
                tempMoves[y+1][x-1] = 2;
            }
        }
        if ((x + 1) < 8) {
            if (chessPieces[y+1][x+1] == 0 && moves[y+1][x+1] == 0) {
                tempMoves[y+1][x+1] = 1;
            } else if (piece == 8 && chessPieces[y+1][x+1] < 7 && moves[y+1][x+1] == 0) {
                tempMoves[y+1][x+1] = 2;
            } else if (piece == 2 && chessPieces[y+1][x+1] > 6 && moves[y+1][x+1] == 0) {
                tempMoves[y+1][x+1] = 2;
            }
        }
    }

    // restore from tempMoves
    for (int a = 0; a < 8; a++) {
        for (int b = 0; b < 8; b++) {
            moves[a][b] = tempMoves[a][b];
        }
    }
}