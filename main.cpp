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