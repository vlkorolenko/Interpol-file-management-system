#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Person.h"
#include "ISearchable.h"
#include "CriminalGroup.h"

class Criminal : public Person, public ISearchable
{
private:

    std::string lawKnowledge;
    std::string criminalProfession;
    std::string lastCrime;
    static std::vector<Criminal> criminalDatabase;
    static void loadCriminalsFromFile();

public:

    Criminal() {}

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

    Criminal(const Criminal& other)
    {
        firstName = other.firstName;
        lastName = other.lastName;
        nickname = other.nickname;
        height = other.height;
        hairColor = other.hairColor;
        eyeColor = other.eyeColor;
        specialFeatures = other.specialFeatures;
        nationality = other.nationality;
        birthDate = other.birthDate;
        birthPlace = other.birthPlace;
        lastResidence = other.lastResidence;
        lawKnowledge = other.lawKnowledge;
        criminalProfession = other.criminalProfession;
        lastCrime = other.lastCrime;
    }

    // Конструктор переміщення
    Criminal(Criminal&& other) noexcept
    {
        firstName = std::move(other.firstName);
        lastName = std::move(other.lastName);
        nickname = std::move(other.nickname);
        height = other.height;
        hairColor = std::move(other.hairColor);
        eyeColor = std::move(other.eyeColor);
        specialFeatures = std::move(other.specialFeatures);
        nationality = std::move(other.nationality);
        birthDate = std::move(other.birthDate);
        birthPlace = std::move(other.birthPlace);
        lastResidence = std::move(other.lastResidence);
        lawKnowledge = std::move(other.lawKnowledge);
        criminalProfession = std::move(other.criminalProfession);
        lastCrime = std::move(other.lastCrime);
    }

    // Оператор копіювання
    Criminal& operator=(const Criminal& other)
    {
        if (this != &other) {
            firstName = other.firstName;
            lastName = other.lastName;
            nickname = other.nickname;
            height = other.height;
            hairColor = other.hairColor;
            eyeColor = other.eyeColor;
            specialFeatures = other.specialFeatures;
            nationality = other.nationality;
            birthDate = other.birthDate;
            birthPlace = other.birthPlace;
            lastResidence = other.lastResidence;
            lawKnowledge = other.lawKnowledge;
            criminalProfession = other.criminalProfession;
            lastCrime = other.lastCrime;
        }
        return *this;
    }

    // Оператор переміщення
    Criminal& operator=(Criminal&& other) noexcept
    {
        if (this != &other) {
            firstName = std::move(other.firstName);
            lastName = std::move(other.lastName);
            nickname = std::move(other.nickname);
            height = other.height;
            hairColor = std::move(other.hairColor);
            eyeColor = std::move(other.eyeColor);
            specialFeatures = std::move(other.specialFeatures);
            nationality = std::move(other.nationality);
            birthDate = std::move(other.birthDate);
            birthPlace = std::move(other.birthPlace);
            lastResidence = std::move(other.lastResidence);
            lawKnowledge = std::move(other.lawKnowledge);
            criminalProfession = std::move(other.criminalProfession);
            lastCrime = std::move(other.lastCrime);
        }
        return *this;
    }

    // Деструктор
    ~Criminal() {}

    std::string getLastName() const {return lastName;}
    std::string getFirstName() const { return firstName; }
    void setFirstName(const std::string& fn) { firstName = fn; }
    void setLastName(const std::string& ln) { lastName = ln; }

    void inputInfo();
    void saveToFile(const Criminal& criminal);
    void archiveCriminal(const Criminal& criminal);
    void removeFromActiveList(const std::string& lastName);
    Criminal findCriminalByName(const std::string& firstName, std::string& lastName);
    void searchByCriteria() const override;
    void displayResults() const override;
    bool isCriminalInGroup(const CriminalGroup& group, const Criminal& criminal);
    void removeFromArchive(const std::string& lastName);
    Criminal findCriminalByNameInArchive(const std::string& firstName, std::string& lastName);
};