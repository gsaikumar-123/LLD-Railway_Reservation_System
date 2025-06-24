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

class Coach {
public:
    unordered_map<int, Berth> berths;
    unordered_map<string, set<int>> typeMap;
    queue<Ticket> RAC, WL;
    vector<Ticket> confirmedTickets;
    map<int, vector<Ticket>> allTickets;
    int RAC_LIMIT = 4;
    int WL_LIMIT = 2;
    int nextPNR = 1000;

    Coach() {
        typeMap["LB"] = {1, 4, 9, 12};
        typeMap["MB"] = {2, 5, 10, 13};
        typeMap["UB"] = {3, 6, 11, 14};
        typeMap["SU"] = {8, 16};

        for (auto &pair : typeMap) {
            for (int seat : pair.second) {
                berths[seat] = Berth(seat, pair.first);
            }
        }
        for (int i = 1; i <= 4; ++i) {
            berths[100 + i] = Berth(-1, "RAC" + to_string(i));
        }
    }

    void printAllBerths() {
	    cout << "All Berths Status:\n";
	    for (const auto& pair : berths) {
	        const Berth& berth = pair.second;
	        cout << "Berth No: " << berth.berthNumber << ", Type: " << berth.type << "\n";
	        
	        if (!berth.isAvailable) {
	            cout << "  PNR: " << berth.pnr
	                 << ", Name: " << berth.passengerName
	                 << ", Age: " << berth.age << "\n";
	        }
			else {
	            cout << "  Status: Available\n";
	        }
	    }
	}	
};

