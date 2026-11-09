#include "KC.h"
#include <iostream> 
#include <string> 
void KC::Setzehrabot(int perzehrab)
{
    if (perzehrab >= 0 && perzehrab <= kolvozehKC)
        zehrabotKC = perzehrab;
}
int KC::Getzehrabot() const
{
    return zehrabotKC;
}
void KC::SetNamekc(std::string peremennaya)
{
    if (!peremennaya.empty())
        nameKC = peremennaya;
}
std::string KC::GetNamekc() const
{
    return nameKC;
}
void KC::SetKolvozehkc(int peremennaya)
{
    if (peremennaya > 0)
        kolvozehKC = peremennaya;
}
int KC::GetKolvozehkc() const
{
    return kolvozehKC;
}
void KC::SetClasskc(int peremennaya)
{
    if (peremennaya > 0)
        clasKC = peremennaya;
}
int KC::GetClasskc() const
{
    return clasKC;
}
std::ostream& operator<<(std::ostream& out, const KC& kc)
{
    out << "Name: " << kc.GetNamekc() << "\n";
    out << "Kol-vo zehov: " << kc.GetKolvozehkc() << "\n";
    out << "Kol-vo zehov v rabote: " << kc.Getzehrabot() << "\n";
    out << "Class: " << kc.GetClasskc() << "\n";

    return out;
}

std::istream& operator>>(std::istream& in, KC& kc)
{
    std::string name;
    int vsego, rabot, clas;

    in.ignore(10000, '\n');
    std::getline(in, name);
    in >> vsego >> rabot >> clas;

    if (!in || name.empty() || vsego <= 0 ||
        rabot < 0 || rabot > vsego || clas <= 0)
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    kc.SetNamekc(name);
    kc.SetKolvozehkc(vsego);
    kc.Setzehrabot(rabot);
    kc.SetClasskc(clas);

    return in;
}
