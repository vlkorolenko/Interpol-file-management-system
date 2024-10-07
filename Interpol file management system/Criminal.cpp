#include "Criminal.h"

// Завантаження злочинців із файлу в базу даних
void Criminal::loadCriminalsFromFile()
{
    criminalDatabase.clear(); // Очищуємо поточну базу даних злочинців
    std::ifstream file("criminals.txt"); // Відкриваємо файл для читання
    std::string line;

    // Читаємо файл рядок за рядком
    while (std::getline(file, line))
    {
        std::istringstream iss(line); // Створюємо потік для розбиття рядка на частини
        std::string firstName, lastName, nickname, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime;
        int height;

        // Розбираємо рядок на поля злочинця
        std::getline(iss, firstName, ',');
        std::getline(iss, lastName, ',');
        std::getline(iss, nickname, ',');
        iss >> height;
        iss.ignore(); // Ігноруємо пробіл після height
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

        // Створюємо об'єкт злочинця та додаємо його до бази даних
        Criminal criminal(firstName, lastName, nickname, height, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime);
        criminalDatabase.push_back(criminal);
    }
    file.close(); // Закриваємо файл
}

// Збір інформації про злочинця від користувача
void Criminal::inputInfo()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаємо буфер
    Criminal newCriminal; // Створюємо новий об'єкт злочинця

    std::cout << "Enter criminal details:" << std::endl;

    // Отримуємо інформацію про злочинця від користувача
    std::cout << "First name: ";
    std::getline(std::cin, newCriminal.firstName);

    std::cout << "Last name: ";
    std::getline(std::cin, newCriminal.lastName);

    std::cout << "Nickname: ";
    std::getline(std::cin, newCriminal.nickname);

    std::cout << "Height: ";
    // Перевіряємо правильність введення height
    while (!(std::cin >> newCriminal.height))
    {
        std::cin.clear();  // Очищаємо стан помилки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Видаляємо залишки введення
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаємо буфер після числового вводу

    // Далі зчитуємо інші атрибути злочинця
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

    saveToFile(newCriminal); // Зберігаємо нового злочинця у файл
}

// Збереження злочинця у файл
void Criminal::saveToFile(const Criminal& criminal)
{
    std::ofstream file("criminals.txt", std::ios::app); // Відкриваємо файл для додавання
    if (file.is_open())
    {
        // Записуємо атрибути злочинця у файл через кому
        file << criminal.firstName << "," << criminal.lastName << "," << criminal.nickname << "," <<
            criminal.height << "," << criminal.eyeColor << "," << criminal.hairColor << "," << criminal.specialFeatures <<
            "," << criminal.nationality << "," << criminal.birthDate << "," << criminal.birthPlace << "," <<
            criminal.lastResidence << "," << criminal.lawKnowledge << "," << criminal.criminalProfession << "," <<
            criminal.lastCrime << std::endl;
        file.close(); // Закриваємо файл
        system("cls"); // Очищаємо екран
        std::cout << "\nNew criminal added successfully." << std::endl;
    }
    else
    {
        system("cls");
        std::cout << "\nUnable to open file." << std::endl; // Якщо файл не вдалося відкрити
    }
}

// Архівування злочинця у файл archive.txt
void Criminal::archiveCriminal(const Criminal& criminal)
{
    std::ofstream archiveFile("archive.txt", std::ios::app); // Відкриваємо файл архіву для додавання
    if (archiveFile.is_open())
    {
        // Записуємо атрибути злочинця у архівний файл
        archiveFile << criminal.firstName << "," << criminal.lastName << "," << criminal.nickname << "," <<
            criminal.height << "," << criminal.eyeColor << "," << criminal.hairColor << "," << criminal.specialFeatures <<
            "," << criminal.nationality << "," << criminal.birthDate << "," << criminal.birthPlace << "," <<
            criminal.lastResidence << "," << criminal.lawKnowledge << "," << criminal.criminalProfession << "," <<
            criminal.lastCrime << std::endl;
        archiveFile.close(); // Закриваємо файл
    }
    else
    {
        std::cerr << "Unable to open archive file." << std::endl; // Якщо файл не вдалося відкрити
    }
}

// Видалення злочинця з активного списку
void Criminal::removeFromActiveList(const std::string& lastName)
{
    std::ifstream inFile("criminals.txt"); // Відкриваємо файл для читання
    std::ofstream tempFile("temp.txt"); // Відкриваємо тимчасовий файл для запису

    if (inFile.is_open() && tempFile.is_open())
    {
        std::string line;
        // Читаємо файл рядок за рядком
        while (getline(inFile, line))
        {
            // Якщо рядок не містить прізвища злочинця, записуємо його у тимчасовий файл
            if (line.find(lastName) == std::string::npos)
                tempFile << line << std::endl;
        }
        inFile.close();
        tempFile.close();
        remove("criminals.txt"); // Видаляємо старий файл
        rename("temp.txt", "criminals.txt"); // Перейменовуємо тимчасовий файл на оригінальний
    }
}

// Пошук злочинця за ім'ям та прізвищем
Criminal Criminal::findCriminalByName(const std::string& firstName, std::string& lastName)
{
    std::ifstream inFile("criminals.txt"); // Відкриваємо файл для читання
    std::string line;
    Criminal foundCriminal;

    // Читаємо файл рядок за рядком
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string firstNameInFile, lastNameInFile, nickname, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime;
        int height;

        // Розбираємо рядок на атрибути
        std::getline(iss, firstNameInFile, ',');
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

        // Якщо прізвище та ім'я збігаються, повертаємо знайденого злочинця
        if (firstName == firstNameInFile && lastName == lastNameInFile)
        {
            foundCriminal = Criminal(firstNameInFile, lastNameInFile, nickname, height, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime);
            break;
        }
    }
    inFile.close(); // Закриваємо файл
    return foundCriminal; // Повертаємо знайденого злочинця
}

std::vector<Criminal> Criminal::criminalDatabase;

// Пошук злочинця по критеріям
void Criminal::searchByCriteria() const
{
    int option = 0;
    while (true) // Цикл, який повторюється, доки користувач не введе коректний варіант
    {
        try
        {
            // Виведення меню для вибору критерію пошуку
            std::cout << "Select search criterion:\n";
            std::cout << "1. First Name\n";
            std::cout << "2. Last Name\n";
            std::cout << "3. Nickname\n";
            std::cout << "4. Height\n";
            std::cout << "5. Hair color\n";
            std::cout << "6. Eye color\n";
            std::cout << "7. Special features\n";
            std::cout << "8. Nationality\n";
            std::cout << "9. Birth date\n";
            std::cout << "10. Birth place\n";
            std::cout << "11. Last residence\n";
            std::cout << "12. Knowledge of law\n";
            std::cout << "13. Criminal profession\n";
            std::cout << "14. Last crime\n";
            std::cout << "Enter option (1-14): ";

            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буферу після введення
            if (std::cin.fail()) // Перевірка, чи було введено число
            {
                throw std::invalid_argument("Input is not a number. Please enter a valid option."); // Кидання винятку у випадку нечислового вводу
            }
            if (option < 1 || option > 14) // Перевірка діапазону введеного значення
            {
                throw std::out_of_range("Invalid option selected."); // Кидання винятку, якщо вибір поза межами
            }
            break; // Вихід з циклу у випадку коректного вводу
        }
        catch (const std::invalid_argument& e)
        {
            // Очищення вводу та виведення повідомлення про помилку
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls"); // Очищення екрану
            std::cout << "Error: " << e.what() << std::endl << std::endl; // Виведення помилки
        }
        catch (const std::out_of_range& e)
        {
            system("cls"); // Очищення екрану
            std::cout << "Option out of range. Please enter a valid option between 1 and 14.\n\n"; // Повідомлення про неправильний вибір
        }
    }

    std::string criteria; // Змінна для зберігання критерію пошуку
    int height = 0; // Змінна для зберігання висоти, якщо критерій пошуку — висота
    switch (option) // Вибір критерію пошуку
    {
    case 1:
        system("cls"); // Очищення екрану
        std::cout << "Enter first name: ";
        std::getline(std::cin, criteria); // Введення імені
        break;
    case 2:
        system("cls");
        std::cout << "Enter last name: ";
        std::getline(std::cin, criteria); // Введення прізвища
        break;
    case 3:
        system("cls");
        std::cout << "Enter nickname: ";
        std::getline(std::cin, criteria); // Введення псевдоніма
        break;
    case 4:
        system("cls");
        std::cout << "Enter height: ";
        std::getline(std::cin, criteria); // Введення висоти
        try
        {
            height = std::stoi(criteria); // Перетворення введеного рядка у ціле число
        }
        catch (const std::invalid_argument& e) // Ловлення винятку, якщо введення не є числом
        {
            std::cout << "Invalid input. Please enter a valid number.\n"; // Повідомлення про помилку
            return;
        }
        catch (const std::out_of_range& e) // Ловлення винятку, якщо число занадто велике або мале
        {
            std::cout << "Number out of range. Please enter a valid number.\n"; // Повідомлення про помилку
            return;
        }
        break;
    case 5:
        system("cls");
        std::cout << "Enter hair color: ";
        std::getline(std::cin, criteria); // Введення кольору волосся
        break;
    case 6:
        system("cls");
        std::cout << "Enter eye color: ";
        std::getline(std::cin, criteria); // Введення кольору очей
        break;
    case 7:
        system("cls");
        std::cout << "Enter special features: ";
        std::getline(std::cin, criteria); // Введення особливих прикмет
        break;
    case 8:
        system("cls");
        std::cout << "Enter nationality: ";
        std::getline(std::cin, criteria); // Введення національності
        break;
    case 9:
        system("cls");
        std::cout << "Enter birth date: ";
        std::getline(std::cin, criteria); // Введення дати народження
        break;
    case 10:
        system("cls");
        std::cout << "Enter birth place: ";
        std::getline(std::cin, criteria); // Введення місця народження
        break;
    case 11:
        system("cls");
        std::cout << "Enter last residence: ";
        std::getline(std::cin, criteria); // Введення останнього місця проживання
        break;
    case 12:
        system("cls");
        std::cout << "Enter knowledge of law: ";
        std::getline(std::cin, criteria); // Введення знань у галузі права
        break;
    case 13:
        system("cls");
        std::cout << "Enter criminal profession: ";
        std::getline(std::cin, criteria); // Введення кримінальної професії
        break;
    case 14:
        system("cls");
        std::cout << "Enter last crime: ";
        std::getline(std::cin, criteria); // Введення останнього злочину
        break;
    default:
        system("cls"); // Очищення екрану у випадку некоректного вибору
        std::cout << "Invalid option selected.\n"; // Виведення повідомлення про помилку
        return;
    }

    // Завантаження злочинців із файлу
    loadCriminalsFromFile();
    std::vector<Criminal> results; // Вектор для зберігання результатів пошуку

    // Пошук злочинців за обраним критерієм
    for (const auto& criminal : criminalDatabase)
    {
        if ((option == 1 && criminal.firstName == criteria) ||
            (option == 2 && criminal.lastName == criteria) ||
            (option == 3 && criminal.nickname == criteria) ||
            (option == 4 && criminal.height == height) ||
            (option == 5 && criminal.hairColor == criteria) ||
            (option == 6 && criminal.eyeColor == criteria) ||
            (option == 7 && criminal.specialFeatures == criteria) ||
            (option == 8 && criminal.nationality == criteria) ||
            (option == 9 && criminal.birthDate == criteria) ||
            (option == 10 && criminal.birthPlace == criteria) ||
            (option == 11 && criminal.lastResidence == criteria) ||
            (option == 12 && criminal.lawKnowledge == criteria) ||
            (option == 13 && criminal.criminalProfession == criteria) ||
            (option == 14 && criminal.lastCrime == criteria)) {
            results.push_back(criminal); // Додавання знайденого злочинця до результатів
        }
    }

    if (results.empty()) // Якщо результатів немає
    {
        system("cls"); // Очищення екрану
        std::cout << "No criminals found with the given criteria.\n"; // Повідомлення, що злочинців не знайдено
    }
    else
    {
        system("cls"); // Очищення екрану
        std::cout << "Found " << results.size() << " criminals.\n\n"; // Виведення кількості знайдених злочинців
        for (const auto& criminal : results)
        {
            criminal.displayResults(); // Виведення результатів кожного знайденого злочинця
        }
    }
}

// Відображення результатів пошуку злочинця
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

// Перевіряє, чи злочинець є у вказаній групі
bool Criminal::isCriminalInGroup(const CriminalGroup& group, const Criminal& criminal)
{
    // Проходимо по всіх учасниках групи
    for (const auto& member : group.getMembers())
    {
        // Якщо ім'я та прізвище збігаються з даними злочинця, вважаємо, що він у групі
        if (member.getFirstName() == criminal.getFirstName() && member.getLastName() == criminal.getLastName())
        {
            return true; // Якщо знайдений злочинець у групі, повертаємо true
        }
    }
    return false; // Злочинця немає в групі
}

// Видаляє злочинця з архіву за його прізвищем
void Criminal::removeFromArchive(const std::string& lastName)
{
    std::ifstream archiveFile("archive.txt"); // Відкриваємо файл архіву для читання
    std::ofstream tempFile("temp.txt");       // Створюємо тимчасовий файл для запису
    std::string line;
    bool criminalFound = false; // Прапорець для відстеження, чи було знайдено злочинця

    // Перевіряємо, чи вдалося відкрити файли
    if (!archiveFile.is_open() || !tempFile.is_open())
    {
        std::cout << "Unable to open file." << std::endl;
        return; // Виходимо, якщо не вдалося відкрити файли
    }

    // Проходимо через всі рядки файлу архіву
    while (std::getline(archiveFile, line))
    {
        // Перевіряємо, чи прізвище збігається з тим, яке шукаємо
        if (line.find(lastName) != std::string::npos)
        {
            criminalFound = true; // Встановлюємо прапорець, що злочинець знайдений
            // Пропускаємо всі рядки, що стосуються цього злочинця
            while (std::getline(archiveFile, line) && !line.empty())
            {
                // Пропускаємо всі дані злочинця до наступного пустого рядка
            }
            continue; // Продовжуємо обробку інших записів
        }

        // Якщо це не дані злочинця, записуємо їх у тимчасовий файл
        tempFile << line << std::endl;
    }

    archiveFile.close(); // Закриваємо файл архіву
    tempFile.close();    // Закриваємо тимчасовий файл

    // Якщо злочинець був знайдений, оновлюємо архів
    if (criminalFound)
    {
        std::remove("archive.txt");        // Видаляємо старий файл архіву
        std::rename("temp.txt", "archive.txt"); // Перейменовуємо тимчасовий файл на архівний
        system("cls"); // Очищаємо екран (залежить від ОС, на Windows працюватиме, на Mac/Linux потрібно використовувати "clear")
        std::cout << "Criminal successfully removed from the archive." << std::endl;
    }
    else
    {
        std::remove("temp.txt"); // Видаляємо тимчасовий файл, якщо злочинця не знайшли
        std::cout << "Criminal not found in the archive." << std::endl;
    }
}

// Пошук злочинця в архіві за ім'ям та прізвищем
Criminal Criminal::findCriminalByNameInArchive(const std::string& firstName, std::string& lastName)
{
    std::ifstream inFile("archive.txt"); // Відкриваємо файл архіву для читання
    std::string line;
    Criminal foundCriminal; // Змінна для збереження знайденого злочинця

    // Читаємо кожен рядок файлу
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line); // Створюємо потік для обробки рядка
        std::string firstNameInFile, lastNameInFile, nickname, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime;
        int height;

        // Зчитуємо дані про злочинця з файлу
        std::getline(iss, firstNameInFile, ',');
        std::getline(iss, lastNameInFile, ',');
        std::getline(iss, nickname, ',');
        iss >> height;
        iss.ignore(); // Пропускаємо символ після height
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

        // Якщо ім'я та прізвище збігаються, створюємо знайденого злочинця
        if (lastNameInFile == lastName && firstNameInFile == firstName)
        {
            foundCriminal = Criminal(firstNameInFile, lastNameInFile, nickname, height, hairColor, eyeColor, specialFeatures, nationality, birthDate, birthPlace, lastResidence, lawKnowledge, criminalProfession, lastCrime);
            break; // При знаходженні злочинця припиняємо пошук
        }
    }
    return foundCriminal; // Повертаємо знайденого злочинця або порожній об'єкт, якщо не знайдено
}