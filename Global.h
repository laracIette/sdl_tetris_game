#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

extern int WIDTH;
extern int HEIGHT;
static const int FPS{ 60 };

static const int LEFT{ 1 };
static const int RIGHT{ 2 };
static const int DOWN{ 3 };

static const bool CLOCKWISE{ 1 };
static const bool COUNTERCLOCKWISE{ 0 };



template <typename T>
static T minimum( std::vector<T> vec )
{
    T min{ vec[0] };
    for( T n : vec )
    {
        if( n < min )
        {
            min = n;
        }
    }
    return min;
}

template <typename T>
static T maximum( std::vector<T> vec )
{
    T max{ vec[0] };
    for( T n : vec )
    {
        if( n > max )
        {
            max = n;
        }
    }
    return max;
}

template <typename T>
static bool isIn( std::vector<T> vec, T num )
{
    for( T n : vec )
    {
        if( n == num ) return true;
    }
    return false;
}



template <typename T>
int len( T arr )
{
    return (sizeof( arr ) / sizeof( arr[0] ));
}



static void t( bool &b ) // = true
{
    if( !b ) b = true;
}
static void f( bool &b ) // = false
{
    if( b ) b = false;
}


static int strtoint( std::string str )
{
    int result{ 0 };

    for( int i{ 0 }; i < str.size(); ++i )
    {
        switch( str[i] )
        {
            case '0': result = result*10; break;
            case '1': result = result*10 + 1; break;
            case '2': result = result*10 + 2; break;
            case '3': result = result*10 + 3; break;
            case '4': result = result*10 + 4; break;
            case '5': result = result*10 + 5; break;
            case '6': result = result*10 + 6; break;
            case '7': result = result*10 + 7; break;
            case '8': result = result*10 + 8; break;
            case '9': result = result*10 + 9; break;
        }
    }

    return result;
}


static Uint32 getTime()
{
    return SDL_GetTicks();
}
static void getTime( Uint32 &t )
{
    t = SDL_GetTicks();
}