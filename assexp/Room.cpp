#include "Room.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>

using namespace std;

Room::Room() {
    classCode = building = "";
    capacity = 0;
}

Room::Room(string classCode, string building, int capacity) {
    this->classCode = classCode;
    this->building = building;
    this->capacity = capacity;
}

string Room::getClassCode() const {
    return classCode;
}

string Room::getBuilding() const {
    return building;
}

int Room::getCapacity() const {
    return capacity;
}
