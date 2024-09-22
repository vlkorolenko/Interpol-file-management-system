#include "CriminalGroup.h"
#include "Criminal.h"

void CriminalGroup::saveToFile(const CriminalGroup& criminalgroup)
{
    std::ofstream file("groups.txt", std::ios::app);
    if (file.is_open())
    {
        file << criminalgroup.name << std::endl;
        for (const auto& member : criminalgroup.members)
        {
            file << member.getFirstName() << "," << member.getLastName() << std::endl;
        }
        file << "---" << std::endl; // Розділювач для груп
        file.close();
    }
    else
    {
        std::cout << "\nUnable to open file." << std::endl;
    }
}

void CriminalGroup::inputInfo()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    CriminalGroup newCriminalGroup;

    std::cout << "Enter criminal group name: ";
    std::getline(std::cin, newCriminalGroup.name);
    bool active = true;
    system("cls");
    do {
        std::cout << "Add member?\n";
        std::cout << "1. Yes\n";
        std::cout << "2. No\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            system("cls");
            std::string firstName, lastName;
            
            std::cout << "Enter the FIRST name of the criminal to add: ";
            std::cin >> firstName;
            std::cout << "Enter the LAST name of the criminal to add: ";
            std::cin >> lastName;

            Criminal criminal = criminal.findCriminalByName(firstName, lastName); // Find the criminal by last name
            if (!criminal.getLastName().empty()) { // Check if the criminal was found
                newCriminalGroup.addMember(criminal);
                system("cls");
                std::cout << "Criminal added successfully.\n\n";
            }
            else
            {
                system("cls");
                std::cout << "Criminal not found.\n\n";
            }
        }
        else
        {
            system("cls");
            active = false;
        }
    } while (active);
     saveToFile(newCriminalGroup);
}

void CriminalGroup::addMember(const Criminal& criminal)
{
    members.push_back(criminal);
}

void CriminalGroup::displayCriminalGroups()
{
    std::ifstream file("groups.txt");
    if (!file.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        // Read the group name
        CriminalGroup group;
        group.setGroupName(line);

        std::cout << "Group: " << group.getGroupName() << std::endl;

        // Read members until the delimiter '---'
        while (std::getline(file, line) && line != "---") {
            std::istringstream iss(line);
            std::string firstName, lastName;
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');

            Criminal member;
            member.setFirstName(firstName);
            member.setLastName(lastName);
            group.addMember(member);
        }

        // Print members
        for (const auto& member : group.getMembers()) {
            std::cout << "  Member: " << member.getFirstName() << " " << member.getLastName() << std::endl;
        }

        std::cout << "-------------\n";
    }

    file.close();
}

std::vector<CriminalGroup> CriminalGroup::loadFromFile()
{
    std::vector<CriminalGroup> groups;
    std::ifstream file("groups.txt");
    std::string line;
    CriminalGroup currentGroup;

    while (std::getline(file, line)) {
        if (line == "---") {
            if (!currentGroup.getGroupName().empty()) {
                groups.push_back(currentGroup);
            }
            currentGroup = CriminalGroup(); // Create new group
        }
        else if (currentGroup.getGroupName().empty()) {
            currentGroup.setGroupName(line);
        }
        else {
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
    if (!currentGroup.getGroupName().empty()) {
        groups.push_back(currentGroup); // Push last group
    }
    return groups;
}

void CriminalGroup::removeGroupFromFile(const std::string& groupName)
{
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        // Якщо знаходимо назву групи, починаємо видаляти всі наступні рядки
        if (line == groupName) {
            inGroup = true;
            continue;  // Пропускаємо цей рядок (назва групи)
        }

        // Якщо знайшли порожній рядок або кінець списку членів групи
        if (inGroup && line.empty()) {
            inGroup = false;
            continue;  // Пропускаємо порожній рядок
        }

        // Якщо не в середині видаляємої групи, записуємо рядки у тимчасовий файл
        if (!inGroup) {
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    // Видаляємо старий файл та перейменовуємо тимчасовий файл
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");
}

void CriminalGroup::removeMember(const std::string& groupName, const std::string& memberFirstName, const std::string& memberLastName)
{
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;

    if (!file.is_open() || !tempFile.is_open()) {
        std::cout << "Unable to open file." << std::endl;
        return;
    }

    std::string fullMemberName = memberFirstName + "," + memberLastName;

    while (std::getline(file, line)) {
        // Якщо знайшли групу, починаємо обробку її членів
        if (line == groupName) {
            inGroup = true;
            tempFile << line << std::endl; // Записуємо назву групи
            continue;
        }

        // Якщо знайшли кінець списку членів (порожній рядок або "---"), виходимо з режиму обробки групи
        if (inGroup && (line.empty() || line == "---")) {
            inGroup = false;
            tempFile << line << std::endl; // Записуємо порожній рядок або розділювач
            continue;
        }

        // Якщо ми в групі, перевіряємо кожного члена
        if (inGroup) {
            if (line != fullMemberName) {
                tempFile << line << std::endl; // Якщо це не той член, просто записуємо рядок
            }
        }
        else {
            // Якщо не в групі, просто записуємо всі рядки
            tempFile << line << std::endl;
        }
    }

    file.close();
    tempFile.close();

    // Замінюємо оригінальний файл на новий
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");
    system("cls");
    std::cout << "Member removal process completed." << std::endl;
}