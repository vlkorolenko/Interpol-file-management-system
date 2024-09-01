#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Person.h"

class Criminal : public Person
{
private:
    std::string lawKnowledge;
    std::string criminalProfession;
    std::string lastCrime;
    //CriminalOrganization* organization;
    bool isArchived;
    bool isDeceased;

public:
    
    void inputInfo();
    void saveToFile(const Criminal criminal);

};

