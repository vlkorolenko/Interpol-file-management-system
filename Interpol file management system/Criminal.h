#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Person.h"
#include "ISearchable.h"

class Criminal : public Person, public ISearchable
{
private:
    std::string lawKnowledge;
    std::string criminalProfession;
    std::string lastCrime;
    //CriminalOrganization* organization;
    bool isArchived;
    bool isDeceased;
    static std::vector<Criminal> criminalDatabase;
    static void loadCriminalsFromFile(); // Load criminals from file

public:
    Criminal() {
        // ������������ ������� �� �������������
    }
    Criminal(std::string firstName, std::string lastName, std::string nickname, int height,
        std::string hairColor, std::string eyeColor, std::string specialFeatures,
        std::string nationality, std::string birthDate, std::string birthPlace,
        std::string lastResidence, std::string lawKnowledge,
        std::string criminalProfession, std::string lastCrime)
    {
        this->firstName = firstName;
        this->lastName = lastName;
        this->nickname = nickname;
        this->height = height;
        this->hairColor = hairColor;
        this->eyeColor = eyeColor;
        this->specialFeatures = specialFeatures;
        this->nationality = nationality;
        this->birthDate = birthDate;
        this->birthPlace = birthPlace;
        this->lastResidence = lastResidence;
        this->lawKnowledge = lawKnowledge;
        this->criminalProfession = criminalProfession;
        this->lastCrime = lastCrime;
    }

    std::string getLastName() const {return lastName;}

    void inputInfo();
    void saveToFile(const Criminal& criminal);
    void archiveCriminal(const Criminal& criminal);
    void removeFromActiveList(const std::string& lastName);
    Criminal findCriminalByName(const std::string& firstName, std::string& lastName);
    void searchByCriteria() const override;
    void displayResults() const override;
    void displayArchive();
};

