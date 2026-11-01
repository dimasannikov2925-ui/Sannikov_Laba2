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
std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Name: " << pipe.namepipe << "\n";
    out << "Dlina: " << pipe.dlinapipe << "\n";
    out << "Diametr: " << pipe.mmpipe << "\n";
    out << "Remont: " << pipe.GetRemontpipe() << "\n";

    return out;
}
