#ifndef LECTUREROOM_H
#define LECTUREROOM_H
#include "Room.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

class LectureRoom: public Room
{
	private:
		string typeofRoom; //Class or Lecture room 
	public:
		LectureRoom();
		LectureRoom(string classCode, string building, int capacity, string typeofRoom);
		string getTypeofRoom();
};

#endif
