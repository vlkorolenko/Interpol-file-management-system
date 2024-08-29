#include "Criminal.h"

void Criminal::saveToFile(const Criminal criminal)
{
    std::ofstream file("criminals.txt", std::ios::app);
    if (file.is_open())
    {
        //file << criminal. << "," << film.year << "," << film.genre << "," << film.director << "," << film.views << std::endl;
        file.close();
        std::cout << "\nNew criminal added successfully." << std::endl;
    }
    else
    {
        std::cout << "\nUnable to open file." << std::endl;
    }
}
