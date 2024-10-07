#include "CriminalGroup.h"
#include "Criminal.h"

// Функція збереження групи злочинців у файл
void CriminalGroup::saveToFile(const CriminalGroup& criminalgroup)
{
    // Відкриваємо файл у режимі додавання
    std::ofstream file("groups.txt", std::ios::app);
    // Перевіряємо, чи відкрито файл
    if (file.is_open())
    {
        // Записуємо ім'я групи
        file << criminalgroup.name << std::endl;
        // Для кожного члена групи записуємо ім'я та прізвище
        for (const auto& member : criminalgroup.members)
        {
            file << member.getFirstName() << "," << member.getLastName() << std::endl;
        }
        // Додаємо розділювач для груп "---"
        file << "---" << std::endl;
        // Закриваємо файл
        file.close();
    }
    else
    {
        // Якщо файл не вдалося відкрити, виводимо повідомлення про помилку
        std::cout << "\nUnable to open file." << std::endl;
    }
}

// Функція введення інформації про групу злочинців
void CriminalGroup::inputInfo()
{
    // Очищуємо вхідний потік, щоб уникнути проблем зі зчитуванням
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    CriminalGroup newCriminalGroup;

    // Запитуємо користувача ввести назву групи
    std::cout << "Enter criminal group name: ";
    std::getline(std::cin, newCriminalGroup.name);
    bool active = true;
    // Очищуємо консоль
    system("cls");
    do
    {
        // Пропонуємо користувачу додати нового члена
        std::cout << "Add member?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            // Якщо обрано додавання, запитуємо ім'я та прізвище
            system("cls");
            std::string firstName, lastName;

            std::cout << "Enter the FIRST name of the criminal to add: ";
            std::cin >> firstName;
            std::cout << "Enter the LAST name of the criminal to add: ";
            std::cin >> lastName;

            // Шукаємо злочинця за ім'ям і прізвищем
            Criminal criminal = criminal.findCriminalByName(firstName, lastName);
            if (!criminal.getLastName().empty())
            {
                // Якщо знайдено, додаємо його до групи
                newCriminalGroup.addMember(criminal);
                system("cls");
                std::cout << "Criminal added successfully.\n\n";
            }
            else
            {
                // Якщо не знайдено, виводимо відповідне повідомлення
                system("cls");
                std::cout << "Criminal not found.\n\n";
            }
        }
        else
        {
            // Якщо обрано "Ні", припиняємо додавання нових членів
            system("cls");
            active = false;
        }
    } while (active);
    // Зберігаємо групу у файл
    saveToFile(newCriminalGroup);
}

// Функція додавання члена групи
void CriminalGroup::addMember(const Criminal& criminal)
{
    // Додаємо злочинця до вектора членів групи
    members.push_back(criminal);
}

// Функція виведення всіх груп злочинців
void CriminalGroup::displayCriminalGroups()
{
    // Відкриваємо файл для читання
    std::ifstream file("groups.txt");
    if (!file.is_open())
    {
        // Якщо не вдалося відкрити файл, виводимо повідомлення про помилку
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    std::string line;
    // Зчитуємо кожен рядок файлу
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // Зчитуємо назву групи
        CriminalGroup group;
        group.setGroupName(line);

        // Виводимо назву групи
        std::cout << "Group: " << group.getGroupName() << std::endl;

        // Зчитуємо членів групи до розділювача '---'
        while (std::getline(file, line) && line != "---")
        {
            std::istringstream iss(line);
            std::string firstName, lastName;
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');

            // Створюємо нового члена групи
            Criminal member;
            member.setFirstName(firstName);
            member.setLastName(lastName);
            group.addMember(member);
        }

        // Виводимо всіх членів групи
        for (const auto& member : group.getMembers())
        {
            std::cout << "  Member: " << member.getFirstName() << " " << member.getLastName() << std::endl;
        }

        std::cout << "-------------\n";
    }

    // Закриваємо файл
    file.close();
}

// Функція завантаження груп злочинців із файлу
std::vector<CriminalGroup> CriminalGroup::loadFromFile()
{
    std::vector<CriminalGroup> groups;
    std::ifstream file("groups.txt");
    std::string line;
    CriminalGroup currentGroup;

    // Читання даних із файлу
    while (std::getline(file, line))
    {
        if (line == "---")
        {
            // Якщо знайшли розділювач, додаємо поточну групу до вектора
            if (!currentGroup.getGroupName().empty())
            {
                groups.push_back(currentGroup);
            }
            currentGroup = CriminalGroup(); // Створюємо нову групу
        }
        else if (currentGroup.getGroupName().empty())
        {
            // Зчитуємо назву групи
            currentGroup.setGroupName(line);
        }
        else
        {
            // Зчитуємо члена групи
            std::istringstream iss(line);
            std::string firstName, lastName;
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName);
            Criminal newCriminal;
            newCriminal.setFirstName(firstName);
            newCriminal.setLastName(lastName);
            currentGroup.addMember(newCriminal);
        }
    }
    // Додаємо останню групу до вектора
    if (!currentGroup.getGroupName().empty())
    {
        groups.push_back(currentGroup);
    }
    return groups;
}

// Функція видалення групи з файлу
void CriminalGroup::removeGroupFromFile(const std::string& groupName)
{
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;
    bool groupFound = false;

    if (!file.is_open() || !tempFile.is_open())
    {
        // Якщо файл не вдалося відкрити, виводимо повідомлення про помилку
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    // Зчитуємо файл рядок за рядком
    while (std::getline(file, line))
    {
        // Якщо знаходимо групу, починаємо видалення
        if (line == groupName)
        {
            inGroup = true;
            groupFound = true;
            continue;  // Пропускаємо назву групи
        }

        // Якщо ми всередині групи, пропускаємо всі рядки до розділювача
        if (inGroup)
        {
            if (line.empty() || line == "---")
            {
                inGroup = false; // Завершуємо обробку групи
                continue;
            }
            continue;
        }

        // Якщо не в групі, записуємо рядки у тимчасовий файл
        tempFile << line << std::endl;
    }

    // Закриваємо файли
    file.close();
    tempFile.close();

    // Видаляємо оригінальний файл і перейменовуємо тимчасовий
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");

    if (groupFound)
    {
        std::cout << "Group '" << groupName << "' has been removed successfully." << std::endl;
    }
    else
    {
        std::cout << "Group '" << groupName << "' not found." << std::endl;
    }
}

// Функція видалення члена групи
void CriminalGroup::removeMember(const std::string& groupName, const std::string& memberFirstName, const std::string& memberLastName)
{
    // Відкриваємо файл "groups.txt" для читання та "temp.txt" для тимчасового запису
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;  // Прапорець, який показує, чи ми всередині групи

    // Перевіряємо, чи вдалося відкрити обидва файли
    if (!file.is_open() || !tempFile.is_open())
    {
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    // Формуємо повне ім'я члена групи для пошуку
    std::string fullMemberName = memberFirstName + "," + memberLastName;

    // Читаємо файл рядок за рядком
    while (std::getline(file, line))
    {
        // Якщо знаходимо назву групи, починаємо обробку її членів
        if (line == groupName)
        {
            inGroup = true;  // Встановлюємо прапорець, що ми всередині групи
            tempFile << line << std::endl;  // Записуємо назву групи в тимчасовий файл
            continue;  // Переходимо до наступного рядка
        }

        // Якщо знаходимо порожній рядок або розділювач "---", виходимо з обробки цієї групи
        if (inGroup && (line.empty() || line == "---"))
        {
            inGroup = false;  // Встановлюємо прапорець, що ми вийшли з групи
            tempFile << line << std::endl;  // Записуємо розділювач в тимчасовий файл
            continue;  // Переходимо до наступного рядка
        }

        // Якщо ми всередині групи, перевіряємо кожного члена групи
        if (inGroup)
        {
            // Якщо це не той член, якого треба видалити, просто записуємо рядок
            if (line != fullMemberName)
            {
                tempFile << line << std::endl;
            }
        }
        else
        {
            // Якщо ми не в групі, записуємо всі рядки, як є
            tempFile << line << std::endl;
        }
    }

    // Закриваємо обидва файли
    file.close();
    tempFile.close();

    // Видаляємо оригінальний файл "groups.txt" та перейменовуємо тимчасовий файл на "groups.txt"
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");

    // Очищуємо екран і повідомляємо, що процес видалення завершений
    system("cls");
    std::cout << "Member removal process completed." << std::endl;
}