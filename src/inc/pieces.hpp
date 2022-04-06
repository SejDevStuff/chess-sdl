#pragma once
#include <iostream>
using namespace std;

class Pieces {
    public:
        void King(int piece, int x, int y, int moves[][8], int chessPieces[][8]);
        void Pawn(int piece, int x, int y, int moves[][8], int chessPieces[][8]);
        void Knight(int piece, int x, int y, int moves[][8], int chessPieces[][8]);
        void Rook(int piece, int x, int y, int moves[][8], int chessPieces[][8]);
    private:
        
};