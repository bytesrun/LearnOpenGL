#include <iostream>
#include "helloWindows.h"
#include "helloTriangle.h"
#include "myShader.h"
#include "texture.h"
#include "transformations.h"
#include "CoordinateSystem.h"
#include "camera.h"
static void menu()
{
	std::cout << std::endl;
	std::cout << "MENU:" << std::endl;
	std::cout << "	1 Hello Window" << std::endl;
	std::cout << " 	2 Hello Triangle" << std::endl;
	std::cout << "	3 MyShader" << std::endl;
	std::cout << "	4 Texture" << std::endl;
	std::cout << "	5 Transformations" << std::endl;
	std::cout << "	6 Coordinate System" << std::endl;
	std::cout << "	7 Camera" << std::endl;
	std::cout << "	0 quit" << std::endl;
	std::cout << "Please input: ";
}

void start()
{
	int cmd = -1;
	while (cmd != 0)
	{
		cmd = -1;
		menu();
		std::cin >> cmd;
		switch(cmd) 
		{
			case 1:
				helloWindows();
				break;
			case 2:
				helloTriangle();
				break;
			case 3:
				myShader();
				break;
			case 4:
				texture();
				break;
			case 5:
				transformations();
				break;
			case 6:
				coordinateSys();
				break;
			case 7:
				camera();
				break;
			case 0:
				break;
			default:
				cmd = -1;
				break;
		}
	}
}