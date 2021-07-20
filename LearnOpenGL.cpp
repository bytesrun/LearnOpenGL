#include <iostream>
#include <string>

#include "start.h"
#include "lighting.h"
static void menu()
{
	std::cout << std::endl;
	std::cout << "MENU:" << std::endl;
	std::cout << "	1 Start" << std::endl;
	std::cout << "	2 Lighting" << std::endl;
	std::cout << "	0 quit" << std::endl;
	std::cout << "Please input: ";
}

int main(int argc, char* argv[])
{
	std::cout << "Welcome to LearnOpenGL!" << std::endl;
	int cmd = -1;
	while (cmd != 0) 
	{
		cmd = -1;
		menu();
		std::cin >> cmd;
		switch(cmd) {
			case 1:
				start();
				break;
			case 2:
				lighting();
				break;
			case 0:
				break;
			default:
				cmd = -1;
				break;
		}
		
	}
	//start();
	std::cout << "Enter any key to quit..." << std::endl;
	std::cin.get();
}