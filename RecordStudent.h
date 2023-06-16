#pragma once
#include <string>
#include "Date.h"
#include "Grade.h"


class RecordStudent
{
private:
    std::string Name, SecondName, MiddleName;
    Date Birth;
public:
    std::string Faculty, Departament, Group;
    char Gender;    
    int Entrance, GradeBook, AmountSubjects;        
    Grade Session[10];    
    RecordStudent();
    RecordStudent(std::string*);
    bool GetPercentageMarks(const int*, Date*);
    std::string GetName();
    std::string GetSecondName();
    std::string GetMiddleName();
    std::string GetBirth();
    void SetName(std::string*);
    void SetSecondName(std::string*);
    void SetMiddleName(std::string*);
    void SetBirth(std::string*);
    int GetDay();
    int GetMonth();
    int GetYear();
};

