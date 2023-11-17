#pragma once
#include "team.h"
#include <string>

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
    DriverInfo driver;
    double mpg;
    double mpgCaution;
    double fuelLevel;
    int horsepower;
    double speed;
    Powertrain engines;
    Tire tires;
    double totalLapTime; // Added to store total lap time for each car
};
