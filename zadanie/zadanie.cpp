/*
Niestety nie udało mi się zaimplementować wielowątkowości. Potrafię sprawdzić pulę wątków, utowrzyć je i wywołać, natomiast nie potrafię
podzielić zadań między nimi. Jedyne udane próby skończyły się na wywołaniu n wątków, ktore wykonały to samo zadanie n razy, jednak to
mija się z celem, ponieważ w żaden sposób nie przyspiesza pracy, a wręcz przeciwnie - przedłuża ją i powtarza operacje na tych samych danych.
Zdaję sobie sprawę, że mój program jest niekompletny, dlatego będę wdzięczny za wskazówki dotyczące zastosowania wielowątkowości i rozwiązania
postawionego problemu.
*/

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <mutex>
#include <thread>

void directory_statistics(const std::string& dir)
{
    int files_counter = 0;
    int lines_counter = 0;
    int chars_counter = 0;

    for (auto& el : std::filesystem::recursive_directory_iterator(dir, std::filesystem::directory_options::skip_permission_denied)) {
        files_counter++;

        std::fstream file;
        file.open(el.path(), std::ios::in);
        if (file.is_open())
        {
            std::string str;
            while (getline(file, str))
            {
                lines_counter++;
                chars_counter += str.length();
            }
        }
        file.close();
    }

    std::cout << "Number of files: " << files_counter << '\n';
    std::cout << "Number of lines: " << lines_counter << '\n';
    std::cout << "Number of chars: " << chars_counter << '\n';
    std::cout << '\n';
}

int main()
{
    std::string path;

    std::cout << "Write path or press 'q' for quit: ";
    std::cin >> path;
    while (path != "q")
    {
        try
        {
            directory_statistics(path);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        std::cout << "Write path or press 'q' for quit: ";
        std::cin >> path;
    }
}
