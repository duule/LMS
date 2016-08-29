#ifndef TOOLS_H
#define TOOLS_H

#include <QDate>
#include <QDebug>

class Tools
{
public:
    Tools();
    static int getDistanceOfDate(QDate a,QDate b){
        QString dateA = a.toString("yyyy-MM-dd");
        QString dateB = b.toString("yyyy-MM-dd");
        int year_A = dateA.left(4).toInt();
        int year_B = dateB.left(4).toInt();
        int month_A = dateA.mid(5,2).toInt();
        int month_B = dateB.mid(5,2).toInt();
        int day_A = dateA.right(2).toInt();
        int day_B = dateB.right(2).toInt();
        if(year_A == year_B && month_A == month_B){
            return day_A>day_B ? day_A-day_B : day_B-day_A;
        }
        else if(year_A == year_B){
            int d1 = getTotalDaysInYear(year_A,month_A,day_A);
            int d2 = getTotalDaysInYear(year_B,month_B,day_B);
            return d1>d2 ? d1-d2 : d2-d1;
        }
        else {
            if(year_A > year_B){
                int temp;
                temp = year_A;year_A = year_B;year_B = temp;
                temp = month_A;month_A = month_B;month_B = temp;
                temp = day_A;day_A = day_B;day_B = temp;
            }
            int d1,d2,d3;
            if(isLeapYear(year_A))d1 = 366 - getTotalDaysInYear(year_A,month_A,day_A);
            else d1 = 365 - getTotalDaysInYear(year_A,month_A,day_A);
            d2 = getTotalDaysInYear(year_B,month_B,day_B);
            d3 = 0;
            for (int year = year_A+1; year < year_B; year++){
                if (isLeapYear(year))d3 += 366;
                else d3 += 365;
            }
            return d1+d2+d3;
        }
    }
private:
    static int getTotalDaysInYear(int year,int month, int day){
        int DAY[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if(isLeapYear(year)) DAY[1] = 29;
        for(int i = 0 ; i<month-1 ; i++){
            day += DAY[i];
        }
        return day;
    }
    static bool isLeapYear(int year){
        return ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0);
    }
};

#endif // TOOLS_H
