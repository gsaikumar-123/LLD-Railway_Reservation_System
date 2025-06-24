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

    void printAllTickets() {
        cout << "PNR\tBerthNo\tStatus\tType\tName\tAge" << endl;
        
		for (auto &t : confirmedTickets){
        	t.print();
		}
        queue<Ticket> tmp = RAC;
        
		while (!tmp.empty()) { 
			tmp.front().print(); tmp.pop(); 
		}
        
		tmp = WL;
        
		while (!tmp.empty()) { 
			tmp.front().print(); tmp.pop(); 
		}
    }

    void bookTicket(vector<Passenger> group) {
	    int pnr = nextPNR++;
	    vector<Ticket> groupTickets;
	
	    for (Passenger& p : group) {
	        string assignedType = "";
	        int assignedSeat = -1;
	
	        if (p.preference != "null" && typeMap[p.preference].empty()) {
	            cout << "Preferred berth for " << p.name << " not available. Book any available berth? (yes/no): ";
	            string resp; cin >> resp;
	            if (resp != "yes") continue;
	            p.preference = "null";
	        }
	
	        if (p.preference == "null" && p.age >= 60 && !typeMap["LB"].empty()) {
	            assignedType = "LB";
	            assignedSeat = *typeMap["LB"].begin();
	        }
	        
	        else if (p.preference != "null" && !typeMap[p.preference].empty()) {
	            assignedType = p.preference;
	            assignedSeat = *typeMap[assignedType].begin();
	        }

	        else {
	            for (auto& pair : typeMap) {
	                if (!pair.second.empty()) {
	                    assignedType = pair.first;
	                    assignedSeat = *pair.second.begin();
	                    break;
	                }
	            }
	        }
	
	        if (assignedSeat != -1) {
	            typeMap[assignedType].erase(assignedSeat);
	            berths[assignedSeat].isAvailable = false;
	            Ticket t(pnr, "Confirmed", assignedSeat, assignedType, p.age, p.name);
	            confirmedTickets.push_back(t);
	            groupTickets.push_back(t);
	        }
	        else if (RAC.size() < RAC_LIMIT) {
	            int racNo = 100 + RAC.size() + 1;
	            Ticket t(pnr, "RAC", -1, "RAC" + to_string(RAC.size() + 1), p.age, p.name);
	            RAC.push(t);
	            groupTickets.push_back(t);
	        }
	        else if (WL.size() < WL_LIMIT) {
	            Ticket t(pnr, "WL", -1, "WL", p.age, p.name);
	            WL.push(t);
	            groupTickets.push_back(t);
	        }
	        else {
	            cout << "No seat/RAC/WL available for " << p.name << "." << endl;
	        }
	    }
	
	    if (!groupTickets.empty()) {
	        allTickets[pnr] = groupTickets;
	        cout << "\nBooking done with PNR: " << pnr << " for " << groupTickets.size() << " passenger(s).\n";
	    } else {
	        cout << "\nNo tickets could be booked for the group.\n";
	    }
	}

    void cancelTicket(int pnr) {
	    bool found = false;
	
	    auto it = confirmedTickets.begin();
	    while (it != confirmedTickets.end()) {
	        if (it->PNR == pnr) {
	            found = true;
	
	            typeMap[it->berthType].insert(it->berthNumber);
	            berths[it->berthNumber].isAvailable = true;
	
	            if (!RAC.empty()) {
	                Ticket rac = RAC.front(); RAC.pop();
	                rac.status = "Confirmed";
	                rac.berthType = it->berthType;
	                rac.berthNumber = it->berthNumber;
	                confirmedTickets.push_back(rac);
	                allTickets[rac.PNR] = {rac};
	
	                if (!WL.empty()) {
	                    Ticket wl = WL.front(); WL.pop();
	                    wl.status = "RAC";
	                    wl.berthType = "RAC" + to_string(RAC.size() + 1);
	                    RAC.push(wl);
	                    allTickets[wl.PNR] = {wl};
	                }
	            }
	
	            it = confirmedTickets.erase(it);
	        } else {
	            ++it;
	        }
	    }
	
	    queue<Ticket> newRAC;
	    while (!RAC.empty()) {
	        Ticket t = RAC.front(); RAC.pop();
	        if (t.PNR == pnr) {
	            found = true;
	            if (!WL.empty()) {
	                Ticket wl = WL.front(); WL.pop();
	                wl.status = "RAC";
	                wl.berthType = "RAC" + to_string(RAC.size() + 1);
	                newRAC.push(wl);
	                allTickets[wl.PNR] = {wl};
	            }
	        } else {
	            newRAC.push(t);
	        }
	    }
	    RAC = newRAC;
	
	    queue<Ticket> newWL;
	    while (!WL.empty()) {
	        Ticket t = WL.front(); WL.pop();
	        if (t.PNR == pnr) {
	            found = true;
	        }
			else {
	            newWL.push(t);
	        }
	    }
	    WL = newWL;
	
	    auto itMap = allTickets.begin();
	    while (itMap != allTickets.end()) {
	        if (itMap->first == pnr) {
	            itMap = allTickets.erase(itMap);
	        } else {
	            ++itMap;
	        }
	    }
	
	    if (!found) {
	        cout << "PNR not found." << endl;
	    }
	}

};

