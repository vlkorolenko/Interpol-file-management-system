#pragma once
#include <iostream>
#include <string>
#include <vector>

class Criminal;

class CriminalGroup
{
private:
	std::string name;
	std::vector<Criminal> members;
public:
    CriminalGroup() = default;

    // ����������� �� �����������
    CriminalGroup(const std::string& groupName, const std::vector<Criminal>& groupMembers)
        : name(groupName), members(groupMembers) {}

    // ����������� ���������
    CriminalGroup(const CriminalGroup& other)
        : name(other.name), members(other.members)
    {
    }

    // �������� ���������
    CriminalGroup& operator=(const CriminalGroup& other)
    {
        if (this != &other)
        {
            name = other.name;
            members = other.members;
        }
        return *this;
    }

    // ����������� ����������
    CriminalGroup(CriminalGroup&& other) noexcept
        : name(std::move(other.name)), members(std::move(other.members))
    {
    }

    // �������� ����������
    CriminalGroup& operator=(CriminalGroup&& other) noexcept
    {
        if (this != &other)
        {
            name = std::move(other.name);
            members = std::move(other.members);
        }
        return *this;
    }

    // ����������
    ~CriminalGroup(){}

	void saveToFile(const CriminalGroup& criminalgroup);
	void inputInfo();
	void addMember(const Criminal& criminal);
	std::string getGroupName() const { return name; }
	const std::vector<Criminal>& getMembers() const { return members; }
	void setGroupName(const std::string& groupName) { name = groupName; }
	void displayCriminalGroups();
	static std::vector<CriminalGroup> loadFromFile();
	void removeGroupFromFile(const std::string& groupName);
	void removeMember(const std::string& groupName, const std::string& memberFirstName, const std::string& memberLastName);
};