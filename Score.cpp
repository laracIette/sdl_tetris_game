#include "Score.h"
#include "TextureManager.h"
#include "Global.h"

Score::Score()
{
    for( int i{ 0 }; i < 10; ++i )
    {
        std::string strPath{ "assets\\" + std::to_string( i ) + ".png" };
        char *path = const_cast<char *>( strPath.c_str() );
        numbers[i] = TextureManager::LoadTexture( path );
    }

    src.x = 0;
    src.y = 0;
    src.w = 50;
    src.h = 60;


    dest.w = WIDTH/38;
    dest.h = HEIGHT/18;
    dest.x = WIDTH/2 - dest.w*2/1.3;
    dest.y = 905 * HEIGHT/1080;

    originX = dest.x;

}
Score::~Score()
{
}

void Score::Init()
{
    score = 0;
}

void Score::DrawScore()
{
    str = std::to_string( score );

    if     ( score < 10 ) str = "000" + str;
    else if( score < 100 ) str = "00" + str;
    else if( score < 1000 ) str = "0" + str;

    posX = 0;
    for( char letter : str )
    {
        dest.x = originX + dest.w/1.3 * posX++;
        TextureManager::DrawTexture( numbers[letter - '0'], src, dest );
    }
}
