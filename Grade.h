#pragma once
#include <string>

struct Grade
{
    std::string Subject;
    char Marks[9] = {'0', '0', '0', '0', '0', '0', '0', '0', '0'};


    Grade();
    Grade(std::string*, char*);
};