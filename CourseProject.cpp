#include <iostream>
#include "windows.h"
#include <fstream>
#include <time.h>
#include "RecordStudent.h"


void Crypt();


bool IsItDate(std::string*);


void DeleteStudent(RecordStudent* Students, RecordStudent* students, unsigned int* amountStudents, int number)
{
    for (int iterator = 0; iterator < number - 1; iterator++)
    {
        Students[iterator] = students[iterator];
    }
    for (int iterator = number - 1; iterator < *amountStudents - 1; iterator++)
    {
        Students[iterator] = students[iterator + 1];
    }
    *amountStudents -= 1;
    std::cout << "Удален студент: " << students[number - 1].GetSecondName() << ' ' << students[number - 1].GetName() << ' ' << students[number - 1].GetMiddleName() << '\n';
}


void Terminate(RecordStudent* Students)
{
    Crypt();    
    exit(0);
}


bool Continue()
{
    std::string answer = "";
    while (answer != "д\n" && answer != "д\r" && answer != "д\0" && answer != "н" && answer != "н\n" && answer != "н\r" && answer != "н\0")
    {
        std::cout << "Продолжить ввод? Введите \"д\" или \"н\". \n";
        std::cin >> answer;
    }
    if (answer == "н")
        return false;
    return true;
}


bool IsDigit(std::string* inputString, char* sessions)
{
    int end = inputString->find(' '), iterator = 0;        
    while (inputString->size() >= 1)
    {        
        if (end == -1 && inputString->size() > 1)
            return false;
        else if (end == -1 && inputString->size() == 1)
        {
            end = 0;
        }
        if ((!isdigit((*inputString)[0]) && (*inputString)[0] != '-') || (((*inputString)[0] > '5' || (*inputString)[0] < '2') && (*inputString)[0] != '-') || end > 1)
        {            
            return false;
        }            
        else {
            sessions[iterator] = (*inputString)[0];
            iterator++;
            inputString->erase(0, end + 1);
            end = inputString->find(' ');
        }
    }
    return true;
}


bool IsStringAlpha(std::string* inputString)
{    
    if (inputString->size() == 0)
        return false;
    for (int iterator = 0; iterator < inputString->size(); iterator++)
    {
        if (((*inputString)[iterator] < 'а' || (*inputString)[iterator] > 'я') && ((*inputString)[iterator] < 'А' || (*inputString)[iterator] > 'Я'))
        {                      
            return false;
        }
    }
    return true;
}


bool IsDigit(std::string* inputStr)
{    
    if (inputStr->size() == 0)
        return false;
    for (auto symbol : (*inputStr))
    {
        if (!isdigit(symbol))
        {            
            return false;
        }
    }
    return true;
}


int StringToInt(std::string* inputString)
{
    int number = 0;
    for (int iterator = 0; iterator < (*inputString).size(); iterator++)
    {
        number *= 10;
        number += static_cast<int>((*inputString)[iterator]) - 48;
    }
    return number;
}


int GetAmountStudents()
{
    std::string inputUser = "";
    do
    {
        std::cout << "Введите количество студентов(целое и неотрицательное число): \n";        
        std::getline(std::cin, inputUser);
    } while (!IsDigit(&inputUser));    
    return StringToInt(&inputUser);
}


int GetNumberStudent(const unsigned int& amountStudents)
{
    std::string inputUser = "none";
    while (!IsDigit(&inputUser) || StringToInt(&inputUser) < 1 || StringToInt(&inputUser) > amountStudents)
    {
        std::cout << "Введите номер студента(натуральное число): \n";        
        std::getline(std::cin, inputUser);
    }    
    return StringToInt(&inputUser);
}


void GetSubjects(RecordStudent* Students, int numberStudent, int amountSubjects = 0)
{
    std::string subject = "none", temporary = "";
    if (amountSubjects == 0)
    {
        do
        {            
            std::cout << "Введите количество дисциплин у студента: \n";            
            std::getline(std::cin, temporary);
        } while (!IsDigit(&temporary));
        amountSubjects = StringToInt(&temporary);
    }    
    char* marks = new char[9];
    for (int iterator = Students[numberStudent].AmountSubjects; iterator < amountSubjects; iterator++)
    {
        bool correct = true;
        do
        {
            correct = true;
            std::cout << "Введите название дисциплины и оценки по этой дисциплине в каждой сессии через пробел(если в сессии не было этого предмета, введите \"-\"): \n";
            int end = 0;
            for (int i = 0; i < 9; i++)
            {
                marks[i] = '0';
            }
            std::getline(std::cin, temporary);
            end = temporary.find(' ');
            subject = temporary.substr(0, end);
            temporary.erase(0, end + 1);
            if (!IsStringAlpha(&subject) || !IsDigit(&temporary, marks))
            {
                correct = false;
                std::cout << "Ошибка, неверно введенные данные!\n";
            }
        } while (!correct);
        Students[numberStudent].Session[iterator] = Grade(&subject, marks);        
    }
    Students[numberStudent].AmountSubjects = amountSubjects;
    delete[] marks;
}


void GetStudents(RecordStudent* Students, unsigned int* amountStudents, const int& amountStudentsToAdd)
{    
    std::string inputUser = "";
    std::cout << "Введите фамилию, имя, отчество, дату рождения(через точку цифрами в формате : ДД.ММ.ГГГГ), год поступления в вуз(четырехзначное число), \n";
    std::cout << "название факультета(аббревиатура, нпример, ПИ), название кафедры(аббревиатура, например: \"КБ1\"), кодировку группы( например: БАСО-04-22), номер зачетной книжки(пятизнанчное число), \n";
    std::cout << "пол(одна буква \"м\" или \"ж\") через пробел поочереди для каждого студента. \n";
    std::cout << "В конце записи каждого студента перейти на новую строку(нажать ENTER). После чего ввести количество дисциплин у студента. \n";         
    for (int i = 0; i < amountStudentsToAdd; i++)
    {
        if (i > 0)
            std::cout << "Введите информацию о следующем студенте: \n";
        std::getline(std::cin, inputUser);
        Students[i + *amountStudents] = RecordStudent(&inputUser);
        GetSubjects(Students, i + *amountStudents);
    }        
    *amountStudents = *amountStudents + amountStudentsToAdd;    
}


void ShowStudentsList(RecordStudent* Students, int amountStudents)
{
    std::cout << "Список студентов: \n";
    for (int iterator = 0; iterator < amountStudents; iterator++)
    {
        std::cout << iterator + 1 << ". " << Students[iterator].GetSecondName() << ' ' << Students[iterator].GetName() << ' ' << Students[iterator].GetMiddleName() << '\n';
    }
    if (amountStudents == 0)
    {
        std::cout << "Список студентов пуст\n";
    }
}


void ChangeSubject(RecordStudent* Students, int numberStudent, int numberSubject)
{
    char* marks = new char[9];
    for (int iterator = 0; iterator < 9; iterator++)
    {
        marks[iterator] = '0';
    }
    int end = 0;
    std::string temporary = "", subject = "";
    while (!IsDigit(&temporary, marks) || !IsStringAlpha(&subject))
    {
        std::cout << "Введите название дисциплины и оценки по этой дисциплине в каждой сессии через пробел(если в сессии не было этого предмета, введите \"-\"): \n";        
        std::getline(std::cin, temporary);
        end = temporary.find(' ');
        subject = temporary.substr(0, end);
        temporary.erase(0, end + 1);
    }
    Students[numberStudent].Session[numberSubject].Subject = subject;
    for (int iterator = 0; iterator < 9; iterator++)
    {
        Students[numberStudent].Session[numberSubject].Marks[iterator] = marks[iterator];
    }    
    delete[] marks;
}


void ChangeInfo(RecordStudent* Students, int amountStudents)
{
    bool incorrect = true, farther = false;
    int numberStudent = -1;    
    std::string number = "", argument = "";        
    do {
        std::cout << "Введите номер студента и что вы хотите изменить через пробел :\n";
        std::cout << "(напишите: \"имя\", если вы хотитие изменить имя; напишите: \"фамилия\", если вы хотите изменить фамилию; \n";
        std::cout << "напишите: \"отчество\", если вы хотите изменить отчество; напишите: \"дата\", если вы хотите изменить дату рождения; \n";
        std::cout << " напишите: \"год\", если вы хотите изменить год поступления; напишите: \"факультет\", если вы хотите изменить факультет; \n";
        std::cout << " напишите: \"кафедра\", если вы хотите изменить кафедру; напишите: \"группа\", если вы хотите изменить группу; \n";
        std::cout << " напишите: \"номер\", если вы хотите изменить номер зачетной книжки; напишите: \"пол\", если вы хотите изменить пол; \n";
        std::cout << " напишите: \"предмет\", если вы хотите изменить предмет или оценки за сессию. \n";
        incorrect = true;
        ShowStudentsList(Students, amountStudents);
        while (incorrect)
        {
            bool farther = true;
            std::cout << "Введите номер студента и что вы хотите изменить через пробел: \n";
            std::cin >> number >> argument;
            numberStudent = StringToInt(&number);
            incorrect = !IsStringAlpha(&argument) || argument.size() < 3 || !IsDigit(&number) || numberStudent < 1 || numberStudent > amountStudents;
            if (incorrect)
            {
                std::cout << "Ошибка ввода!";
                farther = Continue();
            }                
            if (!farther)
                return;
        }
        std::cout << "Выбран студент: " << Students[numberStudent - 1].GetSecondName() << ' ' << Students[numberStudent - 1].GetName() << ' ' << Students[numberStudent - 1].GetMiddleName() << '\n';
        if (argument == "имя")
        {
            std::string name = "";
            while (!IsStringAlpha(&name))
            {
                std::cout << "Введите имя: \n";
                std::cin >> name;
            }
            Students[numberStudent - 1].SetName(&name);
            std::cout << "Имя изменено на " << Students[numberStudent - 1].GetName() << '\n';
        } 
        else if (argument == "фамилия")
        {
            std::string secondName = "";
            while (!IsStringAlpha(&secondName))
            {
                std::cout << "Введите фамилию: \n";
                std::cin >> secondName;
            }
            Students[numberStudent - 1].SetSecondName(&secondName);
            std::cout << "Фамилия изменена на " << Students[numberStudent - 1].GetSecondName() << '\n';
        } 
        else if (argument == "отчество")
        {
            std::string middleName = "";
            while (!IsStringAlpha(&middleName))
            {
                std::cout << "Введите отчество: \n";
                std::cin >> middleName;
            }
            Students[numberStudent - 1].SetMiddleName(&middleName);
            std::cout << "Отчество изменено на " << Students[numberStudent - 1].GetMiddleName() << '\n';
        } 
        else if (argument == "дата")
        {
            std::cout << "Текущая дата рождения: " << Students[numberStudent - 1].GetBirth() << '\n';
            std::string data = "";
            std::cout << "Введите новую дату рождения(в формате ДД.ММ.ГГГГ): \n";
            std::cin >> data;
            if (IsItDate(&data))
            {
                Students[numberStudent - 1].SetBirth(&data);
                std::cout << "Дата изменена на " << Students[numberStudent - 1].GetBirth() << '\n';
            }                
            else
                std::cout << "Ошибка ввода даты! \n";            
        } 
        else if (argument == "год")
        {
            std::cout << "Текущий год поступления: " << Students[numberStudent - 1].Entrance << '\n';
            int entranceInt = 0;
            std::string entrance = "";
            while (!IsDigit(&entrance) || entrance.size() != 4)
            {
                std::cout << "Введите год поступления (четырехзначное число): \n";
                std::cin >> entrance;
            }
            entranceInt = StringToInt(&entrance);
            Students[numberStudent - 1].Entrance = entranceInt;
            std::cout << "Дата поступления изменена на " << Students[numberStudent - 1].Entrance << '\n';
        } 
        else if (argument == "факультет")
        {
            std::cout << "Текущий факультет: " << Students[numberStudent - 1].Faculty << '\n';
            std::string faculty = "";
            while (!IsStringAlpha(&faculty))
            {
                std::cout << "Введите название факультета(аббревиатура) :\n";
                std::cin >> faculty;
            }
            Students[numberStudent - 1].Faculty = faculty;
            std::cout << "Факультет изменен на: " << Students[numberStudent - 1].Faculty << '\n';
        } 
        else if (argument == "кафедра")
        {
            std::cout << "Текущая кафедра: " << Students[numberStudent - 1].Departament << '\n';
            std::string department = "";
            while (!IsStringAlpha(&department))
            {
                std::cout << "Введите название факультета(аббревиатуру): \n";
                std::cin >> department;
            }
            Students[numberStudent - 1].Departament = department;
            std::cout << "Факультет был изменен на: \n" << Students[numberStudent - 1].Departament;
        } 
        else if (argument == "группа")
        {
            std::cout << "Текущая группа: " << Students[numberStudent - 1].Group << '\n';
            std::string group = "";
            while (group.size() <= 8)
            {
                std::cout << "Введите название группы(аббревиатуру, минимальной длины 8, например: БАСО-04-22): \n";
                std::cin >> group;
            }
            Students[numberStudent - 1].Group = group;
            std::cout << "Группа была изменена на: " << Students[numberStudent - 1].Group << '\n';
        } 
        else if (argument == "номер")
        {
            std::cout << "Текущий номер зачетной книжки: " << Students[numberStudent - 1].GradeBook << '\n';
            std::string number = "";
            while (!IsDigit(&number) || number.size() < 5)
            {
                std::cout << "Введите номер зачетной книжки: \n";
                std::cin >> number;
            }
            Students[numberStudent - 1].GradeBook = StringToInt(&number);
            std::cout << "Номер зачетной книжки изменен на " << Students[numberStudent - 1].GradeBook << '\n';
        } 
        else if (argument == "пол")
        {
            std::cout << "Текущий пол: " << Students[numberStudent - 1].Gender << '\n';
            char gender = '0';
            while (gender != 'м' && gender != 'ж')
            {
                std::cout << "Введите пол(букву \'м\' или \'ж\'): \n";
                std::cin >> gender;
            }
            Students[numberStudent - 1].Gender = gender;
            std::cout << "Пол был изменен на " << Students[numberStudent - 1].Gender << '\n';
        } 
        else if (argument == "предмет")
        {
            std::string subject = "", temporary = "";
            int end = 0, amountSubjects = 0;
            for (int iterator = 0; iterator < Students[numberStudent - 1].AmountSubjects; iterator++)
            {
                std::cout << iterator + 1 << ". " << Students[numberStudent - 1].Session[iterator].Subject << ": ";
                int count = 0;
                while (Students[numberStudent - 1].Session[iterator].Marks[count] != '0')
                {
                    std::cout << Students[numberStudent - 1].Session[iterator].Marks[count] << ' ';
                    count++;
                }
                std::cout << "\n";
            }
            while (amountSubjects < 1 || amountSubjects > 10)
            {
                std::cout << "Введите порядковый номер предемета, который хотитие изменить, или обновленное количество предметов для студента(натуральное число меньше 11): \n";
                std::cin >> temporary;
                if (IsDigit(&temporary))
                    amountSubjects = StringToInt(&temporary);
            }            
            if (amountSubjects > Students[numberStudent - 1].AmountSubjects)
            {
                GetSubjects(Students, numberStudent - 1, amountSubjects);
            } else
            {
                ChangeSubject(Students, numberStudent - 1, amountSubjects - 1);
            }                     
            std::cout << "Дисциплины изменены на: \n";
            for (int iterator = 0; iterator < Students[numberStudent - 1].AmountSubjects; iterator++)
            {
                std::cout << iterator + 1 << ". " << Students[numberStudent - 1].Session[iterator].Subject << ": ";
                int count = 0;
                while (Students[numberStudent - 1].Session[iterator].Marks[count] != '0')
                {
                    std::cout << Students[numberStudent - 1].Session[iterator].Marks[count] << ' ';
                    count++;
                }
                std::cout << "\n";
            }
        }
        farther = true;
        farther = Continue();
    } while (farther);
}


bool IsItDate(std::string* inputString)
{    
    std::string day = inputString->substr(0, 2), month = inputString->substr(3, 2), year = inputString->substr(6, 4);
    if (inputString->size() != 10 || (*inputString)[2] != '.' || (*inputString)[5] != '.' || !IsDigit(&day) || !IsDigit(&month) || !IsDigit(&year))
    {               
        return false;
    }    
    if (StringToInt(&day) > 31 || StringToInt(&day) < 1 || StringToInt(&month) < 1 || StringToInt(&month) > 12 || StringToInt(&year) > 2010 || StringToInt(&year) < 1990)
        return false;
    return true;
}


void GetMarks(RecordStudent* Students, const int& amountStudents)
{
    bool anyone = false;
    Date* intervalBirthdays = nullptr;
    int* marks = new int[0];
    std::string inputString = "";
    int amountMarks = 0, countBirthdays = 0;
    std::cout << "Введите оценки(числа от 2 до 5), по которым будут отбираться студенты, через пробел в одной строке.\nВ следющей возможно ввести две даты(в формате: ДД.ММ.ГГГГ) для поиска по дате рождения: \n";
    std::cin.ignore();
    std::getline(std::cin, inputString);        
    while (inputString.size() > 0)
    {     
        std::string mark = inputString.substr(0, 1);
        if (mark.size() == 1 && (static_cast<int>(mark[0]) - 48 < 2 || static_cast<int>(mark[0]) - 48 > 5))
        {
            std::cout << "Была введена не оценка(число от 2 до 5)! \n";
            return;
        }
        else
        {
            int* newMarks = new int[amountMarks];
            for (int i = 0; i < amountMarks; i++)
            {
                newMarks[i] = marks[i];
            }
            marks = new int[amountMarks + 1];
            for (int i = 0; i < amountMarks; i++)
            {
                marks[i] = newMarks[i];
            }
            delete[] newMarks;
            marks[amountMarks] = static_cast<int>(mark[0]) - 48;
            amountMarks++;
        }              
        inputString.erase(0, 2);        
    }
    std::cout << "Введите две даты или оставьте строку пустой, нажав ENTER: \n";    
    std::getline(std::cin, inputString);
    if (inputString.size() != 0)
        intervalBirthdays = new Date[2];    
    while (inputString.size() > 0)
    {        
        std::string date = inputString.substr(0, 10);        
        if ((IsItDate(&date)) && countBirthdays < 2)
        {
            intervalBirthdays[countBirthdays] = Date(&date);
            countBirthdays++;
        } else
        {            
            std::cout << "Была введена не дата в формате ДД.ММ.ГГГГ или больше, чем две даты\n";
            return;
        }
        inputString.erase(0, 11);        
    }
    for (int indexMark = 0; indexMark < amountMarks; indexMark++)
    {
        anyone = false;
        std::cout << "Статистика для оценки " << marks[indexMark] << ":\n";
        for (int numberStudent = 0; numberStudent < amountStudents; numberStudent++)
        {            
            if (Students[numberStudent].GetPercentageMarks(&marks[indexMark], intervalBirthdays))
            {
                std::cout << numberStudent + 1 << ". " << Students[numberStudent].GetSecondName() << ' ' << Students[numberStudent].GetName() << ' ' << Students[numberStudent].GetMiddleName() << '\n';
                anyone = true;
            }                        
        }
        if (!anyone)
            std::cout << "Список пуст\n";
    }
    

}


void Crypt()
{
    srand(time(NULL));
    char* pass = new char[64];
    for (int i = 0; i < 64; i++)
        switch (rand() % 3)
        {
        case 0:
            pass[i] = rand() % 10 + '0';
            break;
        case 1:
            pass[i] = rand() % 26 + 'A';
            break;
        case 2:
            pass[i] = rand() % 26 + 'a';
        }
    std::string command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -salt -in database.bin -out database.enc -pass pass:";
    for (int i = 0; i < 64; i++)
    {
        command += pass[i];        
    }   
    std::cout << '\n';
    system(command.c_str());
    if (remove("database.bin") != 0)
    {
        std::cout << "Не получилось удалить файл \"database.bin\" \n";
    }
    std::ofstream keyWrite; 
    keyWrite.open("key.bin", std::ios::out | std::ios::binary);
    if (keyWrite.is_open())
    {
        for (int i = 0; i < 64; i++)
        {
            keyWrite.write(&pass[i], sizeof(pass[i]));
        }
    }
    keyWrite.close();
    delete[] pass;
    command = "openssl\\bin\\openssl.exe pkeyutl -encrypt -inkey rsa.public -pubin -in key.bin -out key.enc";
    system(command.c_str());
    if (remove("key.bin") != 0)
    {
        std::cout << "Не удалось удалить файл \"key.bin\"\n";
    }
}


void Decrypt()
{    
    std::string command = "openssl\\bin\\openssl.exe rsautl -decrypt -inkey rsa.private -in key.enc -out key.bin";
    system(command.c_str());    
    if (remove("key.enc") != 0)
    {
        std::cout << "Не удалось удалить файл \"key.enc\" \n";
    }    
    char* password = new char[64];
    std::ifstream keyRead; 
    keyRead.open("key.bin", std::ios::in | std::ios::binary);
    if (keyRead.is_open())
    {
        for (int i = 0; i < 64; i++)
        {
            keyRead.read(&password[i], sizeof(password[i]));
        }
    }        
    keyRead.close();        
    if (remove("key.bin") != 0)
    {
        std::cout << "Не удалось удалить файл \"key.bin\"\n";
    }
    command = "openssl\\bin\\openssl.exe enc -aes-256-cbc -d -in database.enc -out database.bin -pass pass:";
    for (int i = 0; i < 64; i++)
    {
        command += password[i];
    }
    system(command.c_str());
    delete[] password;
    if (remove("database.enc") != 0)
    {
        std::cout << "Не удалось удалить файл \"database.enc\"\n";
    }    
}


void Menu()
{
    unsigned int amountStudents = 0, number = 0;
    int size = 0, amountStudentsToAdd = 0;
    char inputUser = '0';
    RecordStudent* Students = new RecordStudent[amountStudents];
    std::string input = "";
    std::ofstream binaryWrite;
    std::ifstream binaryRead;
    RecordStudent* students;
    std::string filename = "database.bin";
    while (inputUser)
    {
        std::cout << "Введите номер одной из возможных опций: \n";
        std::cout << "0 - выйти из программы. При завершении программы происходит шифрование \n";
        std::cout << "1 - добавить студентов(количество) \n";
        std::cout << "2 - удалить студента(номер) \n";
        std::cout << "3 - изменить информацию о студентах \n";
        std::cout << "4 - показать список студентов \n";
        std::cout << "5 - записать список студентов в файл(\"database.bin\") \n";
        std::cout << "6 - загрузить список студентов из файла(\"database.bin\") \n";
        std::cout << "7 - вывести студентов, у которых процент введенных оценок не выше 25% \n";
        std::cin >> inputUser;
        switch (static_cast<int>(inputUser))
        {
        case '1':
        {
            amountStudentsToAdd = GetAmountStudents();
            if (amountStudents == 0)
            {
                Students = new RecordStudent[amountStudentsToAdd];
                GetStudents(Students, &amountStudents, amountStudentsToAdd);
            } else {
                RecordStudent* students = new RecordStudent[amountStudents];
                for (int iterator = 0; iterator < amountStudents; iterator++)
                {
                    students[iterator] = Students[iterator];
                }
                Students = new RecordStudent[amountStudents + amountStudentsToAdd];
                for (int iterator = 0; iterator < amountStudents; iterator++)
                {
                    Students[iterator] = students[iterator];
                }
                GetStudents(Students, &amountStudents, amountStudentsToAdd);
                delete[] students;
            }
        }
            break;
        case '2':
        {
            ShowStudentsList(Students, amountStudents);
            number = GetNumberStudent(amountStudents);
            if ((number < 0) || (number == 0) || number > amountStudents)
            {
                std::cout << "Ошибка ввода. Нет студента с таким номером \n";
                break;
            }          
            RecordStudent* students = new RecordStudent[amountStudents];
            for (int iterator = 0; iterator < amountStudents; iterator++)
            {
                students[iterator] = Students[iterator];
            }
            Students = new RecordStudent[amountStudents - 1];
            DeleteStudent(Students, students, &amountStudents, number);
            delete[] students;
            break;            
        }
        case '3':
            ChangeInfo(Students, amountStudents);
            break;
        case '4':
            ShowStudentsList(Students, amountStudents);            
            break;
        case '5':
            binaryWrite.open(filename, std::ios::out | std::ios::binary);
            if (!binaryWrite)
            {
                std::cout << "Не получается открыть файл! \n";
                break;
            }
            for (unsigned int iterator = 0; iterator < amountStudents; iterator++)
            {
                binaryWrite.write((char*)&Students[iterator], sizeof(RecordStudent));
            }
            binaryWrite.close();
            break;
        case '6':
        {
            std::ifstream test("key.enc");
            if (test.good())
            {              
                test.close();
                Decrypt();
            }
            test.close();
            binaryRead.open(filename, std::ios::in | std::ios::binary);
            if (!binaryRead)
            {
                std::cout << "Не получается открыть файл! \n";
                break;
            }
            binaryRead.seekg(0, std::ios::end);
            amountStudents = binaryRead.tellg() / sizeof(RecordStudent);
            Students = new RecordStudent[amountStudents];
            binaryRead.seekg(0, std::ios::beg);
            for (unsigned int iterator = 0; iterator < amountStudents; iterator++)
            {
                binaryRead.read((char*)&Students[iterator], sizeof(RecordStudent));
            }
            binaryRead.close();
            break;
        }
        case '7':
            GetMarks(Students, amountStudents);
            break;            
        case '0':
            Terminate(Students);
            break;
        default:
            exit(0);
        }
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");    
    Menu();
    return 0;
}