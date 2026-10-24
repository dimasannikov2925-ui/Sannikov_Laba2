#include "Manager.h"
#include <iostream>

void  deletePipeID(std::map<int, Pipe>& pipes)
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
}

void deleteKCID(std::map<int, KC>& kcs)
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
}

void redactpipe(Pipe& pipe)
{
    bool remont = false;
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
    std::cout << "a. Look Pipes\n";
    std::cout << "b. Look KCs\n";
    std::cout << "0.Exit\n";
}
void savefilepipe(std::ofstream& fout, Pipe& pipe, int id)
{
    if (pipe.dlinapipe > 0)
    {
        fout << "PIPE\n";
        fout << id << "\n";
        fout << pipe.namepipe << "\n";
        fout << pipe.dlinapipe << "\n";
        fout << pipe.mmpipe << "\n";
        fout << pipe.GetRemontpipe() << "\n";
    }

}

void savefileKC(std::ofstream& fout, KC& kc,int id)
{
    if (kc.kolvozehKC > 0)
    {
        fout << "KC\n";
        fout << id << "\n";
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
    fin.ignore(10000, '\n');
    kc.Setzehrabot(rabot);
}

std::vector<int> findPipesByName(const std::map<int, Pipe>& pipes, const std::string& name)
{
    std::vector<int> found;
    for (const auto& item : pipes)
    {
        if (item.second.namepipe.find(name) != std::string::npos)
        {
            found.push_back(item.first);
        }
    }
    return found;
}

std::vector<int> findPipeRemont(const std::map<int, Pipe>& pipes, bool remont)
{
    std::vector<int> found;
    for (const auto& item : pipes)
    {
        if (item.second.GetRemontpipe() == remont)
        {
            found.push_back(item.first);
        }
    }
    return found;
}

void lookPipes(std::map<int, Pipe>& pipes)
{
    if (pipes.empty())
    {
        std::cout << "Pipe have not!\n";
        return;
    }

    std::cout << "\n1.Look Pipe by name\n";
    std::cout << "2.Look Pipe by remont\n";

    char vvod;

    while (true)
    {
        std::cout << "Input 1 or 2: ";

        if ((std::cin >> vvod) && (vvod == '1' || vvod == '2') && std::cin.peek() == '\n')
            break;

        std::cout << "Vvedute 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::vector<int> found;

    if (vvod == '1')
    {
        std::string name;

        std::cin.ignore(10000, '\n');
        std::cout << "Input Pipe name: ";
        std::getline(std::cin, name);

        if (name.empty())
        {
            std::cout << "Name empty!\n";
            return;
        }

        found = findPipesByName(pipes, name);
    }
    else
    {
        int remont;

        while (true)
        {
            std::cout << "Input remont (0 or 1): ";

            if ((std::cin >> remont) && (remont == 0 || remont == 1) && std::cin.peek() == '\n')
                break;

            std::cout << "Input 0 or 1!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        found = findPipeRemont(pipes, remont == 1);
    }

    if (found.empty())
    {
        std::cout << "Pipes not found!\n";
        return;
    }

    for (int id : found)
    {
        std::cout << "ID Pipe: " << id << "\n";
        showpipe(pipes.at(id));
    }

    std::cout << "\n1.Redact found Pipes\n";
    std::cout << "2.Delete found Pipes\n";
    std::cout << "0.Back\n";

    char action;

    while (true)
    {
        std::cout << "Input: ";

        if ((std::cin >> action) && (action == '0' || action == '1' || action == '2') && std::cin.peek() == '\n')
            break;

        std::cout << "Input 0, 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    if (action == '0')
        return;

    std::cout << "\n1.All found Pipes\n";
    std::cout << "2.Choose Pipes by ID\n";

    char choice;

    while (true)
    {
        std::cout << "Input: ";

        if ((std::cin >> choice) && (choice == '1' || choice == '2') && std::cin.peek() == '\n')
            break;

        std::cout << "Input 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::vector<int> selected;

    if (choice == '1')
    {
        selected = found;
    }
    else
    {
        std::cout << "Input ID one by one. Input 0 to finish.\n";

        while (true)
        {
            int vvodID;

            std::cout << "Input ID: ";

            if (!(std::cin >> vvodID) || vvodID < 0 || std::cin.peek() != '\n')
            {
                std::cout << "Wrong ID!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (vvodID == 0)
                break;

            bool est = false;

            for (int id : found)
            {
                if (id == vvodID)
                {
                    est = true;
                    break;
                }
            }

            if (!est)
            {
                std::cout << "No such ID among found Pipes!\n";
                continue;
            }

            bool povtor = false;

            for (int id : selected)
            {
                if (id == vvodID)
                {
                    povtor = true;
                    break;
                }
            }

            if (povtor)
            {
                std::cout << "ID already selected!\n";
                continue;
            }

            selected.push_back(vvodID);
        }
    }

    if (selected.empty())
    {
        std::cout << "Nothing selected!\n";
        return;
    }

    if (action == '1')
    {
        int remont;

        while (true)
        {
            std::cout << "New remont status (0 or 1): ";

            if ((std::cin >> remont) && (remont == 0 || remont == 1) && std::cin.peek() == '\n')
                break;

            std::cout << "Input 0 or 1!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        for (int id : selected)
        {
            pipes.at(id).SetRemontpipe(remont == 1);
        }

        std::cout << "Changed Pipes: " << selected.size() << "\n";
    }
    else
    {
        for (int id : selected)
        {
            pipes.erase(id);
        }

        std::cout << "Deleted Pipes: " << selected.size() << "\n";
    }
}


std::vector<int> findKCByName(const std::map<int, KC>& kcs, const std::string& name)
{
    std::vector<int> found;

    for (const auto& item : kcs)
    {
        if (item.second.nameKC.find(name) != std::string::npos)
        {
            found.push_back(item.first);
        }
    }

    return found;
}

std::vector<int> findKCByProstoi(const std::map<int, KC>& kcs, int procent)
{
    std::vector<int> found;

    for (const auto& item : kcs)
    {
        if (item.second.kolvozehKC <= 0)
            continue;

        double prostoi = (item.second.kolvozehKC - item.second.Getzehrabot()) * 100.0 / item.second.kolvozehKC;

        if (prostoi >= procent)
        {
            found.push_back(item.first);
        }
    }

    return found;
}

void lookKC(std::map<int, KC>& kcs)
{
    if (kcs.empty())
    {
        std::cout << "KC have not!\n";
        return;
    }

    std::cout << "\n1.Look KC by name\n";
    std::cout << "2.Look KC by % prostoi\n";

    char vvod;

    while (true)
    {
        std::cout << "Input 1 or 2: ";

        if ((std::cin >> vvod) && (vvod == '1' || vvod == '2') && std::cin.peek() == '\n')
            break;

        std::cout << "Input 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    std::vector<int> found;

    if (vvod == '1')
    {
        std::string name;

        std::cin.ignore(10000, '\n');
        std::cout << "Input KC name: ";
        std::getline(std::cin, name);

        if (name.empty())
        {
            std::cout << "Name empty!\n";
            return;
        }

        found = findKCByName(kcs, name);
    }
    else
    {
        int procent;

        while (true)
        {
            std::cout << "Input minimum % prostoi (0-100): ";

            if ((std::cin >> procent) && procent >= 0 && procent <= 100 && std::cin.peek() == '\n')
                break;

            std::cout << "Input number from 0 to 100!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        found = findKCByProstoi(kcs, procent);
    }

    if (found.empty())
    {
        std::cout << "KC not found!\n";
        return;
    }

    for (int id : found)
    {
        std::cout << "ID KC: " << id << "\n";
        showkc(kcs.at(id));

        int vsego = kcs.at(id).kolvozehKC;

        if (vsego > 0)
        {
            double prostoi = (vsego - kcs.at(id).Getzehrabot()) * 100.0 / vsego;
            std::cout << "Prostoi: " << prostoi << "%\n";
        }
    }

    std::cout << "\n1.Redact KC\n";
    std::cout << "2.Delete KC\n";
    std::cout << "0.Back\n";

    char action;

    while (true)
    {
        std::cout << "Input: ";

        if ((std::cin >> action) && (action == '0' || action == '1' || action == '2') && std::cin.peek() == '\n')
            break;

        std::cout << "Input 0, 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    if (action == '0')
        return;

    int vvodID;

    while (true)
    {
        std::cout << "Input ID KC: ";

        if (!(std::cin >> vvodID) || vvodID <= 0 || std::cin.peek() != '\n')
        {
            std::cout << "Wrong ID!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        bool est = false;

        for (int id : found)
        {
            if (id == vvodID)
            {
                est = true;
                break;
            }
        }

        if (est)
            break;

        std::cout << "No such ID among found KC!\n";
    }

    if (action == '1')
    {
        redactkc(kcs.at(vvodID));
        std::cout << "KC changed!\n";
    }
    else
    {
        kcs.erase(vvodID);
        std::cout << "KC deleted!\n";
    }
}