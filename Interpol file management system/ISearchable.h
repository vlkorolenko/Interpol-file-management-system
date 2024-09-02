#pragma once
#include <string>

class ISearchable {
public:
    virtual ~ISearchable() = default;

    // Pure virtual methods
    virtual void searchByCriteria() const = 0;
    virtual void displayResults() const = 0;
};