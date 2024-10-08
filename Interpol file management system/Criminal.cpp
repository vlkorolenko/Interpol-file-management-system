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

    std::cout << "Введіть інформацію про злочинця:" << std::endl;

    // Отримуємо інформацію про злочинця від користувача
    std::cout << "Ім'я: ";
    std::getline(std::cin, newCriminal.firstName);

    std::cout << "Прізвище: ";
    std::getline(std::cin, newCriminal.lastName);

    std::cout << "Кличка: ";
    std::getline(std::cin, newCriminal.nickname);

    std::cout << "Зріст: ";
    // Перевіряємо правильність введення height
    while (!(std::cin >> newCriminal.height))
    {
        std::cin.clear();  // Очищаємо стан помилки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Видаляємо залишки введення
        std::cout << "Неправильне введення. Будь ласка, введіть число: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаємо буфер після числового вводу

    // Далі зчитуємо інші атрибути злочинця
    std::cout << "Колір очей: ";
    std::getline(std::cin, newCriminal.eyeColor);

    std::cout << "Колір волосся: ";
    std::getline(std::cin, newCriminal.hairColor);

    std::cout << "Особливі прикмети: ";
    std::getline(std::cin, newCriminal.specialFeatures);

    std::cout << "Національність: ";
    std::getline(std::cin, newCriminal.nationality);

    std::cout << "Дата народження (DD/MM/YYYY): ";
    std::getline(std::cin, newCriminal.birthDate);

    std::cout << "Місце народження: ";
    std::getline(std::cin, newCriminal.birthPlace);

    std::cout << "Останнє місце перебування: ";
    std::getline(std::cin, newCriminal.lastResidence);

    std::cout << "Знання законів: ";
    std::getline(std::cin, newCriminal.lawKnowledge);

    std::cout << "Кримінальна професія: ";
    std::getline(std::cin, newCriminal.criminalProfession);

    std::cout << "Останній злочин: ";
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
        std::cout << "\nЗлочинця успішно додано." << std::endl;
    }
    else
    {
        system("cls");
        std::cout << "\nНе вдалося відкрити файл." << std::endl; // Якщо файл не вдалося відкрити
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
        std::cerr << "Не вдалося відкрити файл." << std::endl; // Якщо файл не вдалося відкрити
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
            std::cout << "Виберіть критерій для пошуку:\n";
            std::cout << "1. Ім'я\n";
            std::cout << "2. Прізвище\n";
            std::cout << "3. Кличка\n";
            std::cout << "4. Зріст\n";
            std::cout << "5. Колір волосся\n";
            std::cout << "6. Колір очей\n";
            std::cout << "7. Особливі прикмети\n";
            std::cout << "8. Національність\n";
            std::cout << "9. Дата народження\n";
            std::cout << "10. Місце народження\n";
            std::cout << "11. Останнє місце перебування\n";
            std::cout << "12. Знання законів\n";
            std::cout << "13. Кримінальна професія\n";
            std::cout << "14. Останній злочин\n";
            std::cout << "Оберіть опцію (1-14): ";

            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищення буферу після введення
            if (std::cin.fail()) // Перевірка, чи було введено число
            {
                throw std::invalid_argument("Введене значення не є числом. Будь ласка, введіть дійсну опцію."); // Кидання винятку у випадку нечислового вводу
            }
            if (option < 1 || option > 14) // Перевірка діапазону введеного значення
            {
                throw std::out_of_range("Недійсний вибір."); // Кидання винятку, якщо вибір поза межами
            }
            break; // Вихід з циклу у випадку коректного вводу
        }
        catch (const std::invalid_argument& e)
        {
            // Очищення вводу та виведення повідомлення про помилку
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls"); // Очищення екрану
            std::cout << "Помилка: " << e.what() << std::endl << std::endl; // Виведення помилки
        }
        catch (const std::out_of_range& e)
        {
            system("cls"); // Очищення екрану
            std::cout << "Варіант поза межами. Будь ласка, введіть дійсний варіант від 1 до 14.\n\n"; // Повідомлення про неправильний вибір
        }
    }

    std::string criteria; // Змінна для зберігання критерію пошуку
    int height = 0; // Змінна для зберігання висоти, якщо критерій пошуку — висота
    switch (option) // Вибір критерію пошуку
    {
    case 1:
        system("cls"); // Очищення екрану
        std::cout << "Введіть ім'я: ";
        std::getline(std::cin, criteria); // Введення імені
        break;
    case 2:
        system("cls");
        std::cout << "Введіть прізвище: ";
        std::getline(std::cin, criteria); // Введення прізвища
        break;
    case 3:
        system("cls");
        std::cout << "Введіть кличку: ";
        std::getline(std::cin, criteria); // Введення псевдоніма
        break;
    case 4:
        system("cls");
        std::cout << "Введіть зріст: ";
        std::getline(std::cin, criteria); // Введення висоти
        try
        {
            height = std::stoi(criteria); // Перетворення введеного рядка у ціле число
        }
        catch (const std::invalid_argument& e) // Ловлення винятку, якщо введення не є числом
        {
            std::cout << "Неправильний вибір. Введіть правильне значення.\n"; // Повідомлення про помилку
            return;
        }
        catch (const std::out_of_range& e) // Ловлення винятку, якщо число занадто велике або мале
        {
            std::cout << "Введене число знаходиться поза межами припустимих. Спробуйте ще раз.\n"; // Повідомлення про помилку
            return;
        }
        break;
    case 5:
        system("cls");
        std::cout << "Введіть колір волосся: ";
        std::getline(std::cin, criteria); // Введення кольору волосся
        break;
    case 6:
        system("cls");
        std::cout << "Введіть колір очей: ";
        std::getline(std::cin, criteria); // Введення кольору очей
        break;
    case 7:
        system("cls");
        std::cout << "Введіть особливі прикмети: ";
        std::getline(std::cin, criteria); // Введення особливих прикмет
        break;
    case 8:
        system("cls");
        std::cout << "Введіть національність: ";
        std::getline(std::cin, criteria); // Введення національності
        break;
    case 9:
        system("cls");
        std::cout << "Введіть дату народження: ";
        std::getline(std::cin, criteria); // Введення дати народження
        break;
    case 10:
        system("cls");
        std::cout << "Введіть місце народження: ";
        std::getline(std::cin, criteria); // Введення місця народження
        break;
    case 11:
        system("cls");
        std::cout << "Введіть останнє місце перебування: ";
        std::getline(std::cin, criteria); // Введення останнього місця проживання
        break;
    case 12:
        system("cls");
        std::cout << "Введіть знання законів: ";
        std::getline(std::cin, criteria); // Введення знань у галузі права
        break;
    case 13:
        system("cls");
        std::cout << "Введіть кримінальну професію: ";
        std::getline(std::cin, criteria); // Введення кримінальної професії
        break;
    case 14:
        system("cls");
        std::cout << "Введіть останній злочин: ";
        std::getline(std::cin, criteria); // Введення останнього злочину
        break;
    default:
        system("cls"); // Очищення екрану у випадку некоректного вибору
        std::cout << "Вибрана недійсна опція.\n"; // Виведення повідомлення про помилку
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
        std::cout << "Жодного злочинця не знайдено по заданим критеріям.\n"; // Повідомлення, що злочинців не знайдено
    }
    else
    {
        system("cls"); // Очищення екрану
        std::cout << "Знайдено " << results.size() << " злочинця.\n\n"; // Виведення кількості знайдених злочинців
        for (const auto& criminal : results)
        {
            criminal.displayResults(); // Виведення результатів кожного знайденого злочинця
        }
    }
}

// Відображення результатів пошуку злочинця
void Criminal::displayResults() const
{
    std::cout << "Ім'я: " << firstName << std::endl;
    std::cout << "Прізвище: " << lastName << std::endl;
    std::cout << "Кличка: " << nickname << std::endl;
    std::cout << "Зріст: " << height << std::endl;
    std::cout << "Колір очей: " << eyeColor << std::endl;
    std::cout << "Колір волосся: " << hairColor << std::endl;
    std::cout << "Особливі прикмети: " << specialFeatures << std::endl;
    std::cout << "Націоналість: " << nationality << std::endl;
    std::cout << "Дата народження: " << birthDate << std::endl;
    std::cout << "Місце народження: " << birthPlace << std::endl;
    std::cout << "Останнє місце перебування: " << lastResidence << std::endl;
    std::cout << "Знання законів: " << lawKnowledge << std::endl;
    std::cout << "Кримінальна професія: " << criminalProfession << std::endl;
    std::cout << "Останній злочин: " << lastCrime << std::endl;
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
        std::cout << "Не вдалось знайти файл." << std::endl;
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
        std::cout << "Злочинець успішно видалений з архіву." << std::endl;
    }
    else
    {
        std::remove("temp.txt"); // Видаляємо тимчасовий файл, якщо злочинця не знайшли
        std::cout << "Злочинця не знайдено у архіві." << std::endl;
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