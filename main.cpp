#include <bits/stdc++.h>
using namespace std;

class Berth {
public:
    int berthNumber;
    string type;
    bool isAvailable;
    string passengerName;
    int age;
    long long pnr;

    Berth()
        : berthNumber(0), type(""), isAvailable(true), passengerName(""), age(0), pnr(0) {}

    Berth(int num, string ty, bool aval = true)
        : berthNumber(num), type(ty), isAvailable(aval), passengerName(""), age(0), pnr(0) {}
};

class Passenger {
public:
    string name;
    int age;
    string preference;

    Passenger() : name(""), age(0), preference("") {}

    Passenger(string n, int a, string p)
        : name(n), age(a), preference(p) {}
};

class Ticket {
public:
    int PNR;
    string status;
    int berthNumber;
    string berthType;
    int age;
    string passengerName;

    Ticket() : PNR(0), status(""), berthNumber(-1), berthType(""), age(0), passengerName("") {}

    Ticket(int pnr, const string& stat, int berthNo, const string& bType, int ag, const string& name)
        : PNR(pnr), status(stat), berthNumber(berthNo), berthType(bType), age(ag), passengerName(name) {}

    void print() {
        cout << PNR << "\t" 
             << (berthNumber == -1 ? "N/A" : to_string(berthNumber)) << "\t"
             << status << "\t"
             << berthType << "\t"
             << passengerName << "\t"
             << age << endl;
    }
};

