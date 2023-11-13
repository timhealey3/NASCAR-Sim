#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

class Driver {
public:
    std::string name;
    int carNumber;
    std::string make;
    std::string team;
};
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
    int cautionSpeed;
};

class Car {
public:
    std::string make;
    std::string name;
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
    // Create an array of cars
    Car cars[numCars];

    std::vector<std::string> makes = {"Ford", "Toyota", "Chevy"};

    // Initialize each car with random make
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> makeDist(0, makes.size() - 1);

    // Initialize each car with the same values
    for (int i = 0; i < numCars; ++i) {
        cars[i].make = allDrivers[i].make;
        cars[i].number = allDrivers[i].carNumber;
        cars[i].name = allDrivers[i].name;
        cars[i].fuelLevel = 22;
        cars[i].mpg = 4;
        cars[i].mpgCaution = 16;
        cars[i].horsepower = 750;
        cars[i].tires.leftFront = 40;
        cars[i].tires.leftBack = 40;
        cars[i].tires.rightFront = 40;
        cars[i].tires.rightBack = 40;
        cars[i].totalLapTime = 0;
        cars[i].engines.horsepower = 550;
        cars[i].engines.averageSpeed = 180;
        cars[i].engines.topSpeed = 205;
        cars[i].engines.lowestSpeed = 170;
        cars[i].engines.cautionSpeed = 70;
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
    //int trackChoice = 3;
    int trackChoice;
    std::cin >> trackChoice;

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
    int cautionCount = 0;
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
            // if caution - better mpg
            if (caution == false){
                lapTime = track1.distance / (cars[i].engines.averageSpeed + speedFluctuation(engine)) * 3600;
                cars[i].fuelLevel -= track1.distance / cars[i].mpg;
            }
            else
            {
                lapTime = track1.distance / cars[i].engines.cautionSpeed * 3600;
                cars[i].fuelLevel -= track1.distance / cars[i].mpgCaution;
                cautionCount -= 1;
                if (cautionCount == 1){
                    caution = false;
                }
            }
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
                // Decrease totalSpeed by 0.1 for tirewear
                cars[i].engines.topSpeed -= 0.1;
            }

            if (std::bernoulli_distribution(overallCrashProbability)(engine) && caution == false) {
                // Car crashes or spins
                std::cout << "Car #" << cars[i].number << " (" << cars[i].make << ") crashed or spun during Lap " << lap << "!" << std::endl;
                if (std::bernoulli_distribution(0.5)(engine)) {
                    // 50% chance the car is completely out of the race
                    std::cout << "Car #" << cars[i].number << " (" << cars[i].make << ") is out of the race!" << std::endl;
                    hasCrashed[i] = true;
                    cautionCount = 10;
                } else {
                    // 50% chance the car continues in the race
                    std::cout << "Car #" << cars[i].number << " (" << cars[i].make << ") continues in the race." << std::endl;
                    lapTime += 30;
                    cautionCount = 5;
                } 
                caution = true;
            }
            
            //std::cout << "Car " << i+1 << ": " << lapTime << " second lap time" << std::endl;
            totalTime += lapTime / 3600;

            cars[i].totalLapTime += lapTime;
            standings.push_back(cars[i]);
        }
        // Sort the standings based on total lap time
        //std::sort(standings.begin(), standings.end(), compareCars);
        /*Print standings after each lap
        std::cout << "Standings after Lap " << lap << ":" << std::endl;
        for (int i = 0; i < numCars; ++i) {
            std::cout << "Car " << i+1 << ": Total Lap Time - " << standings[i].totalLapTime << " hours" << std::endl;
        } */
    }
    // print total standings
    std::cout << "Final Standings:" << std::endl;

    // Print finished cars
    std::sort(standings.begin(), standings.end(), compareCars);
    for (std::vector<Car>::size_type i = 0; i < standings.size(); ++i) {
        std::cout << i + 1 << ": #" << standings[i].number << " " << standings[i].name << " " << standings[i].make << " Total Time - " << standings[i].totalLapTime / 3600 << " hr" << std::endl;
    }

    // Print crashed cars as Did Not Finish
    for (std::vector<Car>::size_type i = 0; i < crashedCars.size(); ++i) {
        std::cout << "DNF: #" << crashedCars[i].number << " " << crashedCars[i].name << " " << crashedCars[i].make << std::endl;
    }

    return 0;
}
