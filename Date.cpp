#include <iostream>
#include "Date.h"


Date::Date(std::string* inputString)
{
    int end = inputString->find(' ');
    std::string birth = inputString->substr(0, end);
    inputString->erase(0, end + 1);
    int count = 0, iterator = 0, day = 0, month = 0, filler = 0;
    while (count < 3 && iterator < birth.size())
    {        
        if ((birth[iterator] == ' ' || birth[iterator] == '.') && count == 0)
        {
            day = filler;
            filler = 0;
            count++;            
        } else
        if ((birth[iterator] == ' ' || birth[iterator] == '.') && count == 1)
        {
            month = filler;
            filler = 0;
            count++;            
        }        
        if (isdigit(birth[iterator]) )
        {
            filler *= 10;
            filler += static_cast<int>(birth[iterator]) - 48;            
        } else if (birth[iterator] != '.') {            
            std::cout << "Ошибка в формате ввода даты! \n";
            exit(0);
        }
        iterator++;
    }
    Day = day;
    Month = month;
    Year = filler;
}


Date::Date()
{
    
}


std::string Date::GetDate()
{
    std::string birth = "";    
    if (Day < 10)
    {
        birth += '0';
        birth += static_cast<char>(Day + 48);
    } else {
        int filler = Day, count = 0, number[2] = {};
        while (filler > 0)
        {
            
            number[count] = filler % 10;            
            count++;
            filler /= 10;
        }
        while (count - 1 >= 0)
        {
            
            birth += static_cast<char>(number[count - 1] + 48);
            count--;
        }
    }
    
    birth += '.';
    if (Month < 10)
    {
        birth += '0';
        birth += static_cast<char>(Month + 48);
    } else {
        int filler = Month, count = 0, number[2] = {};
        while (filler > 0)
        {
            number[count] = filler % 10;
            std::cout << filler % 10 << '\n';
            count++;
            filler /= 10;
        }
        while (count - 1 >= 0)
        {
            birth += static_cast<char>(number[count - 1] + 48);
            count--;
        }
    }
    birth += '.';
    int filler = Year, count = 0, number[4] = {};
    while (filler > 0)
    {
        number[count] = filler % 10;
        count++;
        filler /= 10;
    }
    while (count - 1 >= 0)
    {
        birth += static_cast<char>(number[count - 1] + 48);
        count--;
    }        
    return birth;
}