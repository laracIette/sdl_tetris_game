#pragma once

#include <string>
#include <SDL.h>

class Score
{
    int score;
    std::string str;

    SDL_Texture *numbers[10];

    SDL_Rect src, dest;
    int originX;
    int originY;
    int posX;

public:
    Score();
    ~Score();

    void Init( int scr = 0 );

    void Add( int scr ) { score += scr; }

    int GetScore() { return score; }
    int SetScore( int scr ) { score = scr; }

    void DrawScore( int y = 0 );
};