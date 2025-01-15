#ifndef ROOM_H
#define ROOM_H
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

class Room
{
	private:
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
