#pragma once

#include "Piece.h"
#include <SDL.h>
#include <vector>
#include <array>

class Map
{
    SDL_Texture *mapTex;
    SDL_Texture *colors[7];

    SDL_Rect src, dest;
    SDL_Rect tileSrc, tileDest, holdTileDest;

    int topX;
    int topY;

    int holdTopX;
    int holdTopY;

    int tilesMap[20][10];

    int offsetX;
    int offsetY;

    std::vector<int> piecePosX;
    std::vector<int> piecePosY;
    std::vector<std::array<int, 2> > pieceBordersPos;

    int lineFullBonus;

    int holdedPieceMap[4][4];
    int temp[4][4];

    int holdedNumber;
    int tempNumber;

public:
    Map();
    ~Map();

    void Update();

    bool MovePiece( int dir );
    void MovePieceBottom();

    void RotatePiece( int rot );

    void ReplaceTiles();

    bool PieceAtBorder( int bor );
    void FindPieceDownBorder();
    void FindPieceLeftBorder();
    void FindPieceRightBorder();

    //bool PieceAtTop();

    bool HoldPiece();

    int IsLineFull();

    void Reset();

    void DrawMap();

    bool isUpdated;

};