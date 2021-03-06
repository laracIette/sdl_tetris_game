#include "Map.h"
#include "TextureManager.h"
#include "Global.h"
#include <iostream>

Map::Map()
{
    mapTex = TextureManager::LoadTexture( "assets\\map.png" );

    colors[1] = TextureManager::LoadTexture( "assets\\bleu.png" );
    colors[2] = TextureManager::LoadTexture( "assets\\cyan.png" );
    colors[3] = TextureManager::LoadTexture( "assets\\jaune.png" );
    colors[4] = TextureManager::LoadTexture( "assets\\orange.png" );
    colors[5] = TextureManager::LoadTexture( "assets\\rose.png" );
    colors[6] = TextureManager::LoadTexture( "assets\\vert.png" );

    src.x = 0;
    src.y = 0;
    src.w = 1920;
    src.h = 1080;

    dest.x = 0;
    dest.y = 0;
    dest.w = WIDTH;
    dest.h = HEIGHT;

    tileSrc.x = 0;
    tileSrc.y = 0;
    tileSrc.w = 78;
    tileSrc.h = 78;

    tileDest.x = 0;
    tileDest.y = 0;
    tileDest.w = 35 * WIDTH / 1920;
    tileDest.h = 35 * HEIGHT / 1080;

    topX = 786 * WIDTH / 1920;
    topY = 191 * HEIGHT / 1080;

    isUpdated = true;

    offsetX = 2;
    offsetY = 0;

}

Map::~Map()
{
}

void Map::Update( Piece *pce )
{
    isUpdated = false;

    piecePosX.clear();
    piecePosY.clear();

    for( int X{ 0 }; X < 4; ++X )
    {
        for( int Y{ 0 }; Y < 4; ++Y )
        {
            if( pce->pieceMap[Y][X] )
            {
                tilesMap[Y+offsetY][X+offsetX] = pce->pieceMap[Y][X];
                piecePosX.push_back( X+offsetX );
                piecePosY.push_back( Y+offsetY );
            }
        }
    }
}

bool Map::MovePiece( int dir, Piece *pce )
{
    isUpdated = true;

    if( dir == LEFT )
    {
        if( !PieceAtBorder( LEFT ) )
        {
            ReplaceTiles();
            offsetX--;
        }
    }
    else if( dir == RIGHT )
    {
        if( !PieceAtBorder( RIGHT ) )
        {
            ReplaceTiles();
            offsetX++;
        }
    }
    else if( dir == DOWN )
    {
        if( !PieceAtBorder( DOWN ) )
        {
            ReplaceTiles();
            offsetY++;
        }
        else
        {
            return false;
        }
    }
    return true;
}

void Map::MovePieceBottom( Piece *pce )
{
    for(;;)
    {
        if( !PieceAtBorder( DOWN ) )
        {
            ReplaceTiles();
            offsetY++;
            Update( pce );
        }
        else
        {
            break;
        }
    }
}

void Map::ReplaceTiles()
{
    isUpdated = true;

    for( int i{ 0 }; i < piecePosX.size(); ++i )
    {
        tilesMap[piecePosY[i]][piecePosX[i]] = 0;
    }
}

bool Map::PieceAtBorder( int bor )
{
    if( bor != DOWN )
    {
        for( int posX : piecePosX )
        {
            if( (bor == LEFT)  && (posX == 0) ) return true;
            if( (bor == RIGHT) && (posX == 9) ) return true;
        }
    }
    else
    {
        FindPieceDownBorder();
        for( int i{ 0 }; i < pieceBordersPos.size(); ++i )
        {
            if( tilesMap[pieceBordersPos[i][0] + 1][pieceBordersPos[i][1]] )
            {
                return true;
            }
        }

        for( int posY : piecePosY )
        {
            if( posY == 19 ) return true;
        }
    }
    return false;
}

void Map::FindPieceDownBorder()
{
    int max;
    int oldPosX;

    pieceBordersPos.clear();

    for( int posX : piecePosX )
    {
        if( oldPosX == posX ) continue;

        oldPosX = posX;

        max = 0;
        for( int posY : piecePosY )
        {
            if( !tilesMap[posY][posX] ) continue;

            if( posY > max )
            {
                max = posY;
            }
        }
        pieceBordersPos.push_back( {max, posX} );
    }
}

//bool Map::PieceAtTop()
//{
//    if( tilesMap[0][5] || tilesMap[0][6] )
//    {
//        return true;
//    }
//    return false;
//}

void Map::IsLineFull()
{
    bool isRowFull;

    for( int row{ 0 }; row < 20; ++row )
    {
        isRowFull = true;
        for( int column{ 0 }; column < 10; ++column )
        {
            if( !tilesMap[row][column] )
            {
                isRowFull = false;
                break;
            }
        }

        if( !isRowFull )
        {
            continue;
        }

        for( int rowInf{ row - 1 }; rowInf > 1; --rowInf )
        {
            for( int column{ 0 }; column < 10; ++column )
            {
                tilesMap[rowInf+1][column] = tilesMap[rowInf][column];
            }
        }
    }
}

void Map::Reset()
{
    offsetX = 2;
    offsetY = 0;
    piecePosX.clear();
    piecePosY.clear();
    pieceBordersPos.clear();
}

void Map::DrawMap()
{

    TextureManager::DrawTexture( mapTex, src, dest );

    for( int X{ 0 }; X < 10; ++X )
    {
        for( int Y{ 0 }; Y < 20; ++Y )
        {
            if( tilesMap[Y][X] )
            {
                tileDest.x = X * tileDest.w + topX;
                tileDest.y = Y * tileDest.h + topY;
                TextureManager::DrawTexture( colors[tilesMap[Y][X]], tileSrc, tileDest );
            }
        }
    }

}