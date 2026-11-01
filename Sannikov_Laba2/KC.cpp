#include "KC.h"
#include <iostream> 
#include <string> 
#include <fstream>
void KC::Setzehrabot(int perzehrab)
{
    if (perzehrab >= 0 && perzehrab <= kolvozehKC)
        zehrabotKC = perzehrab;
}
int KC::Getzehrabot() const
{
    return zehrabotKC;
}
std::ostream& operator<<(std::ostream& out, const KC& kc)
{
    out << "Name: " << kc.nameKC << "\n";
    out << "Kol-vo zehov: " << kc.kolvozehKC << "\n";
    out << "Kol-vo zehov v rabote: " << kc.Getzehrabot() << "\n";
    out << "Class: " << kc.clasKC << "\n";

    return out;
}