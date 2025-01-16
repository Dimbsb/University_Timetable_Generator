#ifndef LABORATORY_H
#define LABORATORY_H
#include "Room.h"
#include<iostream>
#include<string>
#include <vector>
#include <utility>
using namespace std;

class Laboratory: public Room
{
	private:
		string typeofLab;
	public:
		Laboratory();
		Laboratory(string classCode, string building, int capacity, string typeofLab);
		string getTypeofLab();
};

#endif
