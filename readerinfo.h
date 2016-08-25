#ifndef READERINFO_H
#define READERINFO_H

#include <iostream>

class ReaderInfo
{
public:
    enum ReaderType{
        Undergraduate,
        Graduate,
        Teacher
    };
    enum Departments{
        计算机学院,
        后勤保障部,
        数学科学学院,
        教务处,
        经济管理学院
    };

private:
    std::string id;
    std::string name;
    ReaderInfo::Departments department;
    ReaderInfo::ReaderType type;
public:
    ReaderInfo(std::string id, std::string name, ReaderInfo::Departments department, ReaderInfo::ReaderType type);

    std::string getId();
    void setId(std::string id);
    std::string getName();
    void setName(std::string name);
    ReaderInfo::Departments getDepartment();
    void setDepartment(ReaderInfo::Departments department);
    ReaderInfo::ReaderType getType();
    void setType(ReaderInfo::ReaderType type);

    void display();
};

#endif // READERINFO_H
