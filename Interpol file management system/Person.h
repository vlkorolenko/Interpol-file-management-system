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
    Person() = default;

    // Конструктор із параметрами
    Person(const std::string& firstName, const std::string& lastName, const std::string& nickname, int height, const std::string& hairColor,
        const std::string& eyeColor, const std::string& specialFeatures, const std::string& nationality, const std::string& birthPlace,
        const std::string& birthDate, const std::string& lastResidence)
        : firstName(firstName), lastName(lastName), nickname(nickname), height(height), hairColor(hairColor),
        eyeColor(eyeColor), specialFeatures(specialFeatures), nationality(nationality), birthPlace(birthPlace),
        birthDate(birthDate), lastResidence(lastResidence){}

    // Конструктор копіювання
    Person(const Person& other)
        : firstName(other.firstName), lastName(other.lastName), nickname(other.nickname), height(other.height),
        hairColor(other.hairColor), eyeColor(other.eyeColor), specialFeatures(other.specialFeatures),
        nationality(other.nationality), birthPlace(other.birthPlace), birthDate(other.birthDate),
        lastResidence(other.lastResidence){}

    // Оператор копіювання
    Person& operator=(const Person& other)
    {
        if (this != &other)
        {
            firstName = other.firstName;
            lastName = other.lastName;
            nickname = other.nickname;
            height = other.height;
            hairColor = other.hairColor;
            eyeColor = other.eyeColor;
            specialFeatures = other.specialFeatures;
            nationality = other.nationality;
            birthPlace = other.birthPlace;
            birthDate = other.birthDate;
            lastResidence = other.lastResidence;
        }
        return *this;
    }

    // Конструктор переміщення
    Person(Person&& other) noexcept
        : firstName(std::move(other.firstName)), lastName(std::move(other.lastName)), nickname(std::move(other.nickname)),
        height(other.height), hairColor(std::move(other.hairColor)), eyeColor(std::move(other.eyeColor)),
        specialFeatures(std::move(other.specialFeatures)), nationality(std::move(other.nationality)),
        birthPlace(std::move(other.birthPlace)), birthDate(std::move(other.birthDate)), lastResidence(std::move(other.lastResidence))
    {}

    // Оператор переміщення
    Person& operator=(Person&& other) noexcept
    {
        if (this != &other)
        {
            firstName = std::move(other.firstName);
            lastName = std::move(other.lastName);
            nickname = std::move(other.nickname);
            height = other.height;
            hairColor = std::move(other.hairColor);
            eyeColor = std::move(other.eyeColor);
            specialFeatures = std::move(other.specialFeatures);
            nationality = std::move(other.nationality);
            birthPlace = std::move(other.birthPlace);
            birthDate = std::move(other.birthDate);
            lastResidence = std::move(other.lastResidence);
        }
        return *this;
    }

    // Деструктор
    virtual ~Person(){}
};