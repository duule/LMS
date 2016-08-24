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
    void setId(string id);
    std::string getZtId();
    void setZtId(string ztId);
    std::string getName();
    void setName(string name);
    std::string getAuthor();
    void setAuthor(string author);
    std::string getPress();
    void setPress(string press);
    Date getDateOfPublication();
    void setDateOfPublication(Date dateOfPublication);
    std::string getISBN();
    void setISBN(string iSBN);
    std::string getEditionNumber();
    void setEditionNumber(string editionNumber);
    double getPrice();
    void setPrice(double price);


};

#endif // BOOKINFO_H
