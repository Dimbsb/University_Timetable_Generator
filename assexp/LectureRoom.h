#ifndef LECTUREROOM_H
#define LECTUREROOM_H

#include "Room.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class LectureRoom : public Room {
private:
    string typeofRoom;  // Type of room (e.g., Class room or Lecture room)

public:
    LectureRoom();                      // Default constructor
    LectureRoom(string classCode, string building, int capacity, string typeofRoom); // Parameterized constructor
    string getTypeofRoom();             // Getter for the type of room
    string getRoomName() const;         // Getter for the room name (class code)
};

#endif


