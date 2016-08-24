#ifndef BOOKINFO_H
#define BOOKINFO_H

#include "date.h"
#include <iostream>

class BookInfo
{
    std::string id;
    std::string ztId;
    std::string name;
    std::string author;
    std::string press;
    Date dateOfPublication;
    std::string ISBN;
    std::string editionNumber;
    double price;
public:
    BookInfo();
    BookInfo(std::string id, std::string ztId, std::string name, std::string author, std::string press, Date dateOfPublication, std::string ISBN, std::string editionNumber, double price);

    std::string getId();
    void setId(std::string id);
    std::string getZtId();
    void setZtId(std::string ztId);
    std::string getName();
    void setName(std::string name);
    std::string getAuthor();
    void setAuthor(std::string author);
    std::string getPress();
    void setPress(std::string press);
    Date getDateOfPublication();
    void setDateOfPublication(Date dateOfPublication);
    std::string getISBN();
    void setISBN(std::string iSBN);
    std::string getEditionNumber();
    void setEditionNumber(std::string editionNumber);
    double getPrice();
    void setPrice(double price);


};

#endif // BOOKINFO_H
