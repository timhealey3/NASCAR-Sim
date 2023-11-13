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
    int number;
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

    std::vector<std::string> makes = {"Ford", "Toyota", "Chevy"};

    // Initialize each car with random make
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> makeDist(0, makes.size() - 1);

    // Initialize each car with the same values
    for (int i = 0; i < numCars; ++i) {
        cars[i].make = makes[makeDist(gen)];
        cars[i].number = i;
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
    std::cout << "Choose What Track you would like to race on: " << std::endl;
    std::cout << "<----------------------------------------------->" << std::endl;
    std::cout << "1. Daytona International Speedway" << std::endl;
    std::cout << "2. Bristol Motor Speedway" << std::endl;
    std::cout << "3. Michigan International Speedway" << std::endl;
    std::cout << "4. Phoenix Raceway" << std::endl;
    std::cout << "5. Exit Simulation" << std::endl;
    int trackChoice = 3;
    //std::cin >> trackChoice;

    switch (trackChoice) {
        case 1:
            std::cout << "Invalid choice. Exiting Simulation." << std::endl;
            return 1;
        case 2:
            std::cout << "Invalid choice. Exiting Simulation." << std::endl;
            return 1;
        case 3:
            track1.distance = 2.0; // Set distance for Michigan
            break;
        case 4:
            std::cout << "Invalid choice. Exiting Simulation." << std::endl;
            return 1;
        case 5:
            std::cout << "Exiting Simulation." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Exiting Simulation." << std::endl;
            return 1;
    }

    Race race1;
    race1.laps = 200;

    bool caution = false;
    double lapTime;
    double totalTime;

    // Set up a random number generator
    std::random_device rdd;
    std::default_random_engine engine(rdd());
    double targetCrashesPerRace = 5.0;
    double overallCrashProbability = targetCrashesPerRace / race1.laps / numCars;
    std::vector<bool> hasCrashed(numCars, false);
    int topSpeedFlux;
    int lowSpeedFlux;
    std::vector<Car> standings;
    std::vector<Car> crashedCars;
    // race loop
    for (int lap = 1; lap <= race1.laps; lap++) {
        standings.clear();
        crashedCars.clear();
        // for every car in race
        for (int i = 0; i < numCars; ++i) {
            if (hasCrashed[i]) {
                crashedCars.push_back(cars[i]);
                continue;
            }
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
                cars[i].engines.topSpeed = 205;
            }
            else {
                cars[i].tires.leftFront = std::max(0, cars[i].tires.leftFront - 1);
                cars[i].tires.leftBack = std::max(0, cars[i].tires.leftBack - 1);
                cars[i].tires.rightFront = std::max(0, cars[i].tires.rightFront - 1);
                cars[i].tires.rightBack = std::max(0, cars[i].tires.rightBack - 1);
                // Decrease totalSpeed by 0.1 for every point lost
                cars[i].engines.topSpeed -= 0.1;
            }

            if (std::bernoulli_distribution(overallCrashProbability)(engine)) {
            // Car crashes or spins
            std::cout << "Car #" << cars[i].number << " (" << cars[i].make << ") crashed or spun during Lap " << lap << "!" << std::endl;
            hasCrashed[i] = true;
            //lapTime += 30; // Adjust lap time for the crash
        }

            
            //std::cout << "Car " << i+1 << ": " << lapTime << " second lap time" << std::endl;
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

    // Print finished cars
    std::sort(standings.begin(), standings.end(), compareCars);
    for (int i = 0; i < standings.size(); ++i) {
        std::cout << i + 1 << ": Car #" << standings[i].number << " " << standings[i].make << " Total Lap Time - " << standings[i].totalLapTime / 3600 << " hours" << std::endl;
    }

    // Print crashed cars as Did Not Finish
    for (int i = 0; i < crashedCars.size(); ++i) {
        std::cout << "DNF: Car #" << crashedCars[i].number << " " << crashedCars[i].make << std::endl;
    }

    return 0;
}
