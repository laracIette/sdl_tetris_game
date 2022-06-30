#include "File.h"

File::File( std::string pth )
{
    path = pth;
    Open( std::ios::in );
}
File::~File()
{
}

void File::Open( std::ios_base::openmode mode )
{
    file.open( path, mode );
}

void File::Close()
{
    file.close();
}

void File::Write( std::string text )
{
    Open( std::ios::out );
    file << text;
    Close();
}

std::string File::GetLine()
{
    std::string temp;

    Open( std::ios::in );
    std::getline( file, temp );
    Close();

    return temp;

}
