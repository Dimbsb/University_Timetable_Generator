#ifndef LECTUREROOM_H
#define LECTUREROOM_H

#include "Room.h"

class LectureRoom : public Room {
    string typeofRoom;

public:
    LectureRoom();
    LectureRoom(string classCode, string building, int capacity, string typeofRoom);

    string getTypeofRoom();
};

#endif
