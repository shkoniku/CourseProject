#pragma once

struct Date
{
public:
    Date();
    Date(std::string*);    
    std::string GetDate();
    int Year = 1940,
        Month = 12,
        Day = 1;
};