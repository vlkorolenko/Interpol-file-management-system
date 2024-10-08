#include <iostream>
#include <windows.h>
#include "Menu.h"

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu menu;
	menu.displayMenu();
}