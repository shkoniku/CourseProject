#include <iostream>
#include "Grade.h"


Grade::Grade()
{

}


Grade::Grade(std::string* inputString, char* marks)
{    
    Subject = (*inputString);
    for (int iterator = 0; iterator < 9; iterator++)
    {
        Marks[iterator] = marks[iterator];
    }
}