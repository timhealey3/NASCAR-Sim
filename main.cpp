#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "car.h"
#include "team.h"

class Track {
public:
    double distance;
};

class Race {
public:
    int laps;
};

bool compareDrivers(const DriverInfo& driver1, const DriverInfo& driver2) {
    return driver1.car.totalLapTime < driver2.car.totalLapTime;
}

int main() {
    // Create an array of cars
    Hendrick hend;
    JoeGibbs gibbs;
    Trackhouse thouse;
    TwentyThree twothree;
    RichardChildress rich;
    Penske penske;
    RickWare rickw;
    JTG jtg;
    LiveFast lf;
    // add all team.Drivers to vector
    std::vector<DriverInfo> allDrivers;
    allDrivers.insert(allDrivers.end(), hend.Drivers.begin(), hend.Drivers.end());
    allDrivers.insert(allDrivers.end(), gibbs.Drivers.begin(), gibbs.Drivers.end());
    allDrivers.insert(allDrivers.end(), thouse.Drivers.begin(), thouse.Drivers.end());
    allDrivers.insert(allDrivers.end(), twothree.Drivers.begin(), twothree.Drivers.end());
    allDrivers.insert(allDrivers.end(), rich.Drivers.begin(), rich.Drivers.end());
    allDrivers.insert(allDrivers.end(), penske.Drivers.begin(), penske.Drivers.end());
    allDrivers.insert(allDrivers.end(), rickw.Drivers.begin(), rickw.Drivers.end());
    allDrivers.insert(allDrivers.end(), jtg.Drivers.begin(), jtg.Drivers.end());
    allDrivers.insert(allDrivers.end(), lf.Drivers.begin(), lf.Drivers.end());
    size_t driverLength = allDrivers.size();

    for (int i = 0; i < driverLength; ++i) {
        std::cout << "#" << allDrivers[i].number << " " << allDrivers[i].name << " " << allDrivers[i].car.engines.averageSpeed << std::endl;
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
    double overallCrashProbability = targetCrashesPerRace / race1.laps / driverLength;
    std::vector<bool> hasCrashed(driverLength, false);
    std::vector<DriverInfo> standings;
    std::vector<DriverInfo> crashedCars;

    // race loop
    for (int lap = 1; lap <= race1.laps; lap++) {
        standings.clear();
        crashedCars.clear();
        // for every car in race
        for (int i = 0; i < driverLength; ++i) {
            if (hasCrashed[i]) {
                crashedCars.push_back(allDrivers[i]);
                continue;
            } 
            // lap time based on 170 <- 190 -> 205 mph
            std::uniform_real_distribution<double> speedFluctuation(allDrivers[i].car.engines.lowestSpeed, allDrivers[i].car.engines.topSpeed);
            
            // if caution - better mpg
            if (caution == false){
                lapTime = track1.distance / (allDrivers[i].car.engines.averageSpeed + speedFluctuation(engine)) * 3600;
                allDrivers[i].car.fuelLevel -= track1.distance / allDrivers[i].car.mpg;
            }
            else
            {
                lapTime = track1.distance / allDrivers[i].car.engines.cautionSpeed * 3600;
                allDrivers[i].car.fuelLevel -= track1.distance / allDrivers[i].car.mpgCaution;
                cautionCount -= 1;
                if (cautionCount == 1){
                    caution = false;
                }
            }
            // pitstop loop
            if (allDrivers[i].car.fuelLevel <= 0 || (allDrivers[i].car.fuelLevel - track1.distance / allDrivers[i].car.mpg) <= 0) {
                //std::cout << "pit stop for car " << i+1 << std::endl;
                allDrivers[i].car.fuelLevel = 22;
                allDrivers[i].car.tires.leftFront = 40;
                allDrivers[i].car.tires.leftBack = 40;
                allDrivers[i].car.tires.rightFront = 40;
                allDrivers[i].car.tires.rightBack = 40;
                lapTime += 14;
                allDrivers[i].car.engines.topSpeed = 205;
            }
            else {
                //std::cout << "tire before: " << allDrivers[i].car.tires.leftFront << std::endl;
                //allDrivers[i].car.tires.tireWear(allDrivers[i].car.tires.leftFront)
                allDrivers[i].car.tires.leftFront = allDrivers[i].car.tires.tireWear(allDrivers[i].car.tires.leftFront);
                //std::cout << "tire after: " << allDrivers[i].car.tires.leftFront << std::endl;
                //allDrivers[i].car.tires.leftFront = std::max(0, allDrivers[i].car.tires.leftFront - 1);
                allDrivers[i].car.tires.leftBack = allDrivers[i].car.tires.tireWear(allDrivers[i].car.tires.leftBack);
                allDrivers[i].car.tires.rightFront = allDrivers[i].car.tires.tireWear(allDrivers[i].car.tires.rightFront);
                allDrivers[i].car.tires.rightBack = allDrivers[i].car.tires.tireWear(allDrivers[i].car.tires.rightBack);
                // Decrease totalSpeed by 0.1 for tirewear
                allDrivers[i].car.engines.topSpeed -= 0.1;
            }

            if (std::bernoulli_distribution(overallCrashProbability)(engine) && caution == false) {
                // Car crashes or spins
                std::cout << "Car #" << allDrivers[i].number << " (" << allDrivers[i].name << ") crashed or spun during Lap " << lap << "!" << std::endl;
                if (std::bernoulli_distribution(0.5)(engine)) {
                    // 50% chance the car is completely out of the race
                    std::cout << "Car #" << allDrivers[i].number << " (" << allDrivers[i].name << ") is out of the race!" << std::endl;
                    hasCrashed[i] = true;
                    cautionCount = 10;

                } else {
                    // 50% chance the car continues in the race
                    std::cout << "Car #" << allDrivers[i].number << " (" << allDrivers[i].name << ") continues in the race." << std::endl;
                    lapTime += 30;
                    cautionCount = 5;
                }
                caution = true;
            }

            //std::cout << "Car " << i+1 << ": " << lapTime << " second lap time" << std::endl;
            totalTime += lapTime / 3600;

            allDrivers[i].car.totalLapTime += lapTime;
            standings.push_back(allDrivers[i]);
        }
        // Sort the standings based on total lap time
        std::sort(standings.begin(), standings.end(), compareDrivers);
        //Print standings after each lap
        /*
        std::cout << "Standings after Lap " << lap << ":" << std::endl;
        for (int i = 0; i < driverLength; ++i) {
            std::cout << i+1 << ". #" << standings[i].number << " " << standings[i].name << " : Total Lap Time - " << standings[i].car.totalLapTime << " hours" << " speed: " << std::endl;
        } */
    }
    //print total standings
    std::cout << "Final Standings:" << std::endl;

    // Print finished cars
    std::sort(standings.begin(), standings.end(), compareDrivers);
    for (std::vector<Car>::size_type i = 0; i < standings.size(); ++i) {
        std::cout << i + 1 << ": #" << standings[i].number << " " << standings[i].name << " - " << " Total Time - " << standings[i].car.totalLapTime / 3600 << " hr" << std::endl;
    }

    // Print crashed cars as Did Not Finish
    for (std::vector<Car>::size_type i = 0; i < crashedCars.size(); ++i) {
        std::cout << "DNF: #" << crashedCars[i].number << " " << crashedCars[i].name << " - " << crashedCars[i].car.totalLapTime / 3600 << " hr" << std::endl;
    }
    return 0;
}
