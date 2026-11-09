#include <iostream>
#include <fstream>
#include "Manager.h"
#include "Utils.h"
#include "Logger.h"

int main()
{
    std::ofstream logfile("log.txt", std::ios::trunc);
    Logger log(std::cerr);
    if (logfile)
        log.vFile(logfile);
    else
        std::cout << "Log file ERROR!\n";

    Manager manager;
    char vvod;

    while (true)
    {
        menu();
        while (true)
        {
            std::cout << "\nInput: ";
            if ((std::cin >> vvod) && (vvod >= '0' && vvod <= '6') &&
                std::cin.peek() == '\n')
                break;
            if (std::cin.eof()) return 0;
            std::cout << "Input 0-6!\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        std::cerr << vvod << "\n";

        switch (vvod)
        {
        case '1':
            manager.addPipe();
            break;
        case '2':
            manager.addKC();
            break;
        case '3':
            manager.lookPipes();
            break;
        case '4':
            manager.lookKC();
            break;
        case '5':
            manager.saveFile();
            break;
        case '6':
            manager.loadFile();
            break;
        case '0':
            std::cout << "\nBye Bye!\n";
            return 0;
        }
    }
}