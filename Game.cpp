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

    for( int i{ 0 }; i < KEYS; ++i )
    {
        keyPressed[i] = false;
        keyLock[i] = false;
    }

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
            if( event.key.keysym.sym == SDLK_ESCAPE )
            {
                isRunning = false;
            }
            else
            {
                for( int i{ 0 }; i < KEYS; ++i )
                {
                    if( event.key.keysym.sym != keyCode[i] )
                    {
                        continue;
                    }
                    if( !keyLock[i] )
                    {
                        keyPressed[i] = true;
                        keyLock[i] = true;
                    }
                    break;
                }
            }
            break;

        case SDL_KEYUP:
            for( int i{ 0 }; i < KEYS; ++i )
            {
                if( event.key.keysym.sym == keyCode[i] )
                {
                    keyLock[i] = false;
                    break;
                }
            }
            break;

        default:
            break;
    }

}

void Game::Update()
{
    if( keyPressed[0] )
    {   keyPressed[0] = false;

        map->RotatePiece( COUNTERCLOCKWISE );
        map->ReplaceTiles();
    }

    else if( keyPressed[1] )
    {        keyPressed[1] = false;

        map->RotatePiece( CLOCKWISE );
        map->ReplaceTiles();
    }

    else if( keyPressed[2] )
    {        keyPressed[2]  = false;

        map->MovePiece( LEFT );
    }

    else if( keyPressed[3] )
    {        keyPressed[3] = false;

        map->MovePiece( RIGHT );
    }

    else if( keyPressed[4] )
    {        keyPressed[4]  = false;

        if( map->MovePiece( DOWN ) )
        {
            pieceStartTime = SDL_GetTicks();
        }
    }

    else if( keyPressed[5] )
    {        keyPressed[5] = false;

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
