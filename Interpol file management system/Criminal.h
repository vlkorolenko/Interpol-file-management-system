#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Person.h"

class Criminal : public Person
{
private:

    std::string criminalProfession;
    std::string lastCrime;
    //CriminalOrganization* organization;
    bool isArchived;
    bool isDeceased;

public:
    
    void inputInfo();
    void saveToFile();
};

