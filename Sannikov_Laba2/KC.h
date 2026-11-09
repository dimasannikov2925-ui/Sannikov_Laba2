#pragma once
#include <iostream> 
#include <string> 
#include <fstream>
class KC
{
private:
    int zehrabotKC = 0;
    std::string nameKC;
    int kolvozehKC = 0;
    int clasKC = 0;
public:
  
    void Setzehrabot(int perzehrab);
    int Getzehrabot() const;

    void SetNamekc(std::string peremennaya);
    std::string GetNamekc() const;

    void SetKolvozehkc(int peremennaya);
    int GetKolvozehkc() const;

    void SetClasskc(int peremennaya);
    int GetClasskc() const;
};
std::ostream& operator<<(std::ostream& out, const KC& kc);
std::istream& operator>>(std::istream& in, KC& kc);