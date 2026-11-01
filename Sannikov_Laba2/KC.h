#pragma once
#include <iostream> 
#include <string> 
#include <fstream>
class KC
{
private:
    int zehrabotKC = 0;
public:
    std::string nameKC;
    int kolvozehKC = 0;
    int clasKC = 0;
  
    void Setzehrabot(int perzehrab);
    int Getzehrabot() const;
};
std::ostream& operator<<(std::ostream& out, const KC& kc);