#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class Tire {
public: 
    int leftFront;
    int leftBack;
    int rightFront;
    int rightBack;
};

class Powertrain {
public:
    int horsepower;
    int topSpeed;
    int averageSpeed;
    int lowestSpeed;
};

class Car {
public:
    std::string make;
    double mpg;
    double mpgCaution;
    double fuelLevel;
    int horsepower;
    double speed;
    Powertrain engines;
    Tire tires;
    double totalLapTime; // Added to store total lap time for each car
};

class Track {
public:
    double distance;
};

class Race {
public:
    int laps;
};

bool compareCars(const Car& car1, const Car& car2) {
    return car1.totalLapTime < car2.totalLapTime;
}

int main() {
    const int numCars = 20;

    // Create an array of cars
    Car cars[numCars];

    // Initialize each car with the same values
    for (int i = 0; i < numCars; ++i) {
        cars[i].make = "Ford";
        cars[i].fuelLevel = 22;
        cars[i].mpg = 4;
        cars[i].mpgCaution = 16;
        cars[i].horsepower = 750;
        cars[i].tires.leftFront = 40;
        cars[i].tires.leftBack = 40;
        cars[i].tires.rightFront = 40;
        cars[i].tires.rightBack = 40;
        cars[i].totalLapTime = 0; // Initialize total lap time to 0
        cars[i].engines.horsepower = 550;
        cars[i].engines.averageSpeed = 180;
        cars[i].engines.topSpeed = 205;
        cars[i].engines.lowestSpeed = 170;
    }

    // The rest of your code remains the same, using the cars array instead of car1

    Track track1;
    track1.distance = 2;

    Race race1;
    race1.laps = 200;

    bool caution = false;
    double lapTime;
    double totalTime;

    // Set up a random number generator
    std::random_device rd;
    std::default_random_engine engine(rd());
    int topSpeedFlux;
    int lowSpeedFlux;
    // race loop
    for (int lap = 1; lap <= race1.laps; lap++) {
        std::vector<Car> standings;
        // for every car in race
        for (int i = 0; i < numCars; ++i) {
            topSpeedFlux = cars[i].engines.topSpeed - cars[i].engines.averageSpeed;
            lowSpeedFlux = cars[i].engines.averageSpeed - cars[i].engines.lowestSpeed;
            std::uniform_real_distribution<double> speedFluctuation(-lowSpeedFlux, topSpeedFlux);
            // lap time based on 175 - 185 mph
            lapTime = track1.distance / (cars[i].engines.averageSpeed + speedFluctuation(engine)) * 3600;
            // if caution - better mpg
            if (caution == false)
                cars[i].fuelLevel -= track1.distance / cars[i].mpg;
            else
                cars[i].fuelLevel -= track1.distance / cars[i].mpgCaution;
            // pitstop loop
            if (cars[i].fuelLevel <= 0 || (cars[i].fuelLevel - track1.distance / cars[i].mpg) <= 0) {
                //std::cout << "pit stop for car " << i+1 << std::endl;
                cars[i].fuelLevel = 22;
                cars[i].tires.leftFront = 40;
                cars[i].tires.leftBack = 40;
                cars[i].tires.rightFront = 40;
                cars[i].tires.rightBack = 40;
                lapTime += 14;
            }

            std::cout << "Car " << i+1 << ": " << lapTime << " second lap time" << std::endl;
            totalTime += lapTime / 3600;

            cars[i].totalLapTime += lapTime;
            standings.push_back(cars[i]);
        }

        // Sort the standings based on total lap time
        std::sort(standings.begin(), standings.end(), compareCars);

        /* Print standings after each lap
        std::cout << "Standings after Lap " << lap << ":" << std::endl;
        for (int i = 0; i < numCars; ++i) {
            std::cout << "Car " << i+1 << ": Total Lap Time - " << standings[i].totalLapTime << " hours" << std::endl;
        } */
    }
    // print total standings
    std::cout << "Final Standings:" << std::endl;
    std::sort(cars, cars + numCars, compareCars);
    for (int i = 0; i < numCars; ++i) {
        std::cout << "Car " << i+1 << ": Total Lap Time - " << cars[i].totalLapTime / 3600 << " hours" << std::endl;
    }

    return 0;
}
