#pragma once

#include "File.h"
#include "Score.h"

class Highscore
{
    File *file;
    Score *score;

public:
    Highscore();
    ~Highscore();

    int GetHighscore();

    void SetHighscore( int scr );
    void DrawHighscore();
};