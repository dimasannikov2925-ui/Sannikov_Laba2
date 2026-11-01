#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "KC.h"
#include <vector>
#include <string>

void deletePipeID(std::unordered_map<int, Pipe>& pipes);
void deleteKCID(std::unordered_map<int, KC>& kcs);
void redactpipe(Pipe& pipe);
void redactkc(KC& kc);
void readconsolkc(KC& kc);
void readconsolpipe(Pipe& pipe);
void showpipe(Pipe& pipe);
void showkc(KC& kc);
void menu();
void savefilepipe(std::ofstream& fout, Pipe& pipe,int id);
void savefileKC(std::ofstream& fout, KC& kc, int id);
void openfilepipe(std::ifstream& fin, Pipe& pipe);
void openfileKC(std::ifstream& fin, KC& kc);
std::vector<int> findPipesByName(const std::unordered_map<int, Pipe>& pipes,const std::string& name);
std::vector<int> findPipeRemont(const std::unordered_map<int, Pipe>& pipes, bool remont);
void lookPipes(std::unordered_map<int, Pipe>& pipes);
void lookKC(std::unordered_map<int, KC>& kcs);
std::vector<int> findKCByName(const std::unordered_map<int, KC>& kcs, const std::string& name);
std::vector<int> findKCByProstoi(const std::unordered_map<int, KC>& kcs, int procent);

template <typename T>
bool deleteByID(std::unordered_map<int, T>& objects, int id)
{
    return objects.erase(id) == 1;
}