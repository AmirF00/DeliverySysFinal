#include "label.hpp"
#include <random>
#include <ctime>
#include <iostream>

//int Label::instanceCount = 0;

Label::Label() {
    // Generate random latitude
    latitude.degrees = randomInt(40, 41);
    latitude.minutes = randomInt(0, 59);
    latitude.seconds = randomInt(0, 59) + static_cast<double>(randomInt(0, 99)) / 100.0;

    // Generate random longitude
    longitude.degrees = randomInt(-6, -5);
    longitude.minutes = randomInt(0, 59);
    longitude.seconds = randomInt(0, 59) + static_cast<double>(randomInt(0, 99)) / 100.0;

    //getID
    
    
    // Determine the zone
    zone = static_cast<Zone>(randomInt(0, 3));

    // Generate random date
    randomDate = generateRandomDate();

    // Generate random letter
    randomChar = randomLetter();

    // Generate random 3-digit number
    randomDigits = random3DigitNumber();

    // Generate a random Client-ID (8 random digits + 1 random letter)
    clientID = std::to_string(randomInt(10000000, 99999999)) + randomLetter();
    
    //increase the instaces
    //instanceCount++;
}

std::string Label::getDestination() const {
    return "Destination: [" + std::to_string(longitude.degrees) + "° " + std::to_string(longitude.minutes) + " minutes " + std::to_string(longitude.seconds) + " seconds, " +
           std::to_string(latitude.degrees) + "° " + std::to_string(latitude.minutes) + " minutes " + std::to_string(latitude.seconds) + " seconds]";
}

std::string Label::getPackageID() const {
    return "Package ID: " + std::to_string(randomDigits) + randomChar + "-" + randomDate + "-" + (zone == NE ? "NE" : (zone == NW ? "NW" : (zone == SW ? "SW" : "SE")));
}

std::string Label::getClientID() const {
    return "Client ID: " + clientID;
}

//these 3 functions above are there to access the attributes of the label from outside label class. 

int Label::randomInt(int min, int max) {
    static std::mt19937 mt(static_cast<unsigned>(time(0))); // using the time as seed 
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

char Label::randomLetter() {
    static std::mt19937 mt(static_cast<unsigned>(time(0)));
    std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(mt));
}

std::string Label::generateRandomDate() {
    int year = randomInt(2020, 2024);
    int month = randomInt(1, 12);
    int day = randomInt(1, 31);
    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%04d%02d%02d", year, month, day);
    return std::string(buffer);
}

int Label::random3DigitNumber() {
    return randomInt(100, 999);
}

//std::string Label::getID() const {
    //return " ID: " + std::to_string(instanceCount);
//}
