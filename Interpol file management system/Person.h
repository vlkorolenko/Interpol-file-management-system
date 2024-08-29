#pragma once
#include <iostream>
#include <string>

class Person
{
protected:
    std::string name;
    std::string nickname;
    int height;
    std::string hairColor;
    std::string eyeColor;
    std::string specialFeatures;
    std::string nationality;
    std::string birthPlace;
    std::string birthDate;
    std::string lastResidence;
public:
    virtual void inputInfo();
    virtual void displayInfo();
    virtual ~Person() = default;
};
