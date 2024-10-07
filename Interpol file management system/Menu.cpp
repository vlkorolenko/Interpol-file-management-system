#include "Menu.h"

void addCriminal(Criminal& criminal)
{
    criminal.inputInfo();
}

void addCriminalGroup(CriminalGroup& criminalGroup)
{
    criminalGroup.inputInfo();
}

int Menu::displayMenu()
{
    bool menuIsOpen = true;

    while (menuIsOpen)
    {
        try
        {
            std::cout << "Menu:\n";
            std::cout << "1. Add new criminal\n";
            std::cout << "2. List of criminals\n";;
            std::cout << "3. Archive criminal\n";
            std::cout << "4. Delete criminal after death\n";
            std::cout << "5. View criminal information\n";
            std::cout << "6. Search criminals by criteria\n";
            std::cout << "7. Add new organization\n";
            std::cout << "8. View criminal organizations list\n";
            std::cout << "9. Update organization data\n";
            std::cout << "10. Archive\n";
            std::cout << "11. [Exit]\n";
            std::cout << "Choose option: ";

            int option;
            std::cin >> option;

            // Перевірка на коректність введення
            if (std::cin.fail() || option > 11 || option <= 0)
            {
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
                break;
            case 3:
                system("cls");
                {
                    std::string firstName, lastName;
                    std::cout << "Enter the FIRST name of the criminal to archive: ";
                    std::cin >> firstName;
                    std::cout << "Enter the LAST name of the criminal to archive: ";
                    std::cin >> lastName;

                    Criminal criminal = criminal.findCriminalByName(firstName, lastName); // Find the criminal by last name
                    if (!criminal.getLastName().empty()) { // Check if the criminal was found
                        criminal.archiveCriminal(criminal); // Archive the criminal
                        criminal.removeFromActiveList(lastName); // Remove from active list
                        std::cout << "Criminal archived successfully.\n";
                    }
                    else
                    {
                        std::cout << "Criminal not found.\n";
                    }
                }
                break;
            case 4:
                system("cls");
                {
                    std::string firstName, lastName;
                    std::cout << "Enter the FIRST name of the criminal to archive: ";
                    std::cin >> firstName;
                    std::cout << "Enter the LAST name of the criminal to archive: ";
                    std::cin >> lastName;

                    Criminal criminal = criminal.findCriminalByNameInArchive(firstName, lastName); // Find the criminal by last name
                    if (!criminal.getLastName().empty()) { // Check if the criminal was found
                        criminal.removeFromArchive(lastName); // Archive the criminal
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Criminal not found.\n";
                    }
                }
                break;
            case 5:
                system("cls");
                cout << "Soon\n";
                break;
            case 6:
                system("cls");
                {
                    Criminal criminal;
                    criminal.searchByCriteria();
                }
                break;
            case 7:
                system("cls");
                {
                    CriminalGroup criminalGroup;
                    addCriminalGroup(criminalGroup);
                }
                break;
            case 8:
                system("cls");
                {
                    CriminalGroup criminalGroup;
                    criminalGroup.displayCriminalGroups();
                }
                break;
            case 9:
                system("cls");
                displayCriminalGroups();
                break;
            case 10:
                system("cls");
                displayArchive();
                break;
            case 11:
                cout << "Exiting...\n";
                return 0;

            }
            int variant = 0;

            while (variant != 1)
            {
                try
                {
                    std::cout << "1. Back to menu";
                    std::cout << "\n2. [Exit]\n";
                    std::cout << "Choose option: ";
                    std::cin >> variant;

                    // Перевіряємо, чи ввів користувач рядок замість числа
                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Input is not a number. Please enter a valid option.");
                    }

                    // Перевірка на діапазон варіантів
                    if (variant < 1 || variant > 2)
                    {
                        throw std::out_of_range("Invalid option. Please enter 1 or 2.");
                    }

                    // Обробка вибору користувача
                    if (variant == 2)
                    {
                        std::cout << "Exiting...\n";
                        return 0;
                    }
                    else
                    {
                        system("cls");
                        break;
                    }
                }
                catch (const std::invalid_argument& e)
                {
                    // Очищення вводу та виведення повідомлення про помилку
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    system("cls");
                    std::cout << "Error: " << e.what() << std::endl << std::endl;
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << "Error: " << e.what() << std::endl << std::endl;
                }
            }
        }
        catch (exception ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
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

void Menu::displayArchive()
{
    std::ifstream file("archive.txt");
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

void Menu::displayCriminalGroups()
{
    std::vector<CriminalGroup> groups = CriminalGroup::loadFromFile();
    if (groups.empty())
    {
        std::cout << "No groups found." << std::endl;
        return;
    }

    // Display groups
    std::cout << "Available Criminal Groups:" << std::endl;
    for (size_t i = 0; i < groups.size(); ++i)
    {
        std::cout << i + 1 << ". " << groups[i].getGroupName() << std::endl;
    }

    // User selects a group
    std::cout << "Select a group by number: ";
    int groupIndex;
    std::cin >> groupIndex;

    if (groupIndex < 1 || groupIndex > groups.size())
    {
        std::cout << "Invalid selection." << std::endl;
        return;
    }

    CriminalGroup& selectedGroup = groups[groupIndex - 1];
    //selectedGroup.displayCriminalGroups();
    system("cls");
    int choice;
    do
    {
        std::cout << "Group: " << selectedGroup.getGroupName() << "\n";
        const std::vector<Criminal>& members = selectedGroup.getMembers(); // Отримати список членів
        for (size_t i = 0; i < members.size(); ++i)
        {
            std::cout << "  Member: " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
        }
        std::cout << "\n-------------\n\n";
        // Option to update the selected group
        std::cout << "1. Add member" << std::endl;
        std::cout << "2. Remove member" << std::endl;
        std::cout << "3. Remove group" << std::endl;
        std::cout << "4. [Back to menu]" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice > 4 || choice <= 0)
        {
            system("cls");
            cout << "Invalid option. Try again.\n\n";
        }
    } while (choice > 4 || choice <= 0);
    system("cls");

    switch (choice)
    {
    case 1:
    {
        // Додавання учасника
        bool criminalFound = false;
        std::string firstName, lastName;
        while (!criminalFound) {
            std::cout << "Enter the FIRST name of the criminal: ";
            std::cin >> firstName;
            std::cout << "Enter the LAST name of the criminal: ";
            std::cin >> lastName;

            Criminal criminal = criminal.findCriminalByName(firstName, lastName); // Знайти злочинця

            if (!criminal.getLastName().empty())
            {
                if (criminal.isCriminalInGroup(selectedGroup, criminal))
                {
                    system("cls");
                    std::cout << criminal.getFirstName() + " " + criminal.getLastName() + " is already a member of the group.\n";
                }
                else
                {
                    selectedGroup.addMember(criminal); // Додати члена в групу
                    selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
                    selectedGroup.saveToFile(selectedGroup); // Зберегти зміни в файл
                    system("cls");
                    std::cout << "Criminal added successfully to the group. " << std::endl;
                    criminalFound = true; // Вихід з циклу
                }

            }
            else
            {
                system("cls");
                std::cout << "Criminal not found. Try again.\n";
            }
        }
        break;
    }
    case 2:
    {
        const std::vector<Criminal>& members = selectedGroup.getMembers(); // Отримати список членів групи

        if (members.empty())
        {
            std::cout << "No members in the group." << std::endl;
        }
        else
        {
            int memberIndex = 0;
            bool validInput = false;

            while (!validInput)
            {
                // Виводимо список членів групи при кожній ітерації циклу
                std::cout << "Group: " << selectedGroup.getGroupName() << "\n";
                for (size_t i = 0; i < members.size(); ++i)
                {
                    std::cout << "  " << i + 1 << ". " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
                }

                std::cout << "\n-------------\n\n";

                try
                {
                    std::cout << "Enter the number of the member to remove: ";
                    std::cin >> memberIndex;

                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Invalid input. Please enter a number.");
                    }

                    if (memberIndex < 1 || memberIndex > members.size())
                    {
                        throw std::out_of_range("Invalid selection. Please choose a valid member number.");
                    }

                    // Якщо ввід коректний, встановлюємо прапорець validInput в true для виходу з циклу
                    validInput = true;
                }
                catch (const std::invalid_argument& e)
                {
                    std::cin.clear(); // Очищення помилки
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск некоректного вводу
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                }
            }

            // Після коректного вводу видаляємо члена
            const Criminal& memberToRemove = members[memberIndex - 1];
            selectedGroup.removeMember(selectedGroup.getGroupName(), memberToRemove.getFirstName(), memberToRemove.getLastName());
        }
        break;
    }
    case 3:
        selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
        system("cls");
        std::cout << "Group removed successfully." << std::endl;
        break;
    case 4:
        break;
    default:
        system("cls");
        std::cout << "Invalid option." << std::endl;
        break;
    }
}