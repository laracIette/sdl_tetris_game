#include "Highscore.h"

Highscore::Highscore()
{
    file = new File( "assets\\highscore.txt" );
    score = new Score();
    score->Init( GetHighscore() );
}
Highscore::~Highscore()
{
}

int Highscore::GetHighscore()
{
    file->GetLine();
    return strtoint( file->GetLine() );
}

void Highscore::SetHighscore( int scr )
{
    file->Write( std::to_string( scr ) );
    score->SetScore( scr );
}

void Highscore::DrawHighscore()
{
    score->DrawScore( 1 );
}
