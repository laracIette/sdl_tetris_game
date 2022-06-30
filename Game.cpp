#include "Game.h"
#include "Map.h"
#include "Global.h"
#include "Piece.h"
#include "Score.h"
#include "Highscore.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>


Map *map;
Score *score;
Highscore *highscore;

SDL_Renderer *Game::renderer = nullptr;

Game::Game()
{
}
Game::~Game()
{
}

void Game::Init( const char *title, int moveX, int moveY, bool fullscreen )
{

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
    }
    t( isRunning );

    srand( time( 0 ) );
    rand() % 1;


    map = new Map();
    score = new Score();
    score->Init();

    highscore = new Highscore();

    getTime( pieceStartTime );

    for( int i{ 0 }; i < KEYS; ++i )
    {
        f( keyPressed[i] );
        f( keyLock[i] );
    }

    f( isReset );
    f( isPaused );

}


void Game::HandleEvents()
{

    SDL_PollEvent( &event );

    switch( event.type )
    {
        case SDL_QUIT:
            f( isRunning );
            break;

        case SDL_KEYDOWN:
            for( int i{ 0 }; i < KEYS; ++i )
            {
                if( event.key.keysym.sym != keyCode[i] ) continue;

                if( !keyLock[i] )
                {
                    t( keyPressed[i] );
                    t( keyLock[i] );
                }
                break;
            }
            if( event.key.keysym.sym == SDLK_ESCAPE )
            {
                t( isPaused );
            }
            break;

        case SDL_KEYUP:
            for( int i{ 0 }; i < KEYS; ++i )
            {
                if( event.key.keysym.sym == keyCode[i] )
                {
                    f( keyLock[i] );
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
    while( isPaused )
    {
        SDL_PollEvent( &event );

        if( event.type != SDL_KEYDOWN )
        {
            continue;
        }

        if( event.key.keysym.sym == SDLK_LSHIFT )
        {
            f( isPaused );
            getTime( pieceStartTime );
            break;
        }
    }

    if( keyPressed[0] )
    {f( keyPressed[0] );

        map->RotatePiece( COUNTERCLOCKWISE );
        map->ReplaceTiles();
    }

    else if( keyPressed[1] )
    {     f( keyPressed[1] );

        map->RotatePiece( CLOCKWISE );
        map->ReplaceTiles();
    }

    else if( keyPressed[2] )
    {     f( keyPressed[2] );

        map->MovePiece( LEFT );
    }

    else if( keyPressed[3] )
    {     f( keyPressed[3] );

        map->MovePiece( RIGHT );
    }

    else if( keyPressed[4] )
    {     f( keyPressed[4] );

        if( map->MovePiece( DOWN ) )
        {
            pieceStartTime = SDL_GetTicks();
        }
    }

    else if( keyPressed[5] )
    {     f( keyPressed[5] );

        map->MovePieceBottom();
        score->Add( 1 );

        t( isReset );
    }

    else if( keyPressed[6] )
    {     f( keyPressed[6] );

        if( !map->HoldPiece() ) t( isReset );
    }


    if( (getTime() - pieceStartTime) > 1000 )
    {
        getTime( pieceStartTime );

        if( !map->MovePiece( DOWN ) )
        {
            score->Add( 1 );
            t( isReset );
        }
    }

    if( isReset )
    {
        f( isReset );
        Reset();
        t( map->isUpdated );
    }

    if( map->isUpdated )
    {
        score->Add( map->IsLineFull() );
        if( score->GetScore() > highscore->GetHighscore() )
        {
            highscore->SetHighscore( score->GetScore() );
        }
        map->Update();
        //if( map->PieceAtTop() )
        //    std::cout << "Piece at top!";
        //    f( isRunning );
    }
}

void Game::Render()
{
    SDL_RenderClear( renderer );

    map->DrawMap();
    score->DrawScore();
    highscore->DrawHighscore();

    SDL_RenderPresent( renderer );
}

void Game::Reset()
{
    getTime( pieceStartTime );
    map->Reset();
}

void Game::Clean()
{
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer( renderer );
    SDL_Quit();
}
