#pragma once

class Piece
{
    int nPiece;
    int nRotate;
    int color;

public:
    Piece();
    ~Piece();

    void Init( int num, int clr );

    void Rotate( bool rot );

    int pieceMap[4][4];

};