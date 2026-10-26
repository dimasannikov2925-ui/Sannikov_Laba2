#include <iostream> 
#include <string> 
#include <fstream>
#include "Pipe.h"
#include "KC.h"
#include <map>
#include "Manager.h"
#include "Logger.h"
int main()
{
    std::ofstream logfile("log.txt", std::ios::app);
    Logger log(std::cerr);
    if (logfile)
    {
        log.vFile(logfile);
        std::cerr << "Program start\n";
    }
    else
    {
        std::cout << "Log file ERROR!!\n";
    }
    Pipe pipe{};
    KC kc{};
    std::map<int, Pipe> pipes;
    std::map<int, KC> kcs;
    int PipeID = 1;
    int KCID = 1;
    char vvod;
    while (true)
    {
        menu();
        while (true)
        {
            std::cout << "\nInput: ";
            std::cin >> vvod;

            if (((vvod >= '0' && vvod <= '9') || vvod == 'a' || vvod == 'b') && std::cin.peek() == '\n')
            {
                break;
            }

            std::cout << "Input int 0-9, a/b: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        switch (vvod)
        {
        case '1':
        {
            Pipe newPipe{};
            readconsolpipe(newPipe);
            pipes.emplace(PipeID, newPipe);
            std::cerr << "Pipe created Pipe-ID:  " << PipeID << "\n";
            PipeID++;
            break;
        }
        case '2':
        {
            KC newKC{};
            readconsolkc(newKC);
            kcs.emplace(KCID, newKC);
            std::cerr << "KC created KC-ID:  " << KCID << "\n";
            KCID++;
            break;
        }
        case '3':
        {
            if (!pipes.empty())
            {
                for (auto& item : pipes)
                {
                    std::cout << "ID Pipe: " << item.first << "\n";
                    showpipe(item.second);
                }
            }
            else
            {
                std::cout << "Pipe have not!\n";
            }
            if (!kcs.empty())
            {
                for (auto& item : kcs)
                {
                    std::cout << "ID KC: " << item.first << "\n";
                    showkc(item.second);
                }
            }           
            else
            {
                std::cout << "KC have not!\n";
            }
            break;
        }
        case '4':
        {
            if (!pipes.empty())
            {
                std::cout << "\nPipe ID:\n";
                for (auto& item : pipes)
                {
                    std::cout << "ID: " << item.first << " Name: " << item.second.namepipe << "\n";
                }
                int vvodID;
                while (true)
                {
                    std::cout << "\nInput ID: ";
                    if ((std::cin >> vvodID) && (vvodID > 0) && (std::cin.peek() == '\n'))
                    {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                if (pipes.find(vvodID) != pipes.end())
                {
                    std::cout << "ID Pipe: " << vvodID << "\n";
                    redactpipe(pipes.at(vvodID));
                    std::cerr << "Pipe redact, ID: " << vvodID << "Remont: " << pipes.at(vvodID).GetRemontpipe() << "\n";
                }
                else
                {
                    std::cout << "HeT Takogo ID!\n";
                }
            }
            else
            {
                std::cout << "Pipe have not!\n";
            }
            break;
        }
        case '5':
        {
            if (!kcs.empty())
            {
                std::cout << "\nInput ID:\n";

                for (auto& item : kcs)
                {
                    std::cout << "KC ID: " << item.first << " Name: " << item.second.nameKC << "\n";
                }

                int vvodID;
                while (true)
                {
                    std::cout << "\nInput ID: ";
                    if ((std::cin >> vvodID) && (vvodID > 0) && (std::cin.peek() == '\n'))
                    {
                        break;
                    }
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                if (kcs.find(vvodID) != kcs.end())
                {
                    std::cout << "ID KC: " << vvodID << "\n";
                    redactkc(kcs.at(vvodID));
                    std::cerr << "KC redact, ID: " << vvodID << "B PaboTe:  " << kcs.at(vvodID).Getzehrabot() << "\n";
                }
                else
                {
                    std::cout << "HeT Takogo ID!\n";
                }
            }
            else
            {
                std::cout << "KC have not!\n";
            }
            break;
        }
       
        case '6':
        {
            std::string filename;

            std::cout << "Input filename: ";
            std::cin >> filename;
            if (filename == "log.txt")
            {
                std::cout << "NO! This LOG file!!!\n";
                break;
            }
            std::ofstream fout(filename);

            if (!fout)
            {
                std::cout << "File error!\n";
                std::cerr << "ERROR! File not open: " << filename << "\n";
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
                std::cerr << "File saved: " << filename
                    << " Pipes: " << pipes.size()
                    << " KC: " << kcs.size() << "\n";
            }
            else
            {
                std::cout << "File save error!\n";
                std::cerr << "ERROR! File not saved: " << filename << "\n";
            }

            break;
        }

        case '7':
        {
            std::string filename;

            std::cout << "Input filename: ";
            std::cin >> filename;

            std::ifstream fin(filename);

            if (!fin)
            {
                std::cout << "File broyek\n";
                std::cerr << "ERROR! File not open: " << filename << "\n";
                break;
            }

            std::cerr << "File loading: " << filename << "\n";

            std::string proverka;
            bool error = false;
            std::map<int, Pipe> newPipes;
            std::map<int, KC> newKcs;
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

                    if (!fin || newKC.nameKC.empty() || newKC.kolvozehKC <= 0 || newKC.clasKC <= 0 || newKcs.find(id) != newKcs.end())
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

                    if (!fin || newPipe.namepipe.empty() || newPipe.dlinapipe <= 0 || newPipe.mmpipe <= 0 || newPipes.find(id) != newPipes.end())
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
                std::cerr << "ERROR! File broyek when loading: "
                    << filename << "\n";
            }
            else
            {
                for (auto& item : newPipes)
                    pipes[item.first] = item.second;

                for (auto& item : newKcs)
                    kcs[item.first] = item.second;

                PipeID = newPipeID;
                KCID = newKCID;
                std::cout << "File loaded!\n";
                std::cerr << "File loaded: " << filename << " Pipes: " << pipes.size() << " KC: " << kcs.size() << "\n";
            }

            break;
        }
        case '8':
        {
            if (pipes.empty())
            {
                std::cout << "Pipe have not!\n";
                break;
            }

            std::cout << "\nPipe ID:\n";
            for (auto& item : pipes)
            {
                std::cout << "ID: " << item.first
                    << " Name: " << item.second.namepipe << "\n";
            }

            deletePipeID(pipes);
            break;
        }
        case '9':
        {
            if (kcs.empty())
            {
                std::cout << "KC have not!\n";
                break;
            }

            std::cout << "\nKC ID:\n";
            for (auto& item : kcs)
            {
                std::cout << "ID: " << item.first
                    << " Name: " << item.second.nameKC << "\n";
            }

            deleteKCID(kcs);
            break;
        }
        case 'a':
        {
            lookPipes(pipes);
            break;
        }
        case 'b':
        {
            lookKC(kcs);
            break;
        }
        case '0':
        {
            std::cout << "\n\nBye Bye!\n\n";
            std::cerr << "Program closed";
            std::cerr << "\n\nBye Bye!\n\n";
            return 0;
        }
        default:
        {
            std::cout << "No command, input OT 0 do 9.\n";
            break;
        }
        }

    }
}