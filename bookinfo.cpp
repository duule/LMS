#include "bookinfo.h"

BookInfo::BookInfo()
{

}
BookInfo::BookInfo(std::string id, std::string ztId, std::string name, std::string author, std::string press, Date dateOfPublication, std::string ISBN, std::string editionNumber, double price){
    this->id = id;
    this->ztId = ztId;
    this->name = name;
    this->author = author;
    this->press = press;
    this->dateOfPublication =dateOfPublication;
    this->ISBN = ISBN;
    this->editionNumber = editionNumber;
    this->price = price;
}

std::string BookInfo::getId() {
    return this->id;
}
void BookInfo::setId(std::string id) {
    this->id = id;
}
std::string BookInfo::getZtId() {
    return this->ztId;
}
void BookInfo::setZtId(std::string ztId) {
    this->ztId = ztId;
}
std::string BookInfo::getName() {
    return this->name;
}
void BookInfo::setName(std::string name) {
    this->name = name;
}
std::string BookInfo::getAuthor() {
    return this->author;
}
void BookInfo::setAuthor(std::string author) {
    this->author = author;
}
std::string BookInfo::getPress() {
    return this->press;
}
void BookInfo::setPress(std::string press) {
    this->press = press;
}
Date BookInfo::getDateOfPublication() {
    return this->dateOfPublication;
}
void BookInfo::setDateOfPublication(Date dateOfPublication) {
    this->dateOfPublication = dateOfPublication;
}
std::string BookInfo::getISBN() {
    return this->ISBN;
}
void BookInfo::setISBN(std::string iSBN) {
    ISBN = iSBN;
}
std::string BookInfo::getEditionNumber() {
    return this->editionNumber;
}
void BookInfo::setEditionNumber(std::string editionNumber) {
    this->editionNumber = editionNumber;
}
double BookInfo::getPrice() {
    return this->price;
}
void BookInfo::setPrice(double price) {
    this->price = price;
}
