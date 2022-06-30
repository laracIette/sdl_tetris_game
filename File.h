#pragma once

#include "Global.h"
#include <fstream>

class File
{
    std::string path;
    std::fstream file;

public:
    File( std::string pth );
    ~File();

    void Open( std::ios_base::openmode mode );
    void Write( std::string text );
    void Close();

    std::string GetLine();

};