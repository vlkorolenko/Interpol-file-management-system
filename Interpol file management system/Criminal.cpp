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
        while (!(std::cin >> newCriminal.height))  // Зчитування та перевірка введення height
        {
            std::cin.clear();  // Очищення стану помилки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Видалення залишків вводу
            std::cout << "Invalid input. Please enter a number: ";
        }
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

void Criminal::saveToFile(const Criminal& criminal)
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

void Criminal::archiveCriminal(const Criminal& criminal)
{
    std::ofstream archiveFile("archive.txt", std::ios::app);
    if (archiveFile.is_open()) {
        archiveFile << criminal.firstName << "," << criminal.lastName << "," << criminal.nickname << ","
            << criminal.height << "," << criminal.eyeColor << "," << criminal.hairColor << ","
            << criminal.specialFeatures << "," << criminal.nationality << "," << criminal.birthDate
            << "," << criminal.birthPlace << "," << criminal.lastResidence << ","
            << criminal.lawKnowledge << "," << criminal.criminalProfession << ","
            << criminal.lastCrime << std::endl;
        archiveFile.close();
    }
    else {
        std::cerr << "Unable to open archive file." << std::endl;
    }
}

void Criminal::removeFromActiveList(const std::string& lastName)
{
    std::ifstream inFile("criminals.txt");
    std::ofstream tempFile("temp.txt");

    if (inFile.is_open() && tempFile.is_open())
    {
        std::string line;
        while (getline(inFile, line))
        {
            if (line.find(lastName) == std::string::npos)
                tempFile << line << std::endl;
        }
        inFile.close();
        tempFile.close();
        remove("criminals.txt");
        rename("temp.txt", "criminals.txt");
    }
}

Criminal Criminal::findCriminalByLastName(const std::string& lastName)
{
    std::ifstream inFile("criminals.txt");
    std::string line;
    Criminal foundCriminal;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string firstName, lastNameInFile, nickname, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime;
        int height;

        std::getline(iss, firstName, ',');
        std::getline(iss, lastNameInFile, ',');
        std::getline(iss, nickname, ',');
        iss >> height;
        iss.ignore();
        std::getline(iss, eyeColor, ',');
        std::getline(iss, hairColor, ',');
        std::getline(iss, specialFeatures, ',');
        std::getline(iss, nationality, ',');
        std::getline(iss, birthDate, ',');
        std::getline(iss, birthPlace, ',');
        std::getline(iss, lastResidence, ',');
        std::getline(iss, lawKnowledge, ',');
        std::getline(iss, criminalProfession, ',');
        std::getline(iss, lastCrime, ',');

        if (lastNameInFile == lastName) {
            foundCriminal = Criminal(firstName, lastNameInFile, nickname, height, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime);
            break;
        }
    }
    return foundCriminal;
}
