#include <iostream> 
#include <string> 
#include <fstream>
struct KC
{
    std::string nameKC;
    int kolvozehKC;
    int zehrabotKC;
    int clasKC;
};
struct Pipe
{
    std::string namepipe;
    double dlinapipe;
    int mmpipe;
    bool remontpipe;
};

void redactpipe(Pipe& pipe)
{
    std::cout << "\nV Remonte? Yes-1 / No-0: ";
    while (!(std::cin >> pipe.remontpipe) || (std::cin.peek() != '\n'))
    {
        std::cout << "\nV Remonte? Yes-1 / No-0: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}
void redactkc(KC& kc)
{
    std::cout << "\nRead kol-vo rabot ZEH in KC: ";
    while (!(std::cin >> kc.zehrabotKC) || (std::cin.peek() != '\n') || (kc.zehrabotKC < 0) || (kc.zehrabotKC > kc.kolvozehKC))
    {
        std::cout << "No! Read Kol-vo ZEH v Pabote: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
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
    std::cout << "V remonte (1-Yes, 0-No): " << pipe.remontpipe << "\n";
}
void showkc(KC& kc)
{
    std::cout << "\n---KC---\n" << "Name: " << kc.nameKC << "\n";
    std::cout << "Kol-vo zehov:" << kc.kolvozehKC << "\n";
    std::cout << "Kol-vo zehov B PaboTe :" << kc.zehrabotKC << "\n";
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
        fout << pipe.remontpipe << "\n";
    }

}

void savefileKC(std::ofstream& fout, KC& kc)
{
    if (kc.kolvozehKC > 0)
    {
        fout << "KC\n";
        fout << kc.nameKC << "\n";
        fout << kc.kolvozehKC << "\n";
        fout << kc.zehrabotKC << "\n";
        fout << kc.clasKC << "\n";
    }
}

void openfilepipe(std::ifstream& fin, Pipe& pipe)
{
    std::getline(fin, pipe.namepipe);
    fin >> pipe.dlinapipe;
    fin >> pipe.mmpipe;
    fin >> pipe.remontpipe;
    fin.ignore(10000, '\n');

}

void openfileKC(std::ifstream& fin, KC& kc)
{
    std::getline(fin, kc.nameKC);
    fin >> kc.kolvozehKC;
    fin >> kc.zehrabotKC;
    fin >> kc.clasKC;
}

int main()
{
    Pipe pipe{};
    KC kc{};
    char vvod;
    while (true)
    {
        menu();
        while (true)
        {
            std::cout << "\nInput: ";
            std::cin >> vvod;

            if ((vvod >= '0') && (vvod <= '7') && (std::cin.peek() == '\n'))
            {
                break;
            }

            std::cout << "Input int 0-7: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        switch (vvod)
        {
        case '1':
        {
            readconsolpipe(pipe);
            break;
        }
        case '2':
        {
            readconsolkc(kc);
            break;
        }
        case '3':
        {
            if (pipe.dlinapipe > 0)
            {
                showpipe(pipe);
            }
            else
            {
                std::cout << "Pipe have not!\n";
            }
            if (kc.kolvozehKC > 0)
            {
                showkc(kc);
            }
            else
            {
                std::cout << "KC have not!\n";
            }
            break;
        }
        case '4':
        {
            if (pipe.dlinapipe > 0)
            {
                redactpipe(pipe);
            }
            else
            {
                std::cout << "Pipe have not!\n";
            }
            break;
        }
        case '5':
        {
            if (kc.kolvozehKC > 0)
            {
                redactkc(kc);
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
        case '0':
        {
            std::cout << "\n\nBye Bye!\n\n";
            return 0;
        }
        default:
        {
            std::cout << "No command, input OT 0 do 7.\n";
            break;
        }
        }

    }
}