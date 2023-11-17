#pragma once
#include <cstdint>
#include <string>
#include <vector>

enum class MAKE { NONE, FORD, CHEVY, TOYOTA };
enum class BUDGET { NONE, LOW, MID, HIGH };

struct DriverInfo {
    std::string name;
    static int totalDrivers;
    int number;
    DriverInfo() : name("Unknown"), number(0) {}
    DriverInfo(std::string n, int num) : name(n), number(num) {
        totalDrivers++;
    }

    static int getTotalDrivers() {
        return totalDrivers;
    }
};

int DriverInfo::totalDrivers = 0; 

struct Team {
    Team(std::string name, MAKE m, BUDGET b, std::vector<DriverInfo> drivers) :
        Name(name), carMake(m), teamBudget(b), Drivers(drivers) {}
    std::string Name = "unnamed";
    MAKE carMake = MAKE::NONE;
    BUDGET teamBudget = BUDGET::NONE;
    std::vector<DriverInfo> Drivers;

    std::string getMake(MAKE make) {
        switch (make) {
            case MAKE::NONE: return "NONE";
            case MAKE::FORD: return "Ford";
            case MAKE::CHEVY: return "Chevy";
            case MAKE::TOYOTA: return "Toyota";
            default: return "UNKNOWN";
        }
    }
    std::string getBudget(BUDGET budget) {
        switch (budget) {
            case BUDGET::NONE: return "NONE";
            case BUDGET::LOW: return "Low";
            case BUDGET::MID: return "Medium";
            case BUDGET::HIGH: return "High";
            default: return "UNKNOWN";
        }
    }
    std::string getDrivers(const Team& team) {
        if (Name != team.Name) {
            return "No drivers found for this team!";
        }
        std::string driversInfo;
        for (const auto& driver : Drivers) {
            driversInfo += "Name: " + driver.name + ", Number: " + std::to_string(driver.number) + "\n";
        }
        return driversInfo;
    }
};

class Hendrick : public Team {
public:
    Hendrick() : Team("Hendrick Motorsport", MAKE::CHEVY, BUDGET::HIGH,
    {{"Chase Elliott", 9}, {"Alex Bowman", 48}, {"William Byron", 24}}) {}
};

class JoeGibbs : public Team {
public: 
    JoeGibbs() : Team("Joe Gibbs Racing", MAKE::TOYOTA, BUDGET::HIGH,
    {{"Denny Hamlin", 11}, {"Martin Truex Jr", 19}}) {}
};

