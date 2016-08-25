#include "readerinfo.h"

ReaderInfo::ReaderInfo(std::__1::string id, std::__1::string name, ReaderInfo::Departments department, ReaderInfo::ReaderType type){
    this->id = id;
    this->name = name;
    this->department =  department;
    this->type = type;
}
std::string ReaderInfo::getId() {
    return id;
}
void ReaderInfo::setId(std::string id) {
    this->id = id;
}
std::string ReaderInfo::getName() {
    return name;
}
void ReaderInfo::setName(std::string name) {
    this->name = name;
}
ReaderInfo::Departments ReaderInfo::getDepartment() {
    return department;
}
void ReaderInfo::setDepartment(ReaderInfo::Departments department) {
    this->department = department;
}
ReaderInfo::ReaderType ReaderInfo::getType() {
    return type;
}
void ReaderInfo::setType(ReaderInfo::ReaderType type) {
    this->type = type;
}

void ReaderInfo::display(){
    std::cout<<this->id<<std::endl;
}
