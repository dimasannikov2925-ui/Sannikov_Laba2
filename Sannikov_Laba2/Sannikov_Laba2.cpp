#include <iostream> 
#include <string> 
#include <fstream>
#include "Pipe.h"
#include "KC.h"
#include <map>

void redactpipe(Pipe& pipe)
{
    bool remont=false;
    std::cout << "\nV Remonte? Yes-1 / No-0: ";
    while (!(std::cin >> remont) || (std::cin.peek() != '\n'))
    {
        std::cout << "\nV Remonte? Yes-1 / No-0: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    pipe.SetRemontpipe(remont);
}
void redactkc(KC& kc)
{
    int rabot = 0;
    std::cout << "\nRead kol-vo rabot ZEH in KC: ";
    while (!(std::cin >> rabot) || (std::cin.peek() != '\n') || (rabot < 0) || (rabot > kc.kolvozehKC))
    {
        std::cout << "No! Read Kol-vo ZEH v Pabote: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    kc.Setzehrabot(rabot);
}


void readconsolkc(KC& kc)
{
    std::cout << "\nRead name KC: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, kc.nameKC);

    std::cout << "\nRead Kol-vo ZEH in KC: ";
    while (!(std::cin >> kc.kolvozehKC) || (kc.kolvozehKC <= 0) || (std::cin.peek() != '\n'))
    {
        std::cout << "No! Read Kol-vo ZEH: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    redactkc(kc);
    std::cout << "\nRead Class KC: ";
    while (!(std::cin >> kc.clasKC) || (kc.clasKC <= 0) || (std::cin.peek() != '\n'))
    {
        std::cout << "No! Class - int >0, input: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}
void readconsolpipe(Pipe& pipe)
{
    std::cout << "\nRead Name Pipe: ";
    std::cin.ignore(10000, '\n');
    std::getline(std::cin, pipe.namepipe);

    std::cout << "\nRead dlina(km) pipe: ";
    while (!(std::cin >> pipe.dlinapipe) || (pipe.dlinapipe <= 0) || (std::cin.peek() != '\n'))
    {
        std::cout << "No! Read dlina in KM: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cout << "\nRead diametr(mm) pipe: ";
    while (!(std::cin >> pipe.mmpipe) || (pipe.mmpipe <= 0) || (std::cin.peek() != '\n'))
    {
        std::cout << "No! Read diametr in mm: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    redactpipe(pipe);
}
void showpipe(Pipe& pipe)
{
    std::cout << "\n---Pipe---\n" << "Name:" << pipe.namepipe << "\n";
    std::cout << "Dlina(km): " << pipe.dlinapipe << "\n";
    std::cout << "Diametr(mm): " << pipe.mmpipe << "\n";
    std::cout << "V remonte (1-Yes, 0-No): " << pipe.GetRemontpipe() << "\n"; 
}
void showkc(KC& kc)
{
    std::cout << "\n---KC---\n" << "Name: " << kc.nameKC << "\n";
    std::cout << "Kol-vo zehov:" << kc.kolvozehKC << "\n";
    std::cout << "Kol-vo zehov B PaboTe :" << kc.Getzehrabot() << "\n"; 
    std::cout << "Class CTaHzuu:" << kc.clasKC << "\n";
}
void menu()
{
    std::cout << "\n1.Add Pipe\n";
    std::cout << "2.Add KC\n";
    std::cout << "3.Chek objects\n";
    std::cout << "4.Redact Pipe\n";
    std::cout << "5.Redact KC\n";
    std::cout << "6.Save\n";
    std::cout << "7.Open\n";
    std::cout << "8.Delete Pipe\n";
    std::cout << "9.Delete KC\n";
    std::cout << "0.Exit\n";
}
void savefilepipe(std::ofstream& fout, Pipe& pipe)
{
    if (pipe.dlinapipe > 0)
    {
        fout << "PIPE\n";
        fout << pipe.namepipe << "\n";
        fout << pipe.dlinapipe << "\n";
        fout << pipe.mmpipe << "\n";
        fout << pipe.GetRemontpipe() << "\n";
    }

}

void savefileKC(std::ofstream& fout, KC& kc)
{
    if (kc.kolvozehKC > 0)
    {
        fout << "KC\n";
        fout << kc.nameKC << "\n";
        fout << kc.kolvozehKC << "\n";
        fout << kc.Getzehrabot() << "\n";
        fout << kc.clasKC << "\n";
    }
}

void openfilepipe(std::ifstream& fin, Pipe& pipe)
{
    bool remont = false;
    std::getline(fin, pipe.namepipe);
    fin >> pipe.dlinapipe;
    fin >> pipe.mmpipe;
    fin >> remont;
    fin.ignore(10000, '\n');
    pipe.SetRemontpipe(remont);

}

void openfileKC(std::ifstream& fin, KC& kc)
{
    int rabot = 0;
    std::getline(fin, kc.nameKC);
    fin >> kc.kolvozehKC;
    fin >> rabot;
    fin >> kc.clasKC;
    kc.Setzehrabot(rabot);
}

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

            if ((vvod >= '0') && (vvod <= '9') && (std::cin.peek() == '\n'))
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
            std::ofstream fout("file.txt");

            if (!fout)
            {
                std::cout << "File error!\n";
                break;
            }

            savefilepipe(fout, pipe);
            savefileKC(fout, kc);
            break;
        }
        case '7':
        {
            std::ifstream fin("file.txt");

            if (!fin)
            {
                std::cout << "File broyek\n";
                break;
            }

            std::string proverka;
            while (std::getline(fin, proverka))
            {
                if (proverka == "KC")
                    openfileKC(fin, kc);
                else if (proverka == "PIPE")
                    openfilepipe(fin, pipe);
            }
            break;
        }
        case '8':
        {
            int vvodID;
            
            while (true)
            {
                std::cout << "HoMep ID: ";
                if ((std::cin >> vvodID) && (vvodID > 0) && (std::cin.peek() == '\n'))
                {
                    if (pipes.erase(vvodID) == 1)
                    {
                        std::cout << "Pipe" << vvodID << "delete\n";
                    }
                    else
                    {
                        std::cout << "Pipe not this ID\n";
                    }
                    break;
                }
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            
            break;
        }
        case '9':
        {
            int vvodID;
            while (true)
            {
                std::cout << "HoMep ID: ";
                if ((std::cin >> vvodID) && (vvodID > 0) && (std::cin.peek() == '\n'))
                {
                    if (kcs.erase(vvodID) == 1)
                    {
                        std::cout << "KC" << vvodID << "delete\n";
                    }
                    else
                    {
                        std::cout << "KC not this ID\n";
                    }
                    break;
                }
                std::cin.clear();
                std::cin.ignore(10000, '\n');
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
            std::cout << "No command, input OT 0 do 9.\n";
            break;
        }
        }

    }
}