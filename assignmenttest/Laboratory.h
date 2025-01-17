#ifndef LABORATORY_H
#define LABORATORY_H

#include "Room.h"

class Laboratory : public Room {
    string typeofLab;

public:
    Laboratory();
    Laboratory(string classCode, string building, int capacity, string typeofLab);

    string getTypeofLab();
};

#endif
