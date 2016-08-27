#include "readerinfo.h"

ReaderInfo::ReaderInfo(std::__1::string id, std::__1::string name, std::string department, std::string type){
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
std::string ReaderInfo::getDepartment() {
    return department;
}
void ReaderInfo::setDepartment(std::string department) {
    this->department = department;
}
std::string ReaderInfo::getType() {
    return type;
}
void ReaderInfo::setType(std::string type) {
    this->type = type;
}

void ReaderInfo::display(){
    std::cout<<this->id<<std::endl;
}
