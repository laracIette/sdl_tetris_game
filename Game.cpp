#include "Game.h"
#include "Map.h"
#include "Global.h"
#include "Piece.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>


Map *map;

SDL_Renderer *Game::renderer = nullptr;

Game::Game()
{
}
Game::~Game()
{
}

void Game::Init( const char *title, int moveX, int moveY, bool fullscreen )
{
    isRunning = false;

    int flags{ 0 };
    if( fullscreen )
    {
        flags = SDL_WINDOW_FULLSCREEN;
        WIDTH = 1920;
        HEIGHT = 1080;
    }

    if( !SDL_Init( SDL_INIT_EVERYTHING ) );
    {
        window = SDL_CreateWindow( title, moveX, moveY, WIDTH, HEIGHT, flags );
        renderer = SDL_CreateRenderer( window, -1, 0 );
        if( renderer )
        {
            SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 );
        }

        isRunning = true;
    }

    srand( time( 0 ) );
    rand() % 1;


    map = new Map();

    pieceStartTime = SDL_GetTicks();

    isLCtrlPressed = false;
    isLAltPressed  = false;
    isLeftPressed  = false;
    isRightPressed = false;
    isDownPressed  = false;
    isSpacePressed = false;

    isLCtrlLock    = false;
    isLAltLock     = false;
    isLeftLock     = false;
    isRightLock    = false;
    isDownLock     = false;
    isSpaceLock    = false;

    isReset = false;

}


void Game::HandleEvents()
{

    SDL_PollEvent( &event );

    switch( event.type )
    {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            switch( event.key.keysym.sym )
            {
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;

                case SDLK_LCTRL:
                    if( !isLCtrlLock )
                    {
                        isLCtrlLock = true;
                        isLCtrlPressed = true;
                    }
                    break;

                case SDLK_LALT:
                    if( !isLAltLock )
                    {
                        isLAltLock = true;
                        isLAltPressed = true;
                    }
                    break;

                case SDLK_LEFT:
                    if( !isLeftLock )
                    {
                        isLeftLock = true;
                        isLeftPressed = true;
                    }
                    break;

                case SDLK_RIGHT:
                    if( !isRightLock )
                    {
                        isRightLock = true;
                        isRightPressed = true;
                    }
                    break;

                case SDLK_DOWN:
                    if( !isDownLock )
                    {
                        isDownLock = true;
                        isDownPressed = true;
                    }
                    break;

                case SDLK_SPACE:
                    if( !isSpaceLock )
                    {
                        isSpaceLock = true;
                        isSpacePressed = true;
                    }
                    break;

                default:
                    break;
            }
            break;

        case SDL_KEYUP:
            switch( event.key.keysym.sym )
            {
                case SDLK_LCTRL:
                    isLCtrlLock = false;
                    break;

                case SDLK_LALT:
                    isLAltLock = false;
                    break;

                case SDLK_LEFT:
                    isLeftLock = false;
                    break;

                case SDLK_RIGHT:
                    isRightLock = false;
                    break;

                case SDLK_DOWN:
                    isDownLock = false;
                    break;

                case SDLK_SPACE:
                    isSpaceLock = false;
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

}

void Game::Update()
{
    if( isLCtrlPressed )
    {   isLCtrlPressed = false;

        map->RotatePiece( COUNTERCLOCKWISE );
        map->ReplaceTiles();
    }

    else if( isLAltPressed )
    {        isLAltPressed  = false;

        map->RotatePiece( CLOCKWISE );
        map->ReplaceTiles();
    }

    else if( isLeftPressed )
    {        isLeftPressed  = false;

        map->MovePiece( LEFT );
    }

    else if( isRightPressed )
    {        isRightPressed = false;

        map->MovePiece( RIGHT );
    }

    else if( isDownPressed )
    {        isDownPressed  = false;

        if( map->MovePiece( DOWN ) )
        {
            pieceStartTime = SDL_GetTicks();
        }
    }

    else if( isSpacePressed )
    {        isSpacePressed = false;

        map->MovePieceBottom();

        isReset = true;
    }


    if( (SDL_GetTicks() - pieceStartTime) > 1000 )
    {
        pieceStartTime = SDL_GetTicks();

        if( !map->MovePiece( DOWN ) )
        {
            isReset = true;
        }
    }

    if( isReset )
    {
        isReset = false;
        Reset();
        map->isUpdated = true;
    }

    if( map->isUpdated )
    {
        map->IsLineFull();
        map->Update();
        //if( map->PieceAtTop() )
        //    std::cout << "Piece at top!";
        //    isRunning = false;
    }
}

void Game::Render()
{
    SDL_RenderClear( renderer );

    map->DrawMap();

    SDL_RenderPresent( renderer );
}

void Game::Reset()
{
    pieceStartTime = SDL_GetTicks();
    map->Reset();
}

void Game::Clean()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}
