#include "LectureRoom.h"
#include<iostream>
#include<string>
using namespace std;
LectureRoom::LectureRoom():Room()
{
	typeofRoom="";
}
LectureRoom::LectureRoom(string classCode, string building, int capacity, string typeofRoom):Room(classCode, building, capacity)
{
	this->typeofRoom=typeofRoom;
}
string LectureRoom::getTypeofRoom()
{
	return typeofRoom;
}