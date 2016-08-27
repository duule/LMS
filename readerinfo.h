#ifndef READERINFO_H
#define READERINFO_H

#include <iostream>

class ReaderInfo
{
private:
    std::string id;
    std::string name;
    std::string department;
    std::string type;
public:
    ReaderInfo(std::string id, std::string name, std::string department, std::string type);

    std::string getId();
    void setId(std::string id);
    std::string getName();
    void setName(std::string name);
    std::string getDepartment();
    void setDepartment(std::string department);
    std::string getType();
    void setType(std::string type);

    void display();
};

#endif // READERINFO_H
