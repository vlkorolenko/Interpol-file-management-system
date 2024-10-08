#include "CriminalGroup.h"
#include "Criminal.h"

// ������� ���������� ����� ��������� � ����
void CriminalGroup::saveToFile(const CriminalGroup& criminalgroup)
{
    // ³�������� ���� � ����� ���������
    std::ofstream file("groups.txt", std::ios::app);
    // ����������, �� ������� ����
    if (file.is_open())
    {
        // �������� ��'� �����
        file << criminalgroup.name << std::endl;
        // ��� ������� ����� ����� �������� ��'� �� �������
        for (const auto& member : criminalgroup.members)
        {
            file << member.getFirstName() << "," << member.getLastName() << std::endl;
        }
        // ������ ��������� ��� ���� "---"
        file << "---" << std::endl;
        // ��������� ����
        file.close();
    }
    else
    {
        // ���� ���� �� ������� �������, �������� ����������� ��� �������
        std::cout << "\n�� ������� ������� ����." << std::endl;
    }
}

// ������� �������� ���������� ��� ����� ���������
void CriminalGroup::inputInfo()
{
    // ������� ������� ����, ��� �������� ������� � �����������
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    CriminalGroup newCriminalGroup;

    // �������� ����������� ������ ����� �����
    std::cout << "������ ����� ����������: ";
    std::getline(std::cin, newCriminalGroup.name);
    bool active = true;
    // ������� �������
    system("cls");
    do
    {
        // ��������� ����������� ������ ������ �����
        std::cout << "������ ������ ��������?\n";
        std::cout << "1. ���\n";
        std::cout << "2. ͳ\n";
        std::cout << "������ �����: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            // ���� ������ ���������, �������� ��'� �� �������
            system("cls");
            int id;
            std::cout << "������ ID ��������: ";
            std::cin >> id;

            // ������ �������� �� ��'�� � ��������
            Criminal criminal = criminal.findCriminalById(id);
            if (!criminal.getLastName().empty())
            {
                // ���� ��������, ������ ���� �� �����
                newCriminalGroup.addMember(criminal);
                system("cls");
                std::cout << "�������� ������ ������ �� ����������.\n\n";
            }
            else
            {
                // ���� �� ��������, �������� �������� �����������
                system("cls");
                std::cout << "�������� �� ��������.\n\n";
            }
        }
        else
        {
            // ���� ������ "ͳ", ���������� ��������� ����� �����
            system("cls");
            active = false;
        }
    } while (active);
    // �������� ����� � ����
    saveToFile(newCriminalGroup);
}

// ������� ��������� ����� �����
void CriminalGroup::addMember(const Criminal& criminal)
{
    // ������ �������� �� ������� ����� �����
    members.push_back(criminal);
}

// ������� ��������� ��� ���� ���������
void CriminalGroup::displayCriminalGroups()
{
    // ³�������� ���� ��� �������
    std::ifstream file("groups.txt");
    if (!file.is_open())
    {
        // ���� �� ������� ������� ����, �������� ����������� ��� �������
        std::cerr << "�� ������� ������� ����." << std::endl;
        return;
    }

    std::string line;
    // ������� ����� ����� �����
    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // ������� ����� �����
        CriminalGroup group;
        group.setGroupName(line);

        // �������� ����� �����
        std::cout << "����������: " << group.getGroupName() << std::endl;

        // ������� ����� ����� �� ���������� '---'
        while (std::getline(file, line) && line != "---")
        {
            std::istringstream iss(line);
            std::string firstName, lastName;
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');

            // ��������� ������ ����� �����
            Criminal member;
            member.setFirstName(firstName);
            member.setLastName(lastName);
            group.addMember(member);
        }

        // �������� ��� ����� �����
        for (const auto& member : group.getMembers())
        {
            std::cout << "  �������: " << member.getFirstName() << " " << member.getLastName() << std::endl;
        }

        std::cout << "-------------\n";
    }

    // ��������� ����
    file.close();
}

// ������� ������������ ���� ��������� �� �����
std::vector<CriminalGroup> CriminalGroup::loadFromFile()
{
    std::vector<CriminalGroup> groups;
    std::ifstream file("groups.txt");
    std::string line;
    CriminalGroup currentGroup;

    // ������� ����� �� �����
    while (std::getline(file, line))
    {
        if (line == "---")
        {
            // ���� ������� ���������, ������ ������� ����� �� �������
            if (!currentGroup.getGroupName().empty())
            {
                groups.push_back(currentGroup);
            }
            currentGroup = CriminalGroup(); // ��������� ���� �����
        }
        else if (currentGroup.getGroupName().empty())
        {
            // ������� ����� �����
            currentGroup.setGroupName(line);
        }
        else
        {
            // ������� ����� �����
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
    // ������ ������� ����� �� �������
    if (!currentGroup.getGroupName().empty())
    {
        groups.push_back(currentGroup);
    }
    return groups;
}

// ������� ��������� ����� � �����
void CriminalGroup::removeGroupFromFile(const std::string& groupName)
{
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;
    bool groupFound = false;

    if (!file.is_open() || !tempFile.is_open())
    {
        // ���� ���� �� ������� �������, �������� ����������� ��� �������
        std::cout << "�� ������� ������� ����." << std::endl;
        return;
    }

    // ������� ���� ����� �� ������
    while (std::getline(file, line))
    {
        // ���� ��������� �����, �������� ���������
        if (line == groupName)
        {
            inGroup = true;
            groupFound = true;
            continue;  // ���������� ����� �����
        }

        // ���� �� �������� �����, ���������� �� ����� �� ����������
        if (inGroup)
        {
            if (line.empty() || line == "---")
            {
                inGroup = false; // ��������� ������� �����
                continue;
            }
            continue;
        }

        // ���� �� � ����, �������� ����� � ���������� ����
        tempFile << line << std::endl;
    }

    // ��������� �����
    file.close();
    tempFile.close();

    // ��������� ����������� ���� � ������������� ����������
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");

    if (groupFound)
    {
        std::cout << "���������� '" << groupName << "' ���� ������ ��������." << std::endl;
    }
    else
    {
        std::cout << "���������� '" << groupName << "' �� ��������." << std::endl;
    }
}

// ������� ��������� ����� �����
void CriminalGroup::removeMember(const std::string& groupName, const std::string& memberFirstName, const std::string& memberLastName)
{
    // ³�������� ���� "groups.txt" ��� ������� �� "temp.txt" ��� ����������� ������
    std::ifstream file("groups.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    bool inGroup = false;  // ���������, ���� ������, �� �� �������� �����

    // ����������, �� ������� ������� ������ �����
    if (!file.is_open() || !tempFile.is_open())
    {
        std::cout << "�� ������� ������� ����." << std::endl;
        return;
    }

    // ������� ����� ��'� ����� ����� ��� ������
    std::string fullMemberName = memberFirstName + "," + memberLastName;

    // ������ ���� ����� �� ������
    while (std::getline(file, line))
    {
        // ���� ��������� ����� �����, �������� ������� �� �����
        if (line == groupName)
        {
            inGroup = true;  // ������������ ���������, �� �� �������� �����
            tempFile << line << std::endl;  // �������� ����� ����� � ���������� ����
            continue;  // ���������� �� ���������� �����
        }

        // ���� ��������� ������� ����� ��� ��������� "---", �������� � ������� ���� �����
        if (inGroup && (line.empty() || line == "---"))
        {
            inGroup = false;  // ������������ ���������, �� �� ������ � �����
            tempFile << line << std::endl;  // �������� ��������� � ���������� ����
            continue;  // ���������� �� ���������� �����
        }

        // ���� �� �������� �����, ���������� ������� ����� �����
        if (inGroup)
        {
            // ���� �� �� ��� ����, ����� ����� ��������, ������ �������� �����
            if (line != fullMemberName)
            {
                tempFile << line << std::endl;
            }
        }
        else
        {
            // ���� �� �� � ����, �������� �� �����, �� �
            tempFile << line << std::endl;
        }
    }

    // ��������� ������ �����
    file.close();
    tempFile.close();

    // ��������� ����������� ���� "groups.txt" �� ������������� ���������� ���� �� "groups.txt"
    std::remove("groups.txt");
    std::rename("temp.txt", "groups.txt");

    // ������� ����� � �����������, �� ������ ��������� ����������
    system("cls");
    std::cout << "�������� ������ ��������." << std::endl;
}