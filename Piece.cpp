#include "Piece.h"
#include "Global.h"

Piece::Piece()
{
}

Piece::~Piece()
{
}

void Piece::Init( int num, int clr  )
{

    nPiece = num;
    color = clr;

    nRotate = 0;

    for( int X{ 0 }; X < 4; ++X )
        for( int Y{ 0 }; Y < 4; ++Y )
            pieceMap[Y][X] = 0;

    switch( nPiece )
    {
        case 0:
            pieceMap[0][2] = color;
            pieceMap[1][2] = color;
            pieceMap[2][2] = color;
            pieceMap[3][2] = color;
            break;

        case 1:
            pieceMap[0][2] = color;
            pieceMap[1][2] = color;
            pieceMap[1][3] = color;
            pieceMap[2][2] = color;
            break;

        case 2:
            pieceMap[0][3] = color;
            pieceMap[1][1] = color;
            pieceMap[1][2] = color;
            pieceMap[1][3] = color;
            break;

        case 3:
            pieceMap[0][2] = color;
            pieceMap[0][3] = color;
            pieceMap[1][2] = color;
            pieceMap[1][3] = color;
            break;

        case 4:
            pieceMap[0][1] = color;
            pieceMap[0][2] = color;
            pieceMap[1][0] = color;
            pieceMap[1][1] = color;
            break;

        case 5:
            pieceMap[0][2] = color;
            pieceMap[1][2] = color;
            pieceMap[2][1] = color;
            pieceMap[2][2] = color;
            break;

        case 6:
            pieceMap[0][1] = color;
            pieceMap[0][2] = color;
            pieceMap[1][2] = color;
            pieceMap[1][3] = color;
            break;

        default:
            break;
    }
}

void Piece::Rotate( bool rot )
{
    for( int X{ 0 }; X < 4; ++X )
        for( int Y{ 0 }; Y < 4; ++Y )
            pieceMap[Y][X] = 0;

    if( rot == CLOCKWISE ) nRotate++;
    else                   nRotate--;

    if( nRotate == 4 ) nRotate = 0;
    else if( nRotate == -1 ) nRotate = 3;

    switch( nRotate )
    {
        case 0:
            switch( nPiece )
            {
                case 0:
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    pieceMap[3][2] = color;
                    break;

                case 1:
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    pieceMap[2][2] = color;
                    break;

                case 2:
                    pieceMap[0][3] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 3:
                    pieceMap[0][2] = color;
                    pieceMap[0][3] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 4:
                    pieceMap[0][1] = color;
                    pieceMap[0][2] = color;
                    pieceMap[1][0] = color;
                    pieceMap[1][1] = color;
                    break;

                case 5:
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][1] = color;
                    pieceMap[2][2] = color;
                    break;

                case 6:
                    pieceMap[0][1] = color;
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                default:
                    break;

            }
            break;

        case 1:
            switch( nPiece )
            {
                case 0:
                    pieceMap[2][0] = color;
                    pieceMap[2][1] = color;
                    pieceMap[2][2] = color;
                    pieceMap[2][3] = color;
                    break;

                case 1:
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    pieceMap[2][2] = color;
                    break;

                case 2:
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    pieceMap[2][3] = color;
                    break;

                case 3:
                    pieceMap[0][2] = color;
                    pieceMap[0][3] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 4:
                    pieceMap[0][1] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    break;

                case 5:
                    pieceMap[0][1] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 6:
                    pieceMap[0][2] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][1] = color;
                    break;

                default:
                    break;
            }
            break;

        case 2:
            switch( nPiece )
            {
                case 0:
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    pieceMap[3][2] = color;
                    break;

                case 1:
                    pieceMap[0][2] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    break;

                case 2:
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    pieceMap[2][1] = color;
                    break;

                case 3:
                    pieceMap[0][2] = color;
                    pieceMap[0][3] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 4:
                    pieceMap[0][1] = color;
                    pieceMap[0][2] = color;
                    pieceMap[1][0] = color;
                    pieceMap[1][1] = color;
                    break;

                case 5:
                    pieceMap[0][2] = color;
                    pieceMap[0][3] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    break;

                case 6:
                    pieceMap[0][1] = color;
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                default:
                    break;
            }
            break;

        case 3:
            switch( nPiece )
            {
                case 0:
                    pieceMap[2][0] = color;
                    pieceMap[2][1] = color;
                    pieceMap[2][2] = color;
                    pieceMap[2][3] = color;
                    break;

                case 1:
                    pieceMap[0][2] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 2:
                    pieceMap[0][1] = color;
                    pieceMap[0][2] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    break;

                case 3:
                    pieceMap[0][2] = color;
                    pieceMap[0][3] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    break;

                case 4:
                    pieceMap[0][1] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][2] = color;
                    break;

                case 5:
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[1][3] = color;
                    pieceMap[2][3] = color;
                    break;

                case 6:
                    pieceMap[0][2] = color;
                    pieceMap[1][1] = color;
                    pieceMap[1][2] = color;
                    pieceMap[2][1] = color;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;

    }
}