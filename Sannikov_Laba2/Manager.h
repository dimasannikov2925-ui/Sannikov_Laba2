#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Pipe.h"
#include "KC.h"

class Manager
{
private:
    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, KC> kcs;
    int PipeID = 1;
    int KCID = 1;

    std::vector<int> findPipesByName(const std::string& name) const;
    std::vector<int> findPipeRemont(bool remont) const;
    std::vector<int> findKCByName(const std::string& name) const;
    std::vector<int> findKCByProstoi(int procent) const;

    bool readconsolpipe(Pipe& pipe);
    bool readconsolkc(KC& kc);

    void showAllPipes() const;
    void showAllKC() const;

public:
    void addPipe();
    void addKC();
    void lookPipes();
    void lookKC();
    void saveFile();
    void loadFile();
};