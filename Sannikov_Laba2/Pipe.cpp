#include "Pipe.h"
#include <iostream> 
#include <string> 
void Pipe::SetRemontpipe(bool peremennaya)
{
    remontpipe = peremennaya;
}
bool Pipe::GetRemontpipe() const
{
    return remontpipe;
}
void Pipe::SetNamepipe(std::string peremennaya)
{
    if (!peremennaya.empty())
        namepipe = peremennaya;
}
void Pipe::SetDlinapipe(double peremennaya)
{
    if (peremennaya > 0)
        dlinapipe = peremennaya;
}
void Pipe::SetMmpipe(int peremennaya)
{
    if (peremennaya > 0)
        mmpipe = peremennaya;
}
std::string Pipe::GetNamepipe() const
{
    return namepipe;
}
double Pipe::GetDlinapipe() const
{
    return dlinapipe;
}
int Pipe::GetMmpipe() const
{
    return mmpipe;
}
std::ostream& operator<<(std::ostream& out, const Pipe& pipe)
{
    out << "Name: " << pipe.GetNamepipe() << "\n";
    out << "Dlina: " << pipe.GetDlinapipe() << "\n";
    out << "Diametr: " << pipe.GetMmpipe() << "\n";
    out << "Remont: " << pipe.GetRemontpipe() << "\n";

    return out;
}
std::istream& operator>>(std::istream& in, Pipe& pipe)
{
    std::string name;
    double dlina;
    int diametr, remont;

    in.ignore(10000, '\n');
    std::getline(in, name);
    in >> dlina >> diametr >> remont;

    if (!in || name.empty() || dlina <= 0 || diametr <= 0 ||
        (remont != 0 && remont != 1))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    pipe.SetNamepipe(name);
    pipe.SetDlinapipe(dlina);
    pipe.SetMmpipe(diametr);
    pipe.SetRemontpipe(remont == 1);

    return in;
}

