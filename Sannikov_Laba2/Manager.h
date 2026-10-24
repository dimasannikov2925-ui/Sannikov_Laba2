#pragma once
#include <map>
#include "Pipe.h"
#include "KC.h"
#include <vector>
#include <string>

void deletePipeID(std::map<int, Pipe>& pipes);
void deleteKCID(std::map<int, KC>& kcs);
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
std::vector<int> findPipesByName(const std::map<int, Pipe>& pipes,const std::string& name);
std::vector<int> findPipeRemont(const std::map<int, Pipe>& pipes, bool remont);
void lookPipes(std::map<int, Pipe>& pipes);
void lookKC(std::map<int, KC>& kcs);
std::vector<int> findKCByName(const std::map<int, KC>& kcs, const std::string& name);
std::vector<int> findKCByProstoi(const std::map<int, KC>& kcs, int procent);