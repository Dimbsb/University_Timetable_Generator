#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

class Room {
    string classCode;
    string building;
    int capacity;

public:
    Room();
    Room(string classCode, string building, int capacity);

    string getClassCode();
    string getBuilding();
    int getCapacity();
};

#endif
