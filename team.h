#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "car.h"

class Tire {
public: 
    int leftFront;
    int leftBack;
    int rightFront;
    int rightBack;

    int tireWear(int tire){
        tire -= 1;
        return tire;
    }
};

class Powertrain {
public:
    int horsepower;
    int topSpeed;
    int averageSpeed;
    int lowestSpeed;
    int cautionSpeed;
};

class Car {
public:
    double mpg;
    double mpgCaution;
    double fuelLevel;
    double speed;
    Powertrain engines;
    Tire tires;
    double totalLapTime;
};

enum class MAKE { NONE, FORD, CHEVY, TOYOTA };
enum class BUDGET { NONE, LOW, MID, HIGH };

struct DriverInfo {
    std::string name;
    int number;
    Car car;
    DriverInfo() : name("Unknown"), number(0), car() {}
    // Constructor with parameters
    DriverInfo(std::string n, int num, const Car& c) : name(n), number(num), car(c) {
        car.fuelLevel = 22;
        car.mpg = 4.0;
        car.mpgCaution = 16;
        car.tires.leftFront = 40;
        car.tires.leftBack = 40;
        car.tires.rightFront = 40;
        car.tires.rightBack = 40;
        car.totalLapTime = 0;
        car.engines.horsepower = 550;
        car.engines.averageSpeed = 190;
        car.engines.topSpeed = 15;
        car.engines.lowestSpeed = -20;
        car.engines.cautionSpeed = 70;
    }
};

struct Team {
    Team(std::string name, MAKE m, BUDGET b, std::vector<DriverInfo> drivers, int numDrivers) :
    Name(name), carMake(m), teamBudget(b), Drivers(drivers), NumDrivers(numDrivers) {
        if (teamBudget == BUDGET::LOW) {
                for (auto& driver : Drivers) {
                    driver.car.engines.averageSpeed -= 1;
                }
        }
        else if (teamBudget == BUDGET::HIGH) {
                for (auto& driver : Drivers) {
                    driver.car.engines.averageSpeed += 2;
                }
        }
    }
    std::string Name = "unnamed";
    MAKE carMake = MAKE::NONE;
    BUDGET teamBudget = BUDGET::NONE;
    std::vector<DriverInfo> Drivers;
    int NumDrivers = 0;
    
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
                    {
                        {"Chase Elliott", 9, Car()},
                        {"Alex Bowman", 48, Car()},
                        {"William Byron", 24, Car()}
                    }, 3) {}
};

class JoeGibbs : public Team {
public:
    JoeGibbs() : Team("Joe Gibbs Racing", MAKE::TOYOTA, BUDGET::HIGH,
                    {
                        {"Denny Hamlin", 11, Car()},
                        {"Martin Truex Jr", 19, Car()}
                    }, 2) {}
};

class TwentyThree : public Team {
public:
    TwentyThree() : Team("23XI Racing", MAKE::TOYOTA, BUDGET::MID, 
        {
            {"Bubba Wallace", 23, Car()},
            {"Tyler Reddick", 45, Car()}
        }, 2) {}
};

class Trackhouse : public Team {
public:
    Trackhouse() : Team("Trackhouse Racing", MAKE::FORD, BUDGET::LOW,
                    {
                        {"Ross Chastain", 1, Car()},
                        {"Daniel Suarez", 99, Car()}
                    }, 2) {}
};

/*
std::vector<Driver> allDrivers = {
        {"Ross Chastain", 1, "Chevy", "TRACKHOUSE RACING TEAM"},
        {"Kyle Larson", 5, "Chevy", "Hendrick Motorsports"},
        {"Kyle Busch", 8, "Chevy", "Richard Childress Racing"},
        {"Chase Elliott", 9, "Chevy", "Hendrick Motorsports"},
        {"Aric Almirola", 10, "Ford", "Stewart-Haas Racing"},
        {"Denny Hamlin", 11, "Toyota", "Joe Gibbs Racing"},
        {"Ryan Blaney", 12, "Ford", "Team Penske"},
        {"Chase Brisco", 14, "Ford", "Steward-Haas Racing"},
        {"Ryan Newman", 51, "Ford", "RICK WARE RACING"},
        {"AJ Allmendinger", 16, "Chevy", "Kaulig Racing"},
        {"Chris Buescher", 17, "Chevy", "RFK Racing"},
        {"Martin Truex Jr.", 19, "Toyota", "Joe Gibbs Racing"},
        {"Austin Cindric", 2, "Ford", "Team Penske"},
        {"Christopher Bell", 20, "Toyota", "Joe Gibbs Racing"},
        {"Joey Logano", 22, "Ford", "Team Penske"},
        {"Bubba Wallace", 23, "Toyota", "23XI Racing"},
        {"William Byron", 24, "Chevy", "Hendrick Motorsports"},
        {"Kevin Harvick", 4, "Ford", "Steward-Haas Racing"},
        {"Austin Dillon", 3, "Chevy", "Richard Childress Racing"},
        {"Michael McDowell", 34, "Ford", "Front Row Motorsports"},
        {"Ryan Preece", 41, "Ford", "Steward-Haas Racing"},
        {"Noah Gragson", 42, "Chevy", "Legacy Motor Club"},
        {"Erik Jones", 43, "Chevy", "Legacy Motor Club"},
        {"Tyler Reddick", 45, "Toyota", "23XI Racing"},
        {"Ricky Stenhouse Jr.", 47, "Chevy", "JTG Daugherty Racing"},
        {"Alex Bowman", 48, "Chevy", "Hendrick Motorsports"},
        {"Cole Custer", 51, "Ford", "RICK WARE RACING"},
        {"Ty Gibbs", 54, "Toyota", "Joe Gibbs Racing"},
        {"Brad Keselowski", 6, "Ford", "RFK Racing"},
        {"Ty Dillon", 77, "Chevy", "Spire Motorsports"},
        {"Anthony Alfredo", 78, "Ford", "Live Fast Motorsports"},
        {"Daniel Suarez", 99, "Chevy", "TRACKHOUSE RACING TEAM"}
    }; 
*/
