#include "date.h"

int Date::dayOfMonth(int year,int month) const
{
    int day = 0;
    switch(month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            day = 31;
            break;
        case 4: case 6: case 9: case 11:
            day = 30;
            break;
        case 2:
            day = 28 + this->isLeapyear(year);
            break;
    }
    return day;
}
int Date::toInt() const
{
    int sum =0;
    for(int y=1;y<this->year;++y)
    {
        sum += 365+this->isLeapyear(y);
    }
    for(int m=1;m<this->month;++m)
        sum += this->dayOfMonth(this->year,m);
    sum += this->day;
    return sum;
}
Date::Date(){
    this->year = 1900;
    this->month = 1;
    this->day = 1;
}
Date::Date(int year,int month, int day){
    this->year = year;
    this->month = month;
    this->day = day;
    if((year<=0)||(month<=0 || month>12)||(day<=0 || day>dayOfMonth(year,month)))
    {
        this->year = 1900;
        this->month = this->day = 1;
    }
}
int Date::getYear(){
    return this->year;
}
int Date::getMonth(){
    return this->month;
}
int Date::getDay(){
    return this->day;
}
void Date::setYear(int year){
    if(year<=0) this->year = 1900;
    else this->year = year;
}
void Date::setMonth(int month){
    if(month<=0 || month>12) this->month = 1;
    else this->month = month;
}
void Date::setDay(int day){
    if(day<0 || day>this->dayOfMonth(this->year,this->month)){
        this->day = 1;
    }
    else this->day = day;
}

bool Date::isLeapyear() {
    return this->year%400?(this->year%100?(this->year%4?(false):(true)):(false)):true;
}
bool Date::isLeapyear(int year){
    return year%400?(year%100?(year%4?false:true):false):true;
}
void Date::Display(){
    std::cout<<year<<"-"<<month<<"-"<<day<<std::endl;
}

Date operator + (const int v,const Date a)
{
    Date d = a;
    if(v==0) return d;
    if(v>0)
    {
        d.day += v;
        while(d.day>d.dayOfMonth(d.year,d.month))
        {
            d.day -= d.dayOfMonth(d.year,d.month);
            d.month++;
            if(d.month>12)
            {
                ++d.year;
                d.month = 1;
            }
        }
        return d;
    }
    else
        return d-(-v);
}
Date operator +(const Date a,const int v)
{
    Date d = a;
    if(v==0) return d;
    if(v>0)
    {
        d.day += v;
        while(d.day>d.dayOfMonth(d.year,d.month))
        {
            d.day -= d.dayOfMonth(d.year,d.month);
            d.month++;
            if(d.month>12)
            {
                ++d.year;
                d.month = 1;
            }
        }
        return d;
    }
    else
        return d-(-v);
}
Date operator +=(Date &a,const int v)
{
    if(v==0) return a;
    if(v>0)
    {
        a.day+=v;
        while(a.day>a.dayOfMonth(a.year,a.month))
        {
            a.day -= a.dayOfMonth(a.year,a.month);
            a.month++;
            if(a.month>12)
            {
                ++a.year;
                a.month = 1;
            }
        }
        return a;
    }
    else
        return a-=(-v);
}
Date operator ++(Date &a)
{
    ++a.day;
    if(a.day>a.dayOfMonth(a.year,a.month))
    {
        a.day-=a.dayOfMonth(a.year,a.month);
        a.month++;
        if(a.month>12)
        {
            ++a.year;
            a.month = 1;
        }
    }
    return a;
}
Date operator ++(Date &a,int)
{
    Date d = a;
    ++a.day;
    if(a.day>a.dayOfMonth(a.year,a.month))
    {
        a.day-=a.dayOfMonth(a.year,a.month);
        a.month++;
        if(a.month>12)
        {
            ++a.year;
            a.month = 1;
        }
    }
    return d;
}
Date operator - (const Date a,const int v)
{
    Date d = a;
    if(v==0) return d;
    if(v>0)
    {
        d.day -= v;
        while(d.day<=0)
        {
            --d.month;
            if(d.month==0)
            {
                d.month=12;
                --d.year;
            }
            d.day+=d.dayOfMonth(d.year,d.month);
        }
        return d;
    }
    else
        return d+(-v);
}
int operator - (const Date a,const Date b)
{
    return a.toInt()-b.toInt();
}
Date operator -=(Date &a,const int v)
{
    if(v==0) return a;
    if(v>0)
    {
        a.day -= v;
        while(a.day<=0)
        {
            --a.month;
            if(a.month==0)
            {
                a.month=12;
                --a.year;
            }
            a.day+=a.dayOfMonth(a.year,a.month);
        }
        return a;
    }
    else
        return a+=(-v);
}
Date operator --(Date &a)
{
    --a.day;
    while(a.day<=0)
    {
        --a.month;
        if(a.month==0)
        {
            a.month = 12;
            --a.year;
        }
        a.day += a.dayOfMonth(a.year,a.month);
    }
    return a;
}
Date operator --(Date &a,int)
{
    Date d = a;
    --a.day;
    while(a.day<=0)
    {
        --a.month;
        if(a.month==0)
        {
            a.month = 12;
            --a.year;
        }
        a.day += a.dayOfMonth(a.year,a.month);
    }
    return d;
}
bool operator > (const Date a,const Date b)
{
    return a.toInt()>b.toInt();
}
bool operator >=(const Date a,const Date b)
{
    return a.toInt()>=b.toInt();
}
bool operator < (const Date a,const Date b)
{
    return a.toInt()<b.toInt();
}
bool operator <=(const Date a,const Date b)
{
    return a.toInt()<=b.toInt();
}
bool operator ==(const Date a,const Date b)
{
    return a.toInt()==b.toInt();
}
bool operator !=(const Date a,const Date b)
{
    return a.toInt()!=b.toInt();
}
std::ostream & operator <<(std::ostream &os,const Date &d)
{
    os<<d.year<<"-"<<d.month<<"-"<<d.day;
    return os;
}
std::istream & operator >>(std::istream &is,Date &d){
    Date old = d;
    is>>d.year>>d.month>>d.day;
    if((d.year<=0) ||(d.month>12||d.month<=0) || (d.day<=0||d.day>d.dayOfMonth(d.year,d.month)))
    {
        d = old;
        std::cout<<"Invalid number of date."<<std::endl;
    }
    return is;
}
