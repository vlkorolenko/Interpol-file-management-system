#include "Criminal.h"

void Criminal::loadCriminalsFromFile()
{
    criminalDatabase.clear(); // Clear existing database
    std::ifstream file("criminals.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string firstName, lastName, nickname, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime;
        int height;

        std::getline(iss, firstName, ',');
        std::getline(iss, lastName, ',');
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

        Criminal criminal(firstName, lastName, nickname, height, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime);
        criminalDatabase.push_back(criminal);
    }
    file.close();
}

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

std::vector<Criminal> Criminal::criminalDatabase;

void Criminal::searchByCriteria() const
{
    std::cout << "Select search criterion:\n";
    std::cout << "1. First Name\n";
    std::cout << "2. Last Name\n";
    std::cout << "3. Nickname\n";
    std::cout << "Enter option (1-3): ";

    int option;
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string criteria;
    switch (option) {
    case 1:
        std::cout << "Enter first name: ";
        std::getline(std::cin, criteria);
        break;
    case 2:
        std::cout << "Enter last name: ";
        std::getline(std::cin, criteria);
        break;
    case 3:
        std::cout << "Enter nickname: ";
        std::getline(std::cin, criteria);
        break;
    default:
        std::cout << "Invalid option selected.\n";
        return;
    }

    loadCriminalsFromFile(); // Load criminals from file
    std::vector<Criminal> results;

    for (const auto& criminal : criminalDatabase) {
        if ((option == 1 && criminal.firstName == criteria) ||
            (option == 2 && criminal.lastName == criteria) ||
            (option == 3 && criminal.nickname == criteria)) {
            results.push_back(criminal);
        }
    }

    if (results.empty()) {
        std::cout << "No criminals found with the given criteria.\n";
    }
    else {
        system("cls");
        std::cout << "Found " << results.size() << " criminals.\n\n";
        for (const auto& criminal : results) {
            criminal.displayResults();
        }
    }
}

void Criminal::displayResults() const
{
    std::cout << "First name: " << firstName << std::endl;
    std::cout << "Last name: " << lastName << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Eye color: " << eyeColor << std::endl;
    std::cout << "Hair color: " << hairColor << std::endl;
    std::cout << "Special features: " << specialFeatures << std::endl;
    std::cout << "Nationality: " << nationality << std::endl;
    std::cout << "Birth date: " << birthDate << std::endl;
    std::cout << "Birth place: " << birthPlace << std::endl;
    std::cout << "Last residence: " << lastResidence << std::endl;
    std::cout << "Knowledge of law: " << lawKnowledge << std::endl;
    std::cout << "Criminal profession: " << criminalProfession << std::endl;
    std::cout << "Last crime: " << lastCrime << std::endl;
    std::cout << "-------------\n";
}
