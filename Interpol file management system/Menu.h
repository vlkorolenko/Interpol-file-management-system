#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
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
};