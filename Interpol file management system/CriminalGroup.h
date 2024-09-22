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
	CriminalGroup() {}
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