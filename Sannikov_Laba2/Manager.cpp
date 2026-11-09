#include "Manager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>


void Manager::addPipe()
{
    Pipe newPipe{};
    if (!readconsolpipe(newPipe)) return;
    pipes.emplace(PipeID, newPipe);
    PipeID++;
    std::cout << "Pipe added!\n";
}

void Manager::addKC()
{
    KC newKC{};
    if (!readconsolkc(newKC)) return;
    kcs.emplace(KCID, newKC);
    KCID++;
    std::cout << "KC added!\n";
}

std::vector<int> Manager::findPipesByName(const std::string& name) const
{
    std::vector<int> found;
    for (const auto& item : pipes)
    {
        if (item.second.GetNamepipe().find(name) != std::string::npos)
            found.push_back(item.first);
    }
    return found;
}

std::vector<int> Manager::findPipeRemont(bool remont) const
{
    std::vector<int> found;
    for (const auto& item : pipes)
    {
        if (item.second.GetRemontpipe() == remont)
            found.push_back(item.first);
    }
    return found;
}

std::vector<int> Manager::findKCByName(const std::string& name) const
{
    std::vector<int> found;
    for (const auto& item : kcs)
    {
        if (item.second.GetNamekc().find(name) != std::string::npos)
            found.push_back(item.first);
    }
    return found;
}

std::vector<int> Manager::findKCByProstoi(int procent) const
{
    std::vector<int> found;
    for (const auto& item : kcs)
    {
        if (item.second.GetKolvozehkc() <= 0) continue;
        double prostoi = (item.second.GetKolvozehkc() - item.second.Getzehrabot())
            * 100.0 / item.second.GetKolvozehkc();
        if (prostoi >= procent)
            found.push_back(item.first);
    }
    return found;
}

void Manager::showAllPipes() const
{
    if (pipes.empty())
    {
        std::cout << "Pipes have not!\n";
        return;
    }
    for (const auto& item : pipes)
    {
        std::cout << "\nID Pipe: " << item.first << "\n";
        std::cout << item.second;
    }
}

void Manager::showAllKC() const
{
    if (kcs.empty())
    {
        std::cout << "KC have not!\n";
        return;
    }
    for (const auto& item : kcs)
    {
        const KC& kc = item.second;
        std::cout << "\nID KC: " << item.first << "\n";
        std::cout << kc;
        double prostoi = (kc.GetKolvozehkc() - kc.Getzehrabot())
            * 100.0 / kc.GetKolvozehkc();
        std::cout << "Prostoi: " << prostoi << "%\n";
    }
}

void Manager::lookPipes()
{
    while (true)
    {
        std::cout << "\n1.Look Pipe by name\n";
        std::cout << "2.Look Pipe by remont\n";
        std::cout << "3.Show all Pipes\n";
        std::cout << "0.Back\n";

        char vvod;
        while (true)
        {
            std::cout << "Input: ";
            if ((std::cin >> vvod) && (vvod >= '0' && vvod <= '3') &&
                std::cin.peek() == '\n') break;
            if (std::cin.eof()) return;
            std::cout << "Input 0-3!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cerr << vvod << "\n";

        if (vvod == '0') return;
        if (vvod == '3')
        {
            showAllPipes();
            continue;
        }
        if (pipes.empty())
        {
            std::cout << "Pipes have not!\n";
            continue;
        }

        std::vector<int> found;
        if (vvod == '1')
        {
            std::string name;
            std::cout << "Input Pipe name: ";
            std::cin.ignore(10000, '\n');
            if (!std::getline(std::cin, name)) return;
            std::cerr << name << "\n";
            if (name.empty())
            {
                std::cout << "Name empty!\n";
                continue;
            }
            found = findPipesByName(name);
        }
        else
        {
            int remont;
            while (true)
            {
                std::cout << "Input remont (0 or 1): ";
                if ((std::cin >> remont) && (remont == 0 || remont == 1) &&
                    std::cin.peek() == '\n') break;
                if (std::cin.eof()) return;
                std::cout << "Input 0 or 1!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cerr << remont << "\n";
            found = findPipeRemont(remont == 1);
        }

        if (found.empty())
        {
            std::cout << "Pipes not found!\n";
            continue;
        }
        for (int id : found)
        {
            std::cout << "\nID Pipe: " << id << "\n";
            std::cout << pipes.at(id);
        }

        std::cout << "\n1.Delete found Pipes\n";
        std::cout << "2.Redact found Pipes\n";
        std::cout << "0.Back\n";
        char action;
        while (true)
        {
            std::cout << "Input: ";
            if ((std::cin >> action) && (action >= '0' && action <= '2') &&
                std::cin.peek() == '\n') break;
            if (std::cin.eof()) return;
            std::cout << "Input 0-2!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cerr << action << "\n";
        if (action == '0') continue;

        std::vector<int> selected;
        if (!selectIDs(found, selected)) return;
        if (selected.empty())
        {
            std::cout << "Nothing selected!\n";
            continue;
        }

        if (action == '1')
        {
            for (int id : selected)
                deleteByID(pipes, id);
            std::cout << "Deleted Pipes: " << selected.size() << "\n";
        }
        else
        {
            int remont;
            while (true)
            {
                std::cout << "New remont status (0 or 1): ";
                if ((std::cin >> remont) && (remont == 0 || remont == 1) &&
                    std::cin.peek() == '\n') break;
                if (std::cin.eof()) return;
                std::cout << "Input 0 or 1!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cerr << remont << "\n";
            for (int id : selected)
                pipes.at(id).SetRemontpipe(remont == 1);
            std::cout << "Changed Pipes: " << selected.size() << "\n";
        }
    }
}

void Manager::lookKC()
{
    while (true)
    {
        std::cout << "\n1.Look KC by name\n";
        std::cout << "2.Look KC by % prostoi\n";
        std::cout << "3.Show all KC\n";
        std::cout << "0.Back\n";

        char vvod;
        while (true)
        {
            std::cout << "Input: ";
            if ((std::cin >> vvod) && (vvod >= '0' && vvod <= '3') &&
                std::cin.peek() == '\n') break;
            if (std::cin.eof()) return;
            std::cout << "Input 0-3!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cerr << vvod << "\n";

        if (vvod == '0') return;
        if (vvod == '3')
        {
            showAllKC();
            continue;
        }
        if (kcs.empty())
        {
            std::cout << "KC have not!\n";
            continue;
        }

        std::vector<int> found;
        if (vvod == '1')
        {
            std::string name;
            std::cout << "Input KC name: ";
            std::cin.ignore(10000, '\n');
            if (!std::getline(std::cin, name)) return;
            std::cerr << name << "\n";
            if (name.empty())
            {
                std::cout << "Name empty!\n";
                continue;
            }
            found = findKCByName(name);
        }
        else
        {
            int procent;
            while (true)
            {
                std::cout << "Input minimum % prostoi (0-100): ";
                if ((std::cin >> procent) && procent >= 0 && procent <= 100 &&
                    std::cin.peek() == '\n') break;
                if (std::cin.eof()) return;
                std::cout << "Input 0-100!\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            std::cerr << procent << "\n";
            found = findKCByProstoi(procent);
        }

        if (found.empty())
        {
            std::cout << "KC not found!\n";
            continue;
        }
        for (int id : found)
        {
            const KC& kc = kcs.at(id);
            std::cout << "\nID KC: " << id << "\n";
            std::cout << kc;
            double prostoi = (kc.GetKolvozehkc() - kc.Getzehrabot())
                * 100.0 / kc.GetKolvozehkc();
            std::cout << "Prostoi: " << prostoi << "%\n";
        }

        std::cout << "\n1.Delete found KC\n";
        std::cout << "2.Redact found KC\n";
        std::cout << "0.Back\n";
        char action;
        while (true)
        {
            std::cout << "Input: ";
            if ((std::cin >> action) && (action >= '0' && action <= '2') &&
                std::cin.peek() == '\n') break;
            if (std::cin.eof()) return;
            std::cout << "Input 0-2!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cerr << action << "\n";
        if (action == '0') continue;

        std::vector<int> selected;
        if (!selectIDs(found, selected)) return;
        if (selected.empty())
        {
            std::cout << "Nothing selected!\n";
            continue;
        }

        if (action == '1')
        {
            for (int id : selected)
                deleteByID(kcs, id);
            std::cout << "Deleted KC: " << selected.size() << "\n";
        }
        else
        {
            for (int id : selected)
            {
                KC& kc = kcs.at(id);
                int rabot;
                std::cout << "ID KC: " << id << "\n";
                while (true)
                {
                    std::cout << "New working ZEH: ";
                    if ((std::cin >> rabot) && rabot >= 0 &&
                        rabot <= kc.GetKolvozehkc() && std::cin.peek() == '\n')
                        break;
                    if (std::cin.eof()) return;
                    std::cout << "Wrong kol-vo ZEH!\n";
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                }
                std::cerr << rabot << "\n";
                kc.Setzehrabot(rabot);
            }
            std::cout << "KC changed!\n";
        }
    }
}

void Manager::saveFile()
{
    std::string filename;
    std::cout << "Input filename: ";
    if (!(std::cin >> filename)) return;
    std::cerr << filename << "\n";

    if (filename == "log.txt")
    {
        std::cout << "NO! This LOG file!\n";
        return;
    }

    std::ofstream fout(filename);
    if (!fout)
    {
        std::cout << "File error!\n";
        return;
    }
    fout.precision(17);

    for (const auto& item : pipes)
    {
        const Pipe& pipe = item.second;
        fout << "PIPE\n";
        fout << item.first << "\n";
        fout << pipe.GetNamepipe() << "\n";
        fout << pipe.GetDlinapipe() << "\n";
        fout << pipe.GetMmpipe() << "\n";
        fout << pipe.GetRemontpipe() << "\n";
    }
    for (const auto& item : kcs)
    {
        const KC& kc = item.second;
        fout << "KC\n";
        fout << item.first << "\n";
        fout << kc.GetNamekc() << "\n";
        fout << kc.GetKolvozehkc() << "\n";
        fout << kc.Getzehrabot() << "\n";
        fout << kc.GetClasskc() << "\n";
    }

    fout.close();
    if (fout)
        std::cout << "File saved!\n";
    else
        std::cout << "File save error!\n";
}

void Manager::loadFile()
{
    std::string filename;
    std::cout << "Input filename: ";
    if (!(std::cin >> filename)) return;
    std::cerr << filename << "\n";

    std::ifstream fin(filename);
    if (!fin)
    {
        std::cout << "File error!\n";
        return;
    }

    std::unordered_map<int, Pipe> newPipes;
    std::unordered_map<int, KC> newKcs;
    int newPipeID = PipeID;
    int newKCID = KCID;
    bool error = false;
    std::string tip;

    while (fin >> tip)
    {
        int id;
        if (!(fin >> id) || id <= 0)
        {
            error = true;
            break;
        }

        if (tip == "PIPE")
        {
            Pipe pipe;
            if (!(fin >> pipe) || newPipes.find(id) != newPipes.end())
            {
                error = true;
                break;
            }
            newPipes[id] = pipe;
            if (id >= newPipeID) newPipeID = id + 1;
        }
        else if (tip == "KC")
        {
            KC kc;
            if (!(fin >> kc) || newKcs.find(id) != newKcs.end())
            {
                error = true;
                break;
            }
            newKcs[id] = kc;
            if (id >= newKCID) newKCID = id + 1;
        }
        else
        {
            error = true;
            break;
        }
    }

    if (error || !fin.eof())
    {
        std::cout << "File load error!\n";
        return;
    }

    for (const auto& item : newPipes)
        pipes[item.first] = item.second;
    for (const auto& item : newKcs)
        kcs[item.first] = item.second;
    PipeID = newPipeID;
    KCID = newKCID;
    std::cout << "File loaded!\n";
}

bool Manager::readconsolpipe(Pipe& pipe)
{
    std::string name;
    double dlina;
    int diametr, remont;

    std::cout << "\nRead Name Pipe: ";
    std::cin.ignore(10000, '\n');
    if (!std::getline(std::cin, name)) return false;
    while (name.empty())
    {
        std::cout << "No! Name Pipe pusto! Read: ";
        if (!std::getline(std::cin, name)) return false;
    }
    std::cerr << name << "\n";

    while (true)
    {
        std::cout << "Read dlina(km) Pipe: ";
        if ((std::cin >> dlina) && dlina > 0 && std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "No! Read positive dlina: \n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr.precision(17);
    std::cerr << dlina << "\n";

    while (true)
    {
        std::cout << "Read diametr(mm) Pipe: ";
        if ((std::cin >> diametr) && diametr > 0 && std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "No! Read positive diametr: \n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << diametr << "\n";

    while (true)
    {
        std::cout << "V remonte? Yes-1 / No-0: ";
        if ((std::cin >> remont) && (remont == 0 || remont == 1) &&
            std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "Input 0 or 1!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << remont << "\n";

    pipe.SetNamepipe(name);
    pipe.SetDlinapipe(dlina);
    pipe.SetMmpipe(diametr);
    pipe.SetRemontpipe(remont == 1);
    return true;
}

bool Manager::readconsolkc(KC& kc)
{
    std::string name;
    int vsego, rabot, clas;

    std::cout << "\nRead Name KC: ";
    std::cin.ignore(10000, '\n');
    if (!std::getline(std::cin, name)) return false;
    while (name.empty())
    {
        std::cout << "No! Name KC pusto! Read: ";
        if (!std::getline(std::cin, name)) return false;
    }
    std::cerr << name << "\n";

    while (true)
    {
        std::cout << "Read kol-vo ZEH in KC: ";
        if ((std::cin >> vsego) && vsego > 0 && std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "No! Read positive kol-vo ZEH!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << vsego << "\n";

    while (true)
    {
        std::cout << "Read working ZEH: ";
        if ((std::cin >> rabot) && rabot >= 0 && rabot <= vsego &&
            std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "No! Read working ZEH from 0 to total!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << rabot << "\n";

    while (true)
    {
        std::cout << "Read class KC: ";
        if ((std::cin >> clas) && clas > 0 && std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "No! Read positive class!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << clas << "\n";

    kc.SetNamekc(name);
    kc.SetKolvozehkc(vsego);
    kc.Setzehrabot(rabot);
    kc.SetClasskc(clas);
    return true;
}