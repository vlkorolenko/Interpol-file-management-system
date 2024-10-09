#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"

// Метод для додання нового злочинця у базу
void addCriminal(Criminal* criminal)
{
    criminal->inputInfo();  // Викликаємо метод для введення інформації про нового злочинця
}

// Метод для додання нової злочинної організації
void addCriminalGroup(CriminalGroup& criminalGroup)
{
    criminalGroup.inputInfo();  // Викликаємо метод для введення інформації про нову злочинну групу
}

// Виведення меню у консоль
int Menu::displayMenu()
{
    bool menuIsOpen = true;  // Змінна для збереження стану відкритого меню

    while (menuIsOpen)  // Цикл для відображення меню поки воно відкрите
    {
        try
        {
            std::cout << "Меню:\n";  // Виведення опцій меню
            std::cout << "1. Додати злочинця\n";
            std::cout << "2. Список злочинців\n";;
            std::cout << "3. Архівувати злочинця\n";
            std::cout << "4. Видалити злочинця після смерті\n";
            std::cout << "5. Пошук злочинця за критерією\n";
            std::cout << "6. Відсортувати злочинців\n";
            std::cout << "7. Додати нову організацію\n";
            std::cout << "8. Переглянути список злочинних організацій\n";
            std::cout << "9. Оновити інформацію про організацію\n";
            std::cout << "10. Архів\n";
            std::cout << "11. Посібник користувача\n";
            std::cout << "12. [Вийти]\n";
            std::cout << "Оберіть опцію: ";

            int option;
            std::cin >> option;  // Введення вибору користувача

            // Перевірка на коректність введення
            if (std::cin.fail() || option > 12 || option <= 0)
            {
                std::cin.clear();  // Очищуємо прапорець помилки вводу
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Пропускаємо некоректні символи
                throw std::invalid_argument("Невірний ввід. Спробуйте ще раз.");  // Генеруємо виняток при некоректному введенні
            }

            switch (option)  // Обробка введеного користувачем варіанту
            {
            case 1:
                system("cls");  // Очищуємо екран
                {
                    Criminal* newCriminal = new Criminal();  // Створюємо новий об'єкт злочинця
                    addCriminal(newCriminal);  // Викликаємо функцію для введення інформації про злочинця
                    delete newCriminal;  // Очищаємо пам'ять після використання об'єкта
                }
                break;
            case 2:
                system("cls");  // Очищуємо екран
                displayCriminals();  // Викликаємо функцію для відображення списку злочинців
                break;
            case 3:
                system("cls");  // Очищуємо екран
                {
                    int id;
                    std::cout << "Введіть ID злочинця: ";  // Запитуємо прізвище
                    std::cin >> id;

                    Criminal criminal = criminal.findCriminalById(id);  // Пошук злочинця за ім'ям
                    if (!criminal.getLastName().empty())  // Якщо злочинець знайдений
                    {
                        system("cls");
                        criminal.archiveCriminal(criminal);  // Архівуємо злочинця
                        criminal.removeFromActiveList(id);  // Видаляємо з активного списку
                        std::cout << "Злочинець успішно заархівований.\n";  // Виводимо повідомлення про успіх
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Злочинця не знайдено.\n";  // Повідомлення, якщо злочинця не знайдено
                    }
                }
                break;
            case 4:
                system("cls");
                {
                    int id;
                    std::cout << "Введіть ID злочинця: ";  // Запитуємо прізвище
                    std::cin >> id;

                    Criminal criminal = criminal.findCriminalByIdInArchive(id);  // Пошук злочинця в архіві
                    if (!criminal.getLastName().empty())  // Якщо знайдено
                    {
                        system("cls");
                        criminal.removeFromArchive(id);  // Видаляємо з архіву
                    }
                    else
                    {
                        system("cls");
                        std::cout << "Злочинця не знайдено.\n";  // Повідомлення, якщо не знайдено
                    }
                }
                break;
            case 5:
                system("cls");  // Очищуємо екран
                {
                    Criminal criminal;
                    criminal.searchByCriteria();  // Викликаємо пошук за критеріями
                }
                break;
            case 6:
                system("cls");  // Очищуємо екран
                displaySortMenu();
                break;
            case 7:
                system("cls");  // Очищуємо екран
                {
                    CriminalGroup criminalGroup;
                    addCriminalGroup(criminalGroup);  // Викликаємо функцію для додавання нової організації
                }
                break;
            case 8:
                system("cls");  // Очищуємо екран
                {
                    CriminalGroup criminalGroup;
                    criminalGroup.displayCriminalGroups();  // Виведення списку організацій
                }
                break;
            case 9:
                system("cls");  // Очищуємо екран
                displayCriminalGroups();  // Відображення даних про організації
                break;
                break;
            case 10:
                system("cls");  // Очищуємо екран
                displayArchive();  // Відображення архіву
                break;
            case 11:
                displayUserGuide();
                break;
            case 12:
                cout << "Вихід...\n";  // Повідомлення про вихід
                return 0;  // Завершення програми
            }

            int variant = 0;  // Змінна для вибору повернення до меню чи виходу

            while (variant != 1)
            {
                try
                {
                    std::cout << "1. Повернутись у меню";  // Виводимо опції повернення до меню
                    std::cout << "\n2. [Вихід]\n";
                    std::cout << "Оберіть опцію: ";
                    std::cin >> variant;  // Введення вибору

                    // Перевіряємо, чи ввів користувач рядок замість числа
                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Введене значення не є числом. Будь ласка, введіть дійсну опцію.");  // Виняток при некоректному введенні
                    }

                    // Перевірка на діапазон варіантів
                    if (variant < 1 || variant > 2)
                    {
                        throw std::out_of_range("Недійсна опція. Будь ласка, введіть 1 або 2.");  // Виняток при некоректному варіанті
                    }

                    // Обробка вибору користувача
                    if (variant == 2)
                    {
                        std::cout << "Вихід...\n";  // Повідомлення про вихід
                        return 0;  // Завершення програми
                    }
                    else
                    {
                        system("cls");  // Очищення екрану для повернення до меню
                        break;
                    }
                }
                catch (const std::invalid_argument& e)
                {
                    // Очищення вводу та виведення повідомлення про помилку
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    system("cls");
                    std::cout << "Помилка: " << e.what() << std::endl << std::endl;  // Виведення помилки
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << "Помилка: " << e.what() << std::endl << std::endl;  // Виведення помилки
                }
            }
        }
        catch (exception ex)  // Перехоплення загальних винятків
        {
            std::cout << "Помилка: " << ex.what() << std::endl;  // Виведення помилки
            system("pause");  // Пауза перед очищенням екрану
            system("cls");  // Очищення екрану після помилки
        }

    }
}

// Метод для відображення інформації про злочинців із файлу "criminals.txt"
void Menu::displayCriminals()
{
    std::ifstream file("criminals.txt"); // Відкриття файлу "criminals.txt" для читання

    try
    {
        std::string line;
        // Читання кожного рядка файлу, поки є рядки для обробки
        while (std::getline(file, line))
        {
            std::istringstream iss(line); // Створення потоку для парсингу рядка
            int id;
            std::string firstName;
            std::string lastName;
            std::string nickname;
            int height;
            std::string hairColor;
            std::string eyeColor;
            std::string specialFeatures;
            std::string nationality;
            std::string birthPlace;
            std::string birthDate;
            std::string lastResidence;
            std::string lawKnowledge;
            std::string criminalProfession;
            std::string lastCrime;

            // Розбір полів з рядка CSV (розділеного комами)
            iss >> id;
            iss.ignore(); // Пропуск символу після числового значення
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');
            std::getline(iss, nickname, ',');
            iss >> height;
            iss.ignore(); // Пропуск символу після числового значення
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

            // Виведення даних про злочинця
            std::cout << "ID: " << id << std::endl;
            std::cout << "Ім'я: " << firstName << std::endl;
            std::cout << "Прізвище: " << lastName << std::endl;
            std::cout << "Кличка: " << nickname << std::endl;
            std::cout << "Зріст: " << height << std::endl;
            std::cout << "Колір очей: " << eyeColor << std::endl;
            std::cout << "Колір волосся: " << hairColor << std::endl;
            std::cout << "Особливі прикмети: " << specialFeatures << std::endl;
            std::cout << "Національність: " << nationality << std::endl;
            std::cout << "Дата народження: " << birthDate << std::endl;
            std::cout << "Місце народження: " << birthPlace << std::endl;
            std::cout << "Останнє місце перебування: " << lastResidence << std::endl;
            std::cout << "Знання законів: " << lawKnowledge << std::endl;
            std::cout << "Кримінальна професія: " << criminalProfession << std::endl;
            std::cout << "Останній злочин: " << lastCrime << std::endl;
            std::cout << "-------------\n";
        }
        file.close(); // Закриття файлу після обробки
    }
    catch (const std::runtime_error& e)
    {
        // Обробка можливих помилок під час читання файлу
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Метод для відображення архівованих злочинців із файлу "archive.txt"
void Menu::displayArchive()
{
    std::ifstream file("archive.txt");
    try
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            int id;
            std::string firstName;
            std::string lastName;
            std::string nickname;
            int height;
            std::string hairColor;
            std::string eyeColor;
            std::string specialFeatures;
            std::string nationality;
            std::string birthPlace;
            std::string birthDate;
            std::string lastResidence;
            std::string lawKnowledge;
            std::string criminalProfession;
            std::string lastCrime;

            // Парсинг рядка CSV (розділеного комами)
            iss >> id;
            iss.ignore();
            std::getline(iss, firstName, ',');
            std::getline(iss, lastName, ',');
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

            std::cout << "ID: " << id << std::endl;
            std::cout << "Ім'я: " << firstName << std::endl;
            std::cout << "Прізвище: " << lastName << std::endl;
            std::cout << "Кличка: " << nickname << std::endl;
            std::cout << "Зріст: " << height << std::endl;
            std::cout << "Колір очей: " << eyeColor << std::endl;
            std::cout << "Колір волосся: " << hairColor << std::endl;
            std::cout << "Особливі прикмети: " << specialFeatures << std::endl;
            std::cout << "Національність: " << nationality << std::endl;
            std::cout << "Дата народження: " << birthDate << std::endl;
            std::cout << "Місце народження: " << birthPlace << std::endl;
            std::cout << "Останнє місце перебування: " << lastResidence << std::endl;
            std::cout << "Знання законів: " << lawKnowledge << std::endl;
            std::cout << "Кримінальна професія: " << criminalProfession << std::endl;
            std::cout << "Останній злочин: " << lastCrime << std::endl;
            std::cout << "-------------\n";
        }
        file.close();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Помилка: " << e.what() << std::endl;
    }
}

// Метод для виведення меню зі злочинними організаціями
void Menu::displayCriminalGroups()
{
    // Завантаження груп злочинців із файлу
    std::vector<CriminalGroup> groups = CriminalGroup::loadFromFile();
    if (groups.empty())
    {
        // Якщо груп немає, повідомляємо користувача
        std::cout << "Кримінальних організацій не знайдено." << std::endl;
        return;
    }

    // Виведення списку груп
    std::cout << "Доступні кримінальні організації:" << std::endl;
    for (size_t i = 0; i < groups.size(); ++i)
    {
        // Виводимо кожну групу по порядковому номеру
        std::cout << i + 1 << ". " << groups[i].getGroupName() << std::endl;
    }

    // Користувач обирає групу
    std::cout << "Введіть номер групи: ";
    int groupIndex;
    std::cin >> groupIndex;

    // Перевірка на правильність вибору
    if (groupIndex < 1 || groupIndex > groups.size())
    {
        std::cout << "Недійсний вибір." << std::endl;
        return;
    }

    // Отримуємо вибрану групу
    CriminalGroup& selectedGroup = groups[groupIndex - 1];
    system("cls");
    int choice;
    do
    {
        // Виведення інформації про вибрану групу та її членів
        std::cout << "Організація: " << selectedGroup.getGroupName() << "\n";
        const std::vector<Criminal>& members = selectedGroup.getMembers(); // Отримати список членів
        for (size_t i = 0; i < members.size(); ++i)
        {
            std::cout << "  Учасник: " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
        }
        std::cout << "\n-------------\n\n";

        // Опції для користувача
        std::cout << "1. Додати учасника" << std::endl;
        std::cout << "2. Видалити учасника" << std::endl;
        std::cout << "3. Видалити організацію" << std::endl;
        std::cout << "4. [Повернутись у меню]" << std::endl;
        std::cout << "Оберіть опцію: ";
        std::cin >> choice;

        // Перевірка на правильність введення
        if (choice > 4 || choice <= 0)
        {
            system("cls");
            std::cout << "Недійсна опція. Спробуйте ще раз.\n\n";
        }
    } while (choice > 4 || choice <= 0);
    system("cls");

    switch (choice)
    {
    case 1:
    {
        // Додавання учасника
        bool criminalFound = false;
        std::string firstName, lastName;
        while (!criminalFound)
        {
            std::cout << "Введіть ім'я злочинця: ";
            std::cin >> firstName;
            std::cout << "Введіть прізвище злочинця: ";
            std::cin >> lastName;

            // Пошук злочинця
            Criminal criminal = criminal.findCriminalByName(firstName, lastName);

            if (!criminal.getLastName().empty())
            {
                // Перевіряємо, чи не є злочинець вже членом групи
                if (criminal.isCriminalInGroup(selectedGroup, criminal))
                {
                    system("cls");
                    std::cout << criminal.getFirstName() + " " + criminal.getLastName() + " уже являється учасником організації.\n";
                }
                else
                {
                    // Додавання злочинця до групи
                    selectedGroup.addMember(criminal);
                    selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
                    selectedGroup.saveToFile(selectedGroup); // Збереження змін у файл
                    system("cls");
                    std::cout << "Злочинець успішно доданий до організації" << std::endl;
                    criminalFound = true; // Вихід з циклу
                }
            }
            else
            {
                system("cls");
                std::cout << "Злочинця не знайдено. Спробуйте ще раз.\n";
            }
        }
        break;
    }
    case 2:
    {
        // Видалення члена групи
        const std::vector<Criminal>& members = selectedGroup.getMembers(); // Отримати список членів групи

        if (members.empty())
        {
            std::cout << "У організації жодного злочинця." << std::endl;
        }
        else
        {
            int memberIndex = 0;
            bool validInput = false;

            while (!validInput)
            {
                // Виводимо список членів групи
                std::cout << "Організація: " << selectedGroup.getGroupName() << "\n";
                for (size_t i = 0; i < members.size(); ++i)
                {
                    std::cout << "  " << i + 1 << ". " << members[i].getFirstName() << " " << members[i].getLastName() << std::endl;
                }

                std::cout << "\n-------------\n\n";

                try
                {
                    // Вибір члена для видалення
                    std::cout << "Введіть номер учасника якого бажаєте видалити: ";
                    std::cin >> memberIndex;

                    // Перевірка на коректність вводу
                    if (std::cin.fail())
                    {
                        throw std::invalid_argument("Неправильне введення. Будь ласка, введіть число.");
                    }

                    if (memberIndex < 1 || memberIndex > members.size())
                    {
                        throw std::out_of_range("Неправильний вибір. Будь ласка, виберіть правильний номер учасника.");
                    }

                    validInput = true; // Вихід з циклу після коректного вводу
                }
                catch (const std::invalid_argument& e)
                {
                    std::cin.clear(); // Очищення помилки
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропуск некоректного вводу
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                }
                catch (const std::out_of_range& e)
                {
                    system("cls");
                    std::cout << e.what() << std::endl << std::endl;
                }
            }

            // Видалення вибраного члена
            const Criminal& memberToRemove = members[memberIndex - 1];
            selectedGroup.removeMember(selectedGroup.getGroupName(), memberToRemove.getFirstName(), memberToRemove.getLastName());
        }
        break;
    }
    case 3:
        // Видалення групи
        selectedGroup.removeGroupFromFile(selectedGroup.getGroupName());
        system("cls");
        std::cout << "Організацію успішно видалено." << std::endl;
        break;
    case 4:
        // Повернення до меню
        break;
    default:
        system("cls");
        std::cout << "Недійсна опція." << std::endl;
        break;
    }
}

// Метод для виведення посібника користувача
void Menu::displayUserGuide()
{
    system("cls"); // Очищаємо екран перед виведенням нової інформації.

    // Виводимо заголовок і список дій, для яких можна отримати інструкції.
    std::cout << "-------- Посібник користувача --------" << std::endl;
    std::cout << "Оберіть дію для перегляду інструкції:\n";
    std::cout << "1. Як додати нового злочинця\n";
    std::cout << "2. Як переглянути список злочинців\n";
    std::cout << "3. Як архівувати злочинця\n";
    std::cout << "4. Як видалити злочинця після смерті\n";
    std::cout << "5. Як здійснити пошук злочинців за критеріями\n";
    std::cout << "6. Як здійснити сортування злочинців\n";
    std::cout << "7. Як додати нову кримінальну організацію\n";
    std::cout << "8. Як переглянути список кримінальних організацій\n";
    std::cout << "9. Як оновити дані організації\n";
    std::cout << "10. Як переглянути архів\n";
    std::cout << "---------------------------------------" << std::endl;

    // Запитуємо вибір користувача для відображення відповідних інструкцій.
    std::cout << "\nОберіть опцію: ";
    int choice;
    cin >> choice;
    displayInstructions(choice); // Викликаємо функцію для відображення інструкцій на основі вибору.
}

// Метод для виведення інструкцій у посібнику користувача
void Menu::displayInstructions(int choice)
{
    switch (choice) {
    case 1:
        system("cls");
        std::cout << "Інструкція: Як додати нового злочинця\n";
        std::cout << "1. Виберіть опцію 'Додати злочинця' у головному меню.\n";
        std::cout << "2. Введіть ім'я, прізвище, псевдонім, зріст, колір очей, волосся, особливі ознаки та інші запитувані дані.\n";
        std::cout << "3. Після введення даних, злочинець буде доданий до бази даних.\n\n\n";
        break;
    case 2:
        system("cls");
        std::cout << "Інструкція: Як переглянути список злочинців\n";
        std::cout << "1. Виберіть опцію 'Список злочинців' у головному меню.\n";
        std::cout << "2. Ви побачите список всіх злочинців, що є в базі даних.\n\n\n";
        break;
    case 3:
        system("cls");
        std::cout << "Інструкція: Як архівувати злочинця\n";
        std::cout << "1. Виберіть опцію 'Архівувати злочинця' у головному меню.\n";
        std::cout << "2. Введіть ім'я та прізвище злочинця, якого потрібно архівувати.\n";
        std::cout << "3. Після підтвердження злочинець буде переміщений в архів.\n\n\n";
        break;
    case 4:
        system("cls");
        std::cout << "Інструкція: Як видалити злочинця після смерті\n";
        std::cout << "1. Виберіть опцію 'Видалити злочинця після смерті' у головному меню.\n";
        std::cout << "2. Введіть дані злочинця, якого потрібно видалити.\n";
        std::cout << "3. Підтвердьте видалення злочинця з бази даних.\n\n\n";
        break;
    case 5:
        std::cout << "Інструкція: Як здійснити пошук злочинців за критеріями\n";
        std::cout << "1. Виберіть опцію 'Пошук злочинця за критерієм' у головному меню.\n";
        std::cout << "2. Введіть критерії для пошуку (ім'я, прізвище, псевдонім тощо).\n";
        std::cout << "3. Результати пошуку будуть відображені на екрані.\n\n\n";
        break;
    case 6:
        system("cls");
        std::cout << "Інструкція: Як здійснити сортування злочинців\n";
        std::cout << "1. Виберіть опцію 'Сортування' у головному меню.\n";
        std::cout << "2. Оберіть тип сортування (по імені, прізвищу або зросту).\n";
        std::cout << "3. Результати сортування будуть відображені на екрані.\n\n\n";
        break;
    case 7:
        system("cls");
        std::cout << "Інструкція: Як додати нову кримінальну організацію\n";
        std::cout << "1. Виберіть опцію 'Додати нову організацію' у головному меню.\n";
        std::cout << "2. Введіть назву організації та інші запитувані дані.\n";
        std::cout << "3. Організація буде додана до бази даних.\n\n\n";
        break;
    case 8:
        system("cls");
        std::cout << "Інструкція: Як переглянути список кримінальних організацій\n";
        std::cout << "1. Виберіть опцію 'Переглянути список кримінальних організацій' у головному меню.\n";
        std::cout << "2. Ви побачите список усіх організацій, що є в базі даних.\n\n\n";
        break;
    case 9:
        system("cls");
        std::cout << "Інструкція: Як оновити дані організації\n";
        std::cout << "1. Виберіть опцію 'Оновити інформацію про організацію' у головному меню.\n";
        std::cout << "2. Введіть нові дані для організації, яку потрібно оновити.\n";
        std::cout << "3. Після підтвердження дані організації будуть оновлені.\n\n\n";
        break;
    case 10:
        system("cls");
        std::cout << "Інструкція: Як переглянути архів\n";
        std::cout << "1. Виберіть опцію 'Архів' у головному меню.\n";
        std::cout << "2. Ви побачите список архівованих злочинців та організацій.\n\n\n";
        break;
    case 11:
        system("cls");
        std::cout << "Інструкція: Як переглянути посібник користувача\n";
        std::cout << "1. Виберіть опцію 'Посібник користувача' у головному меню.\n";
        std::cout << "2. Ви зможете вибрати конкретну інструкцію для перегляду.\n\n\n";
        break;
    default:
        system("cls");
        std::cout << "Некоректний вибір. Спробуйте ще раз.\n\n\n";
        break;
    }
}

// Метод для виведення меню сортування
void Menu::displaySortMenu()
{
    try
    {
        // Виведення меню сортування.
        cout << "Оберіть тип сортування: \n";
        cout << "1. По імені\n";
        cout << "2. По прізвищу\n";
        cout << "3. По зросту\n";
        std::cout << "Оберіть опцію: ";
        int option;
        std::cin >> option;

        // Перевірка на коректність введеного значення.
        if (std::cin.fail() || option < 1 || option > 3)
        {
            system("cls");
            throw std::invalid_argument("Неправильний вибір опції. Введіть число від 1 до 3.");
        }

        Criminal criminal;  // Створення об'єкта Criminal.

        switch (option)
        {
        case 1:
            system("cls");
            criminal.sortCriminalByFirstName();  // Сортування за ім'ям.
            break;

        case 2:
            system("cls");
            criminal.sortCriminalByLastName();  // Сортування за прізвищем.
            break;

        case 3:
            system("cls");
            criminal.sortCriminalByHeight();  // Сортування за зростом.
            break;

        default:
            throw std::invalid_argument("Неправильний вибір.");
        }
    }
    catch (const std::invalid_argument& e)
    {
        // Обробка помилки вводу.
        std::cerr << "Помилка: " << e.what() << std::endl;
        std::cin.clear(); // Скидання стану потоку.
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ігнорування неправильного введення.
    }
    catch (const std::exception& e)
    {
        // Загальна обробка помилок.
        std::cerr << "Виникла помилка: " << e.what() << std::endl;
    }
}