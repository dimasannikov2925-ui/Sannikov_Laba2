
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "KC.h"
#include "Manager.h"
#include "Logger.h"

int main()
{
    std::ofstream logfile("log.txt", std::ios::trunc);
    Logger log(std::cerr);

    if (logfile)
    {
        log.vFile(logfile);
    }
    else
    {
        std::cout << "Log file ERROR!!\n";
    }

    std::unordered_map<int, Pipe> pipes;
    std::unordered_map<int, KC> kcs;

    int PipeID = 1;
    int KCID = 1;
    char vvod;

    while (true)
    {
        menu();

        while (true)
        {
            std::cout << "\nInput: ";

            if ((std::cin >> vvod) &&
                (vvod >= '0' && vvod <= '6') &&
                std::cin.peek() == '\n')
            {
                break;
            }

            std::cout << "Input 0-6!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        std::cerr << vvod << "\n";

        switch (vvod)
        {
        case '1':
        {
            Pipe newPipe{};
            readconsolpipe(newPipe);

            pipes.emplace(PipeID, newPipe);
            PipeID++;

            break;
        }

        case '2':
        {
            KC newKC{};
            readconsolkc(newKC);

            kcs.emplace(KCID, newKC);
            KCID++;

            break;
        }

        case '3':
        {
            lookPipes(pipes);
            break;
        }

        case '4':
        {
            lookKC(kcs);
            break;
        }

        case '5':
        {
            std::string filename;

            std::cout << "Input filename: ";
            std::cin >> filename;
            std::cerr << filename << "\n";

            if (filename == "log.txt")
            {
                std::cout << "NO! This LOG file!!!\n";
                break;
            }

            std::ofstream fout(filename);

            if (!fout)
            {
                std::cout << "File error!\n";
                break;
            }

            for (auto& item : pipes)
            {
                savefilepipe(fout, item.second, item.first);
            }

            for (auto& item : kcs)
            {
                savefileKC(fout, item.second, item.first);
            }

            fout.close();

            if (fout)
            {
                std::cout << "File saved!\n";
            }
            else
            {
                std::cout << "File save error!\n";
            }

            break;
        }

        case '6':
        {
            std::string filename;

            std::cout << "Input filename: ";
            std::cin >> filename;
            std::cerr << filename << "\n";

            std::ifstream fin(filename);

            if (!fin)
            {
                std::cout << "File broyek\n";
                break;
            }

            std::string proverka;
            bool error = false;

            std::unordered_map<int, Pipe> newPipes;
            std::unordered_map<int, KC> newKcs;

            int newPipeID = PipeID;
            int newKCID = KCID;

            while (std::getline(fin, proverka))
            {
                if (proverka == "KC")
                {
                    int id;

                    if (!(fin >> id) || id <= 0)
                    {
                        error = true;
                        break;
                    }

                    fin.ignore(10000, '\n');

                    KC newKC{};
                    openfileKC(fin, newKC);

                    if (!fin ||
                        newKC.nameKC.empty() ||
                        newKC.kolvozehKC <= 0 ||
                        newKC.clasKC <= 0 ||
                        newKcs.find(id) != newKcs.end())
                    {
                        error = true;
                        break;
                    }

                    newKcs[id] = newKC;

                    if (id >= newKCID)
                        newKCID = id + 1;
                }
                else if (proverka == "PIPE")
                {
                    int id;

                    if (!(fin >> id) || id <= 0)
                    {
                        error = true;
                        break;
                    }

                    fin.ignore(10000, '\n');

                    Pipe newPipe{};
                    openfilepipe(fin, newPipe);

                    if (!fin ||
                        newPipe.namepipe.empty() ||
                        newPipe.dlinapipe <= 0 ||
                        newPipe.mmpipe <= 0 ||
                        newPipes.find(id) != newPipes.end())
                    {
                        error = true;
                        break;
                    }

                    newPipes[id] = newPipe;

                    if (id >= newPipeID)
                        newPipeID = id + 1;
                }
                else if (!proverka.empty())
                {
                    error = true;
                    break;
                }
            }

            if (fin.bad())
            {
                error = true;
            }

            if (error)
            {
                std::cout << "File load error!\n";
            }
            else
            {
                for (auto& item : newPipes)
                {
                    pipes[item.first] = item.second;
                }

                for (auto& item : newKcs)
                {
                    kcs[item.first] = item.second;
                }

                PipeID = newPipeID;
                KCID = newKCID;

                std::cout << "File loaded!\n";
            }

            break;
        }

        case '0':
        {
            std::cout << "\n\nBye Bye!\n\n";
            return 0;
        }

        default:
        {
            std::cout << "No command, input OT 0 do 6.\n";
            break;
        }
        }
    }
}
