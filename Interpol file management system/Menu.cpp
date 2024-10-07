#include "Menu.h"

// Метод для додання нового злочинця у базу
void addCriminal(Criminal* criminal)
{
    criminal->inputInfo();  // Викликаємо метод для введення інформації про нового злочинця
}

// Метод для додання нової злочинної організації
void addCriminalGroup(CriminalGroup& criminalGroup)
{
    criminalGroup.inputInfo();  // Викликаємо метод для введення інформації про нову злочинну групу
}

// Виведення меню у консоль
int Menu::displayMenu()
{
    bool menuIsOpen = true;  // Змінна для збереження стану відкритого меню

    while (menuIsOpen)  // Цикл для відображення меню поки воно відкрите
    {
        try
        {
            std::cout << "Menu:\n";  // Виведення опцій меню
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
            std::cin >> option;  // Введення вибору користувача

            // Перевірка на коректність введення
            if (std::cin.fail() || option > 11 || option <= 0)
            {
                std::cin.clear();  // Очищуємо прапорець помилки вводу
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Пропускаємо некоректні символи
                throw std::invalid_argument("Incorrect entry. Please try again.");  // Генеруємо виняток при некоректному введенні
            }

            switch (option)  // Обробка введеного користувачем варіанту
            {
            case 1:
                system("cls");  // Очищуємо екран
                {
                    Criminal* newCriminal = new Criminal();  // Створюємо новий об'єкт злочинця
                    addCriminal(newCriminal);  // Викликаємо функцію для введення інформації про злочинця
                    delete newCriminal;  // Очищаємо пам'ять після використання об'єкта
                }
                break;
            case 2:
                system("cls");  // Очищуємо екран
                displayCriminals();  // Викликаємо функцію для відображення списку злочинців
                break;
            case 3:
                system("cls");  // Очищуємо екран
                {
                    std::string firstName, lastName;
                    std::cout << "Enter the FIRST name of the criminal to archive: ";  // Запитуємо ім'я
                    std::cin >> firstName;
                    std::cout << "Enter the LAST name of the criminal to archive: ";  // Запитуємо прізвище
                    std::cin >> lastName;

                    Criminal criminal = criminal.findCriminalByName(firstName, lastName);  // Пошук злочинця за ім'ям
                    if (!criminal.getLastName().empty())  // Якщо злочинець знайдений
                    {
                        system("cls");
                        criminal.archiveCriminal(criminal);  // Архівуємо злочинця
                        criminal.removeFromActiveList(lastName);  // Видаляємо з активного списку
                        std::cout << "Criminal archived successfully.\n";  // Виводимо повідомлення про успіх
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Criminal not found.\n";  // Повідомлення, якщо злочинця не знайдено
                    }
                }
                break;
            case 4:
                system("cls");
                {
                    std::string firstName, lastName;
                    std::cout << "Enter the FIRST name of the criminal to archive: ";  // Запитуємо ім'я
                    std::cin >> firstName;
                    std::cout << "Enter the LAST name of the criminal to archive: ";  // Запитуємо прізвище
                    std::cin >> lastName;

                    Criminal criminal = criminal.findCriminalByNameInArchive(firstName, lastName);  // Пошук злочинця в архіві
                    if (!criminal.getLastName().empty())  // Якщо знайдено
                    {
                        system("cls");
                        criminal.removeFromArchive(lastName);  // Видаляємо з архіву
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Criminal not found.\n";  // Повідомлення, якщо не знайдено
                    }
                }
                break;
            case 5:
                system("cls");  // Очищуємо екран
                cout << "Soon\n";  // Повідомлення, що функція ще не реалізована
                break;
            case 6:
                system("cls");  // Очищуємо екран
                {
                    Criminal criminal;
                    criminal.searchByCriteria();  // Викликаємо пошук за критеріями
                }
                break;
            case 7:
                system("cls");  // Очищуємо екран
                {
                    CriminalGroup criminalGroup;
                    addCriminalGroup(criminalGroup);  // Викликаємо функцію для додавання нової організації
                }
                break;
            case 8:
                system("cls");  // Очищуємо екран
                {
                    CriminalGroup criminalGroup;
                    criminalGroup.displayCriminalGroups();  // Виведення списку організацій
                }
                break;
            case 9:
                system("cls");  // Очищуємо екран
                displayCriminalGroups();  // Відображення даних про організації
                break;
            case 10:
                system("cls");  // Очищуємо екран
                displayArchive();  // Відображення архіву
                break;
            case 11:
                cout << "Exiting...\n";  // Повідомлення про вихід
                return 0;  // Завершення програми
            }

            int variant = 0;  // Змінна для вибору повернення до меню чи виходу

            while (variant != 1)
            {
                try
                {
                    std::cout << "1. Back to menu";  // Виводимо опції повернення до меню
                    std::cout << "\n2. [Exit]\n";
                    std::cout << "Choose option: ";
                    std::cin >> variant;  // Введення вибору

                    // Перевіряємо, чи ввів користувач рядок замість числа
                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Input is not a number. Please enter a valid option.");  // Виняток при некоректному введенні
                    }

                    // Перевірка на діапазон варіантів
                    if (variant < 1 || variant > 2)
                    {
                        throw std::out_of_range("Invalid option. Please enter 1 or 2.");  // Виняток при некоректному варіанті
                    }

                    // Обробка вибору користувача
                    if (variant == 2)
                    {
                        std::cout << "Exiting...\n";  // Повідомлення про вихід
                        return 0;  // Завершення програми
                    }
                    else
                    {
                        system("cls");  // Очищення екрану для повернення до меню
                        break;
                    }
                }
                catch (const std::invalid_argument& e)
                {
                    // Очищення вводу та виведення повідомлення про помилку
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    system("cls");
                    std::cout << "Error: " << e.what() << std::endl << std::endl;  // Виведення помилки
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << "Error: " << e.what() << std::endl << std::endl;  // Виведення помилки
                }
            }
        }
        catch (exception ex)  // Перехоплення загальних винятків
        {
            std::cout << "Error: " << ex.what() << std::endl;  // Виведення помилки
            system("pause");  // Пауза перед очищенням екрану
            system("cls");  // Очищення екрану після помилки
        }

    }
}

// Метод для відображення інформації про злочинців із файлу "criminals.txt"
void Menu::displayCriminals()
{
    std::ifstream file("criminals.txt"); // Відкриття файлу "criminals.txt" для читання
    try
    {
        std::string line;
        // Читання кожного рядка файлу, поки є рядки для обробки
        while (std::getline(file, line))
        {
            std::istringstream iss(line); // Створення потоку для парсингу рядка
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

            // Розбір полів з рядка CSV (розділеного комами)
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');
            std::getline(iss, nickname, ',');
            iss >> height;
            iss.ignore(); // Пропуск символу після числового значення
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

            // Виведення даних про злочинця
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
        file.close(); // Закриття файлу після обробки
    }
    catch (const std::runtime_error& e)
    {
        // Обробка можливих помилок під час читання файлу
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Метод для відображення архівованих злочинців із файлу "archive.txt"
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

            // Парсинг рядка CSV (розділеного комами)
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

// Виведення меню зі злочинними організаціями
void Menu::displayCriminalGroups()
{
    // Завантаження груп злочинців із файлу
    std::vector<CriminalGroup> groups = CriminalGroup::loadFromFile();
    if (groups.empty())
    {
        // Якщо груп немає, повідомляємо користувача
        std::cout << "No groups found." << std::endl;
        return;
    }

    // Виведення списку груп
    std::cout << "Available Criminal Groups:" << std::endl;
    for (size_t i = 0; i < groups.size(); ++i)
    {
        // Виводимо кожну групу по порядковому номеру
        std::cout << i + 1 << ". " << groups[i].getGroupName() << std::endl;
    }

    // Користувач обирає групу
    std::cout << "Select a group by number: ";
    int groupIndex;
    std::cin >> groupIndex;

    // Перевірка на правильність вибору
    if (groupIndex < 1 || groupIndex > groups.size())
    {
        std::cout << "Invalid selection." << std::endl;
        return;
    }

    // Отримуємо вибрану групу
    CriminalGroup& selectedGroup = groups[groupIndex - 1];
    system("cls");
    int choice;
    do
    {
        // Виведення інформації про вибрану групу та її членів
        std::cout << "Group: " << selectedGroup.getGroupName() << "\n";
        const std::vector<Criminal>& members = selectedGroup.getMembers(); // Отримати список членів
        for (size_t i = 0; i < members.size(); ++i)
        {
            std::cout << "  Member: " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
        }
        std::cout << "\n-------------\n\n";

        // Опції для користувача
        std::cout << "1. Add member" << std::endl;
        std::cout << "2. Remove member" << std::endl;
        std::cout << "3. Remove group" << std::endl;
        std::cout << "4. [Back to menu]" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Перевірка на правильність введення
        if (choice > 4 || choice <= 0)
        {
            system("cls");
            std::cout << "Invalid option. Try again.\n\n";
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
        while (!criminalFound)
        {
            std::cout << "Enter the FIRST name of the criminal: ";
            std::cin >> firstName;
            std::cout << "Enter the LAST name of the criminal: ";
            std::cin >> lastName;

            // Пошук злочинця
            Criminal criminal = criminal.findCriminalByName(firstName, lastName);

            if (!criminal.getLastName().empty())
            {
                // Перевіряємо, чи не є злочинець вже членом групи
                if (criminal.isCriminalInGroup(selectedGroup, criminal))
                {
                    system("cls");
                    std::cout << criminal.getFirstName() + " " + criminal.getLastName() + " is already a member of the group.\n";
                }
                else
                {
                    // Додавання злочинця до групи
                    selectedGroup.addMember(criminal);
                    selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
                    selectedGroup.saveToFile(selectedGroup); // Збереження змін у файл
                    system("cls");
                    std::cout << "Criminal added successfully to the group." << std::endl;
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
        // Видалення члена групи
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
                // Виводимо список членів групи
                std::cout << "Group: " << selectedGroup.getGroupName() << "\n";
                for (size_t i = 0; i < members.size(); ++i)
                {
                    std::cout << "  " << i + 1 << ". " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
                }

                std::cout << "\n-------------\n\n";

                try
                {
                    // Вибір члена для видалення
                    std::cout << "Enter the number of the member to remove: ";
                    std::cin >> memberIndex;

                    // Перевірка на коректність вводу
                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Invalid input. Please enter a number.");
                    }

                    if (memberIndex < 1 || memberIndex > members.size())
                    {
                        throw std::out_of_range("Invalid selection. Please choose a valid member number.");
                    }

                    validInput = true; // Вихід з циклу після коректного вводу
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

            // Видалення вибраного члена
            const Criminal& memberToRemove = members[memberIndex - 1];
            selectedGroup.removeMember(selectedGroup.getGroupName(), memberToRemove.getFirstName(), memberToRemove.getLastName());
        }
        break;
    }
    case 3:
        // Видалення групи
        selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
        system("cls");
        std::cout << "Group removed successfully." << std::endl;
        break;
    case 4:
        // Повернення до меню
        break;
    default:
        system("cls");
        std::cout << "Invalid option." << std::endl;
        break;
    }
}