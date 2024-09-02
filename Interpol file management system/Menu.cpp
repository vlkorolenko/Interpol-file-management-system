#include "Menu.h"

void addCriminal(Criminal& criminal) {
    criminal.inputInfo();
}

int Menu::displayMenu()
{
    bool menuIsOpen = true;

    while (menuIsOpen)
    {
        try
        {
            std::cout << "Menu:\n";
            std::cout << "1. Add New Criminal\n";
            std::cout << "2. List of criminals\n";;
            std::cout << "3. Archive Criminal\n";
            std::cout << "4. Delete Criminal After Death\n";
            std::cout << "5. View Criminal Information\n";
            std::cout << "6. Search Criminals by Criteria\n";
            std::cout << "7. View Criminal Organizations List\n";
            std::cout << "8. Add New Organization\n";
            std::cout << "9. Update Organization Data\n";
            std::cout << "10. View Case History\n";
            std::cout << "11. [Exit]\n";
            std::cout << "Choose option: ";

            int option;
            std::cin >> option;

            // Перевірка на коректність введення
            if (std::cin.fail() || option > 11 || option <= 0) {
                std::cin.clear(); // очищаємо прапор помилки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // відкидаємо некоректний ввід
                throw std::invalid_argument("Incorrect entry. Please try again.");
            }

            switch (option)
            {
            case 1:
                system("cls");
                {
                    Criminal criminal; // Create a local object
                    addCriminal(criminal); // Call the function to handle input
                }
                break;
            case 2:
                system("cls");
                displayCriminals();
                /*{
                    Criminal criminal;
                    criminal.displayInfo();
                }*/
                break;
            case 3:
                system("cls");
                {
                    std::string lastName;
                    std::cout << "Enter the last name of the criminal to archive: ";
                    std::cin >> lastName;

                    Criminal criminal = criminal.findCriminalByLastName(lastName); // Find the criminal by last name
                    if (!criminal.getLastName().empty()) { // Check if the criminal was found
                        criminal.archiveCriminal(criminal); // Archive the criminal
                        criminal.removeFromActiveList(lastName); // Remove from active list
                        std::cout << "Criminal archived successfully.\n";
                    }
                    else {
                        std::cout << "Criminal not found.\n";
                    }
                }
                break;
            case 4:
                system("cls");
                cout << "Soon\n";
                break;
            case 5:
                system("cls");
                cout << "Soon\n";
                break;
            case 6:
                system("cls");
                cout << "Soon\n";
                break;
            case 7:
                system("cls");
                cout << "Soon\n";
                break;
            case 8:
                system("cls");
                cout << "Soon\n";
                break;
            case 9:
                system("cls");
                cout << "Soon\n";
                break;
            case 10:
                system("cls");
                cout << "Soon\n";
                break;
            case 11:
                cout << "Exiting...\n";
                return 0;

            }
            int variant = 0;
            do {
                cout << "\n1. Back to menu";
                cout << "\n2. [Exit]\n";
                cout << "Choose option: ";
                cin >> variant;
                while (variant < 1 || variant > 2)
                {
                    std::cout << "Incorrect option. \nTry again: ";
                    std::cin >> variant;
                }
                if (variant == 2)
                {
                    cout << "Exiting...\n";
                    return 0;
                }
                else
                {
                    system("cls");
                    break;
                }
            } while (variant != 1);
        }
        catch (exception ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
            std::cout << "Return to menu..." << std::endl;
            system("pause");
            system("cls");
        }

    }
}

void Menu::displayCriminals()
{
    std::ifstream file("criminals.txt");
    try
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
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
            std::string lawKnowledge;
            std::string criminalProfession;
            std::string lastCrime;

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
        file.close();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
