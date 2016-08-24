#ifndef DATE_H
#define DATE_H

#include <string>
#include <iostream>

class Date
{
    int year,month,day;
    int dayOfMonth(int year,int month) const ;
    int toInt() const ;
public:
    Date();
    Date(int year,int month,int day);
    int getYear();
    int getMonth();
    int getDay();
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    bool isLeapyear();
    static bool isLeapyear(int year);
    void Display();

    friend Date operator + (const int v,const Date a);
    friend Date operator + (const Date a,const int v);
    friend Date operator +=(Date &a,const int v);
    friend Date operator ++(Date &a);
    friend Date operator ++(Date &a,int);
    friend Date operator - (const Date a,const int v);
    friend int operator - (const Date a,const Date b);
    friend Date operator -=(Date &a,const int v);
    friend Date operator --(Date &a);
    friend Date operator --(Date &a,int);
    friend bool operator > (const Date a,const Date b);
    friend bool operator >=(const Date a,const Date b);
    friend bool operator < (const Date a,const Date b);
    friend bool operator <=(const Date a,const Date b);
    friend bool operator ==(const Date a,const Date b);
    friend bool operator !=(const Date a,const Date b);
    friend std::ostream & operator <<(std::ostream &os,const Date &d);
    friend std::istream & operator >>(std::istream &is,Date &d);
};

#endif // DATE_H
