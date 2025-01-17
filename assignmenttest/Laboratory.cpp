#include "Laboratory.h"
#include<iostream>
#include<string>
using namespace std;
Laboratory::Laboratory():Room()
{
	typeofLab="";
}
Laboratory::Laboratory(string classCode, string building, int capacity, string typeofLab):Room(classCode, building, capacity)
{
	this->typeofLab=typeofLab;
}
string Laboratory::getTypeofLab()
{
	return typeofLab;
}