#pragma once
#include <iostream> 
#include <string> 
#include <fstream>
class Pipe
{
private:
    bool remontpipe = false;
public:
    std::string namepipe;
    double dlinapipe = 0;
    int mmpipe = 0;

    void SetRemontpipe(bool peremennaya);
    bool GetRemontpipe() const;
};
std::ostream& operator<<(std::ostream& out, const Pipe& pipe);