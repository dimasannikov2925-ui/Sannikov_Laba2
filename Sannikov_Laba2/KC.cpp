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