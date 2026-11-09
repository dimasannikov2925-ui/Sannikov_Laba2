#pragma once
#include <iostream> 
#include <string> 
#include <fstream>
class Pipe
{
private:
    bool remontpipe = false;
    std::string namepipe;
    double dlinapipe = 0;
    int mmpipe = 0;
public:
    void SetNamepipe(std::string peremennaya);
    void SetDlinapipe(double peremennaya);
    void SetMmpipe(int peremennaya);
    void SetRemontpipe(bool peremennaya);
    bool GetRemontpipe() const;
    std::string GetNamepipe() const;
    double GetDlinapipe() const;
    int GetMmpipe() const;
};
std::ostream& operator<<(std::ostream& out, const Pipe& pipe);
std::istream& operator>>(std::istream& in, Pipe& pipe);