#include "Pipe.h"
#include <iostream> 
#include <string> 
#include <fstream>
void Pipe::SetRemontpipe(bool peremennaya)
{
    remontpipe = peremennaya;
}
bool Pipe::GetRemontpipe() const
{
    return remontpipe;
}