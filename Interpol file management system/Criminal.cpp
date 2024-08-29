#include "Criminal.h"

void Criminal::inputInfo()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Criminal newCriminal;
    std::cout << "Enter criminal details:" << std::endl;
    std::cout << "First name: ";
    std::getline(std::cin, newCriminal.firstName);
    std::cout << "Last name: ";
    std::getline(std::cin, newCriminal.lastName);
    std::cout << "Nickname: ";
    std::getline(std::cin, newCriminal.nickname);
    std::cout << "Height: ";
    std::cin >> newCriminal.height;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Eye color: ";
    std::getline(std::cin, newCriminal.eyeColor);
    std::cout << "Hair color: ";
    std::getline(std::cin, newCriminal.hairColor);
    std::cout << "Special features: ";
    std::getline(std::cin, newCriminal.specialFeatures);
    std::cout << "Nationality: ";
    std::getline(std::cin, newCriminal.nationality);
    std::cout << "Birth date (DD/MM/YYYY): ";
    std::getline(std::cin, newCriminal.birthDate);
    std::cout << "Birth place: ";
    std::getline(std::cin, newCriminal.birthPlace);
    std::cout << "Last residence: ";
    std::getline(std::cin, newCriminal.lastResidence);
    std::cout << "Knowledge of law: ";
    std::getline(std::cin, newCriminal.lawKnowledge);
    std::cout << "Criminal profession: ";
    std::getline(std::cin, newCriminal.criminalProfession);
    std::cout << "Last crime: ";
    std::getline(std::cin, newCriminal.lastCrime);
    saveToFile(newCriminal);
}

void Criminal::saveToFile(const Criminal criminal)
{
    std::ofstream file("criminals.txt", std::ios::app);
    if (file.is_open())
    {
        file << criminal.firstName << "," << criminal.lastName << "," << criminal.nickname << "," << 
            criminal.height << "," << criminal.eyeColor << "," << criminal.hairColor << "," << criminal.specialFeatures <<
            "," << criminal.nationality << "," << criminal.birthDate << "," << criminal.birthPlace << "," <<
            criminal.lastResidence << "," << criminal.lawKnowledge << "," << criminal.criminalProfession << "," <<
            criminal.lastCrime << std::endl;
        file.close();
        std::cout << "\nNew criminal added successfully." << std::endl;
    }
    else
    {
        std::cout << "\nUnable to open file." << std::endl;
    }
}
