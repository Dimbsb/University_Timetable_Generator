#ifndef LABORATORY_H
#define LABORATORY_H

#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Laboratory : public Room {
private:
    string typeofLab;  // Type of lab

public:
    Laboratory();                        // Default constructor
    Laboratory(string classCode, string building, int capacity, string typeofLab); // Parameterized constructor
    string getTypeofLab();               // Getter for the type of lab
    string getRoomName() const;          // Getter for the room name (class code)
};

#endif

