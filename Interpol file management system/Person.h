#pragma once
#include <iostream>
#include <string>
#include <vector>

class Person
{
protected:
    std::string firstName;
    std::string lastName;
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
    //virtual void inputInfo() const = 0;
    //virtual void displayInfo();
    virtual ~Person() = default;
};
