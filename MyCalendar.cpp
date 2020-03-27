#include<bits/stdc++.h>
using namespace std;

// Checks if the year is leap or not

int leap(int year) {
    if (year%400==0) return 1;
    else if (year%4==0 && year%100!=0) return 1;
    else return 0;
}

//Returns the starting day of a year

int startingDay(int year) {
    int mao;
    if (year<=2001) {
        for (int i=year; i<2001; i++) {
            mao+=(leap(i)? 2:1);
        }
        mao=((mao%7==0)? 0: 7-mao%7);
    }
    else {
        for (int i=2001; i<year; i++) {
            mao+=(leap(i)?2:1);
        }
        mao=mao%7;
    }
    return (mao+2)%7;
}

// Meow

void must() {
    cout<<endl<<endl<<"By Morshed"<<endl;
}

// Returns month name based on month number

string findMonth(int n) {
    string months[]= {"January", "February", "March", "April",
                    "May", "June", "July", "August", "September",
                    "October", "November", "December"};
    return months[n];
}

// Returns number of days based on month's number

int daysOnMonth(int n, int year) {
    switch(n) {
        case 0:
            return 31;
        case 1:
            if (leap(year)) return 29;
            return 28;
        case 2:
            return 31;
        case 3:
            return 30;
        case 4:
            return 31;
        case 5:
            return 30;
        case 6:
            return 31;
        case 7:
            return 31;
        case 8:
            return 30;
        case 9:
            return 31;
        case 10:
            return 30;
        case 11:
            return 31;

    }
}

// Prints the whole calendar

void printCalendar(int year) {
    int meow=startingDay(year);
    cout<<endl<<"               Year: "<<year<<endl<<endl;
    for(int i=0; i<12; i++) {
        string monthName=findMonth(i);
        int bm, days=daysOnMonth(i, year);
        cout<<"*************** "<<monthName<<" ***************\n"<<endl;
        cout<<"  Sat  Sun  Mon  Tue  Wed  Thu  Fri"<<endl;
        for(bm=0; bm<meow; bm++) {
            cout<<"     ";
        }
        for(int j=1; j<=days; j++) {
            cout<<setw(5)<<j;
            if(++bm>6) {
                bm=0;
                cout<<endl;
            }
        }
        cout<<endl<<endl;

        meow=bm;
    }
    must();
}
int main() {
    int year;
    cin>>year;
    printCalendar(year);
    return 0;
}
