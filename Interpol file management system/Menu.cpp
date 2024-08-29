#include "Menu.h"

void addCriminal(Criminal& criminal) {
    criminal.inputInfo();
}

int Menu::displayMenu()
{
    bool menuIsOpen = true;

    while (menuIsOpen)
    {
        try
        {
            std::cout << "Menu:\n";
            std::cout << "1. Add New Criminal\n";
            std::cout << "2. Update Criminal Data\n";;
            std::cout << "3. Archive Criminal\n";
            std::cout << "4. Delete Criminal After Death\n";
            std::cout << "5. View Criminal Information\n";
            std::cout << "6. Search Criminals by Criteria\n";
            std::cout << "7. View Criminal Organizations List\n";
            std::cout << "8. Add New Organization\n";
            std::cout << "9. Update Organization Data\n";
            std::cout << "10. View Case History\n";
            std::cout << "11. [Exit]\n";
            std::cout << "Choose option: ";

            int option;
            std::cin >> option;

            // Перевірка на коректність введення
            if (std::cin.fail() || option > 11 || option <= 0) {
                std::cin.clear(); // очищаємо прапор помилки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // відкидаємо некоректний ввід
                throw std::invalid_argument("Incorrect entry. Please try again.");
            }

            switch (option)
            {
            case 1:
                system("cls");
                {
                    Criminal criminal; // Create a local object
                    addCriminal(criminal); // Call the function to handle input
                }
                break;
            case 2:
                system("cls");
                cout << "Soon\n";
                break;
            case 3:
                system("cls");
                cout << "Soon\n";
                break;
            case 4:
                system("cls");
                cout << "Soon\n";
                break;
            case 5:
                system("cls");
                cout << "Soon\n";
                break;
            case 6:
                system("cls");
                cout << "Soon\n";
                break;
            case 7:
                system("cls");
                cout << "Soon\n";
                break;
            case 8:
                system("cls");
                cout << "Soon\n";
                break;
            case 9:
                system("cls");
                cout << "Soon\n";
                break;
            case 10:
                system("cls");
                cout << "Soon\n";
                break;
            case 11:
                cout << "Exiting...\n";
                return 0;

            }
            int variant = 0;
            do {
                cout << "\n1. Back to menu";
                cout << "\n2. [Exit]\n";
                cout << "Choose option: ";
                cin >> variant;
                while (variant < 1 || variant > 2)
                {
                    std::cout << "Incorrect option. \nTry again: ";
                    std::cin >> variant;
                }
                if (variant == 2)
                {
                    cout << "Exiting...\n";
                    return 0;
                }
                else
                {
                    system("cls");
                    break;
                }
            } while (variant != 1);
        }
        catch (exception ex)
        {
            std::cout << "Error: " << ex.what() << std::endl;
            std::cout << "Return to menu..." << std::endl;
            system("pause");
            system("cls");
        }

    }
}