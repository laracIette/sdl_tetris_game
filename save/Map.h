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
    SDL_Rect tileSrc, tileDest;

    int topX;
    int topY;

    int tilesMap[20][10];

    int offsetX;
    int offsetY;

    std::vector<int> piecePosX;
    std::vector<int> piecePosY;
    std::vector<std::array<int, 2> > pieceBordersPos;


public:
    Map();
    ~Map();

    void Update( Piece *pce );

    bool MovePiece( int dir, Piece *pce );
    void MovePieceBottom( Piece *pce );

    void ReplaceTiles();

    bool PieceAtBorder( int bor );
    void FindPieceDownBorder();
    void FindPieceLeftBorder();

    //bool PieceAtTop();

    void IsLineFull();

    void Reset();

    void DrawMap();

    bool isUpdated;

};