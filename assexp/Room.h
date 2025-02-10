#ifndef ROOM_H
#define ROOM_H

#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

class Room {
private:
    string classCode;  // Room's class code (e.g., 101, 102, etc.)
    string building;   // Building name
    int capacity;      // Room capacity 

public:
    Room();            // Default constructor
    Room(string classCode, string building, int capacity); // Parameterized constructor
    string getClassCode() const;  // Getter for the class code
    string getBuilding() const;   // Getter for the building name/number
    int getCapacity() const;      // Getter for the room's capacity
};

#endif

