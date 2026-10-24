#include <iostream> 
#include <string> 
#include <fstream>
#include "Pipe.h"
#include "KC.h"
#include <map>
#include "Manager.h"

int main()
{
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

            std::cout << "Input int 0-9: ";
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
            if (!pipes.empty())
            {
                for (int i = 0; i <= PipeID; i++)
                {
                    if (pipes.find(i)!=pipes.end())
                    {
                        std::cout << "ID Pipe: " << i << "\n";
                        showpipe(pipes.at(i));
                    }
                    else
                        continue;
                }
            }
            else
            {
                std::cout << "Pipe have not!\n";
            }
            if (!kcs.empty())
            {
                for (int i = 1;i <= KCID;i++)
                {
                    if (kcs.find(i) != kcs.end())
                    {
                        std::cout << "ID KC: " << i << "\n";
                        showkc(kcs.at(i));
                    }
                    else
                        continue;
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
                break;
            }

            std::string proverka;
            while (std::getline(fin, proverka))
            {
                if (proverka == "KC")
                {
                    int id;
                    fin >> id;
                    fin.ignore(10000, '\n');

                    KC newKC{};
                    openfileKC(fin, newKC);

                    kcs[id] = newKC;

                    if (id >= KCID)
                        KCID = id + 1;
                }
                else if (proverka == "PIPE")
                {
                    int id;
                    fin >> id;
                    fin.ignore(10000, '\n');

                    Pipe newPipe{};
                    openfilepipe(fin, newPipe);

                    pipes[id] = newPipe;

                    if (id >= PipeID)
                        PipeID = id + 1;
                }
            }
            break;
        }
        case '8':
        {
            deletePipeID(pipes);
            break;
        }
        case '9':
        {
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