#include "Map.h"
#include "TextureManager.h"
#include "Global.h"


#define FOR_Y_FOR_X_begin for( int Y{ 0 }; Y < 4; ++Y ) { for( int X{ 0 }; X < 4; ++X ) {
#define FOR_Y_FOR_X_end } }

Piece *piece;

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

    holdTileDest.x = 0;
    holdTileDest.y = 0;
    holdTileDest.w = 25 * WIDTH / 1920;
    holdTileDest.h = 25 * HEIGHT / 1080;

    holdTopX = 640 * WIDTH / 1920;
    holdTopY = 223 * HEIGHT / 1080;

    t( isUpdated );

    offsetX = 2;
    offsetY = 0;

    piece = new Piece();
    piece->Init( rand() % 7, (rand() % 6) + 1 );

}

Map::~Map()
{
}

void Map::Update()
{
    f( isUpdated );

    piecePosX.clear();
    piecePosY.clear();

    FOR_Y_FOR_X_begin
        if( piece->pieceMap[Y][X] )
        {
            tilesMap[Y+offsetY][X+offsetX] = piece->pieceMap[Y][X];
            piecePosX.push_back( X+offsetX );
            piecePosY.push_back( Y+offsetY );
        }
    FOR_Y_FOR_X_end
}

bool Map::MovePiece( int dir )
{
    t( isUpdated );

    switch( dir )
    {
        case LEFT:
            if( !PieceAtBorder( LEFT ) )
            {
                offsetX--;
                ReplaceTiles();
            }
            else
            {
                return false;
            }
            break;

        case RIGHT:
            if( !PieceAtBorder( RIGHT ) )
            {
                offsetX++;
                ReplaceTiles();
            }
            else
            {
                return false;
            }
            break;

        case DOWN:
            if( !PieceAtBorder( DOWN ) )
            {
                offsetY++;
                ReplaceTiles();
            }
            else
            {
                return false;
            }
            break;

        default:
            break;
    }
    return true;
}

void Map::MovePieceBottom()
{
    while( !PieceAtBorder( DOWN ) )
    {
        offsetY++;
        ReplaceTiles();
        Update();
    }
}

void Map::RotatePiece( int rot )
{
    piece->Rotate( rot );
}

void Map::ReplaceTiles()
{
    t( isUpdated );

    for( int i{ 0 }; i < piecePosX.size(); ++i )
    {
        tilesMap[piecePosY[i]][piecePosX[i]] = 0;
    }
}

bool Map::PieceAtBorder( int bor )
{
    switch( bor )
    {
        case LEFT:
            FindPieceLeftBorder();
            for( int i{ 0 }; i < pieceBordersPos.size(); ++i )
            {
                if( tilesMap[pieceBordersPos[i][0]][pieceBordersPos[i][1] - 1] )
                {
                    return true;
                }
            }

            return isIn( piecePosX, 0 );
            break;

        case RIGHT:
            FindPieceRightBorder();
            for( int i{ 0 }; i < pieceBordersPos.size(); ++i )
            {
                if( tilesMap[pieceBordersPos[i][0]][pieceBordersPos[i][1] + 1] )
                {
                    return true;
                }
            }

            return isIn( piecePosX, 9 );
            break;

        case DOWN:
            FindPieceDownBorder();
            for( int i{ 0 }; i < pieceBordersPos.size(); ++i )
            {
                std::cout << tilesMap[pieceBordersPos[i][0] + 1][pieceBordersPos[i][1]]
                << "Y+1 : " << pieceBordersPos[i][0] + 1
                << ", Y : " << pieceBordersPos[i][0]
                << ", X : " << pieceBordersPos[i][1] << '\n';

                if( tilesMap[pieceBordersPos[i][0] + 1][pieceBordersPos[i][1]] )
                {
                    std::cout << '\n';
                    return true;
                }
            }

            return isIn( piecePosY, 19 );
            break;

        default:
            break;
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

            if( posY > max ) max = posY;
        }
        pieceBordersPos.push_back( {max, posX} );
    }
}

void Map::FindPieceLeftBorder()
{
    int min;
    int oldPosY;

    pieceBordersPos.clear();

    for( int posY : piecePosY )
    {
        if( oldPosY == posY ) continue;

        oldPosY = posY;

        min = INT32_MAX;

        for( int posX : piecePosX )
        {
            if( !tilesMap[posY][posX] ) continue;

            if( posX < min ) min = posX;
        }
        pieceBordersPos.push_back( {posY, min} );
    }
}

void Map::FindPieceRightBorder()
{
    int max;
    int oldPosY;

    pieceBordersPos.clear();

    for( int posY : piecePosY )
    {
        if( oldPosY == posY ) continue;

        oldPosY = posY;

        max = 0;

        for( int posX : piecePosX )
        {
            if( !tilesMap[posY][posX] ) continue;

            if( posX > max ) max = posX;
        }
        pieceBordersPos.push_back( {posY, max} );
    }
}

bool Map::HoldPiece()
{
    bool isHolded{ false };

    FOR_Y_FOR_X_begin
        if( holdedPieceMap[Y][X] )
        {
            isHolded = true;
            break;
        }
    FOR_Y_FOR_X_end

    if( isHolded )
    {
        FOR_Y_FOR_X_begin
            temp[Y][X] = 0;
            if( holdedPieceMap[Y][X] ) temp[Y][X] = holdedPieceMap[Y][X];
        FOR_Y_FOR_X_end

        tempNumber = piece->GetNumber();
    }


    FOR_Y_FOR_X_begin
        if( holdedPieceMap[Y][X] ) holdedPieceMap[Y][X] = 0;

        if( piece->pieceMap[Y][X] )
        {
            holdedPieceMap[Y][X] = piece->pieceMap[Y][X];
        }
    FOR_Y_FOR_X_end

    ReplaceTiles();

    if( isHolded )
    {
        FOR_Y_FOR_X_begin
            if( piece->pieceMap[Y][X] ) piece->pieceMap[Y][X] = 0;

            if( temp[Y][X] )
            {
                piece->pieceMap[Y][X] = temp[Y][X];
            }
        FOR_Y_FOR_X_end
        piece->SetNumber( tempNumber );
    }

    return isHolded;
}

//bool Map::PieceAtTop()
//{
//    if( tilesMap[0][5] || tilesMap[0][6] )
//    {
//        return true;
//    }
//    return false;
//}

int Map::IsLineFull()
{
    lineFullBonus = 0;

    bool isRowFull;

    for( int row{ 0 }; row < 20; ++row )
    {
        t( isRowFull );
        for( int column{ 0 }; column < 10; ++column )
        {
            if( !tilesMap[row][column] )
            {
                f( isRowFull );
                break;
            }
        }

        if( !isRowFull )
        {
            continue;
        }

        lineFullBonus += 10 + lineFullBonus/10;

        for( int rowInf{ row - 1 }; rowInf > 1; --rowInf )
        {
            for( int column{ 0 }; column < 10; ++column )
            {
                tilesMap[rowInf+1][column] = tilesMap[rowInf][column];
            }
        }
    }

    return lineFullBonus;
}

void Map::Reset()
{
    offsetX = 2;
    offsetY = 0;
    piecePosX.clear();
    piecePosY.clear();

    piece->Init( rand() % 7, (rand() % 6) + 1 );

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

    FOR_Y_FOR_X_begin
        if( holdedPieceMap[Y][X] )
        {
            holdTileDest.x = X * holdTileDest.w + holdTopX;
            holdTileDest.y = Y * holdTileDest.h + holdTopY;
            TextureManager::DrawTexture( colors[holdedPieceMap[Y][X]], tileSrc, holdTileDest );
        }
    FOR_Y_FOR_X_end

}