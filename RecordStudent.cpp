#include <iostream>
#include <regex>
#include "RecordStudent.h"


char GetGender(std::string* inputString)
{
    char filler = '0';
    filler = (*inputString)[0];
    if (filler == 'м' || filler == 'ж')
    {
        return filler;
    } else {        
        std::cout << "Ошибка, неверно введенные данные!";
        exit(0);
    }        
}


std::string getSubstring(std::string* inputString, bool border=false)
{
    std::string filler = "";
    int end = inputString->find(' ');
    if (end != -1)
    {
        filler = inputString->substr(0, end);        
        inputString->erase(0, end + 1);
        return filler;
    } else if (!border) {
        std::cout << "Ошибка, неверно введенные данные!";
        exit(0);
    } else {
        filler = (*inputString);
        inputString->erase(0, (*inputString).size() - 1);
        return filler;
    }
}


int getSubstringToInt(std::string* inputString, bool border=false)
{
    std::string filler = "";    
    int value = 0;
    int end = inputString->find(' ');
    if (end != -1)
        {
        filler = inputString->substr(0, end);
        int iterator = 0;
        while (iterator < filler.size())
        {
            if (isdigit(filler[iterator]))
            {
                value *= 10;
                value += static_cast<int>(filler[iterator]) - 48;
            } else {                
                std::cout << "Ошибка, неверно введенные данные!";
                exit(0);
            }
            iterator++;
        }                
        (*inputString).erase(0, end + 1);
        return value;
    } else if (!border) {
        std::cout << "Ошибка, неверно введенные данные!";
        exit(0);
    } else {
        filler = (*inputString);
        inputString->erase(0, (*inputString).size() - 1);
        int iterator = 0;
        while (iterator < filler.size())
        {
            value *= 10;
            value += static_cast<int>(filler[iterator]) - 48;
            iterator++;
        }
        return value;
    }
}


bool RecordStudent::GetPercentageMarks(const int* mark, Date* intervalBirthdays)
{
    const double percentage = 25.0;
    int amountAllMarks = 0;    
    std::pair<int, int>* percent = new std::pair<int, int>[1];
    for (int i = 0; i < 1; i++)
    {        
        percent[i].first = *mark;
        percent[i].second = 0;
    }
    for (int subject = 0; subject < AmountSubjects; subject++)
    {
        int markNumber = 0;
        while (markNumber < 9 && Session[subject].Marks[markNumber] != '0')
        {
            for (int numberMarkPercent = 0; numberMarkPercent < 1; numberMarkPercent++)
            {
                if (static_cast<int>(Session[subject].Marks[markNumber]) - 48 == percent[numberMarkPercent].first)
                {                           
                    int count = percent[numberMarkPercent].second;
                    count++;
                    percent[numberMarkPercent].second = count;
                }
                if (Session[subject].Marks[markNumber] != '-' && numberMarkPercent == 0)
                    amountAllMarks++;
            }
            markNumber++;
        }
    }
    for (int marks = 0; marks < 1; marks++)
    {        
        if (intervalBirthdays == nullptr)
        {
            if (double(percent[marks].second) / amountAllMarks * 100 - percentage > 0.0001)
            {
                delete[] percent;
                return false;
            }
        }
        else
        {
            int leftBorder = intervalBirthdays[0].Day + intervalBirthdays[0].Month * 30 + intervalBirthdays[0].Year * 364,
                rigthBorder = intervalBirthdays[1].Day + intervalBirthdays[1].Month * 30 + intervalBirthdays[1].Year * 364,
                borderNow = GetDay() + GetMonth() * 30 + GetYear() * 364;
            if (double(percent[marks].second) / amountAllMarks * 100 - percentage > 0.0001 || borderNow < leftBorder || borderNow > rigthBorder)
                return false;
        }
        
    }    
    delete[] percent;
    return true;
}


RecordStudent::RecordStudent(std::string* inputString)
{
    AmountSubjects = 0;
    SecondName = getSubstring(inputString);   
    Name = getSubstring(inputString);
    MiddleName = getSubstring(inputString);
    Birth = Date(inputString);
    Entrance = getSubstringToInt(inputString);
    Faculty = getSubstring(inputString);
    Departament = getSubstring(inputString);
    Group = getSubstring(inputString);
    GradeBook = getSubstringToInt(inputString, true);
    Gender = GetGender(inputString);
}


RecordStudent::RecordStudent()
{
    Name = SecondName = MiddleName = Faculty = Departament = Group = "none";
    Gender = 'n';
    Entrance = GradeBook = 0;
}


std::string RecordStudent::GetName()
{
    return Name;
}


std::string RecordStudent::GetSecondName()
{
    return SecondName;
}


std::string RecordStudent::GetMiddleName()
{
    return MiddleName;
}


std::string RecordStudent::GetBirth()
{
    return Birth.GetDate();
}


void RecordStudent::SetName(std::string* name)
{
    Name = (*name);
}


void RecordStudent::SetSecondName(std::string* secondName)
{
    SecondName = (*secondName);
}


void RecordStudent::SetMiddleName(std::string* middleName)
{
    MiddleName = (*middleName);
}


void RecordStudent::SetBirth(std::string* birth)
{
    Birth = Date(birth);
}


int RecordStudent::GetDay()
{
    return Birth.Day;
}


int RecordStudent::GetMonth()
{
    return Birth.Month;
}


int RecordStudent::GetYear()
{
    return Birth.Year;
}