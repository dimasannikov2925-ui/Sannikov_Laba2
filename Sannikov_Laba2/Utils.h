#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

inline void menu()
{
    std::cout << "\n1.Add Pipe\n";
    std::cout << "2.Add KC\n";
    std::cout << "3.Look Pipes\n";
    std::cout << "4.Look KC\n";
    std::cout << "5.Save\n";
    std::cout << "6.Open\n";
    std::cout << "0.Exit\n";
}

template <typename T>
bool deleteByID(std::unordered_map<int, T>& objects, int id)
{
    return objects.erase(id) == 1;
}

inline bool selectIDs(const std::vector<int>& found, std::vector<int>& selected)
{
    char choice;
    std::cout << "\n1.Choose by ID\n2.All found\n";
    while (true)
    {
        std::cout << "Input: ";
        if ((std::cin >> choice) && (choice == '1' || choice == '2') &&
            std::cin.peek() == '\n')
            break;
        if (std::cin.eof()) return false;
        std::cout << "Input 1 or 2!\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cerr << choice << "\n";

    if (choice == '2')
    {
        selected = found;
        return true;
    }

    std::cout << "Input IDs one by one. 0 to finish.\n";
    while (true)
    {
        int id;
        std::cout << "Input ID: ";
        if (!(std::cin >> id) || id < 0 || std::cin.peek() != '\n')
        {
            if (std::cin.eof()) return false;
            std::cout << "Wrong ID!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (id == 0)
        {
            std::cerr << id << "\n";
            break;
        }

        bool est = false;
        for (int foundID : found)
        {
            if (foundID == id) est = true;
        }
        if (!est)
        {
            std::cout << "No such ID among found!\n";
            continue;
        }

        bool povtor = false;
        for (int selectedID : selected)
        {
            if (selectedID == id) povtor = true;
        }
        if (povtor)
        {
            std::cout << "ID already selected!\n";
            continue;
        }
        std::cerr << id << "\n";
        selected.push_back(id);
    }
    return true;
}
