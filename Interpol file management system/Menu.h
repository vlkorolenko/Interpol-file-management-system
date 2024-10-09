#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include "Person.h"
#include "Criminal.h"
#include "CriminalGroup.h"

using namespace std;

class Menu
{
public:

	int displayMenu();
	void displayCriminals();
	void displayArchive();
	void displayCriminalGroups();
	void displayUserGuide();
	void displayInstructions(int choice);
	void displaySortMenu();
};