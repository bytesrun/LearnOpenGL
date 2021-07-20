#include <iostream>

#include "colors.h"
#include "02_BasicLighting.h"
static void menu()
{
    std::cout << std::endl;
    std::cout << "MENU: " << std::endl;
    std::cout << "	1 Colors" << std::endl;
    std::cout << "	2 Basic Lighting" << std::endl;
    std::cout << "	0 quit" << std::endl;
    std::cout << "Please input: ";
}
void lighting()
{
    int cmd = -1;
    while (cmd != 0) {
        menu();
        std::cin >> cmd;
        switch (cmd) 
        {
            case 1:
                colors();
                break;
            case 2:
                basicLighting();
                break;
            case 0:
                break;
            default:
                cmd = -1;
        }
    }
}