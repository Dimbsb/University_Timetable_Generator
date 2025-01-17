#include "Room.h"

Room::Room() {
    classCode = building = "";
    capacity = 0;
}

Room::Room(string classCode, string building, int capacity) {
    this->classCode = classCode;
    this->building = building;
    this->capacity = capacity;
}

string Room::getClassCode() {
    return classCode;
}

string Room::getBuilding() {
    return building;
}

int Room::getCapacity() {
    return capacity;
}
