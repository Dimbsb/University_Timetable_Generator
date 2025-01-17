#include "Course.h"

#include<iostream>
#include<string>
#include <utility>
#include <vector>
using namespace std;

Course::Course() {
    id = "";
    name = "";
    isLecture = false;
    isLab = false;
    TeachingHours = 0;
}

Course::Course(string id, string name, bool isLecture, bool isLab, int TeachingHours) {
    this->id = id;
    this->name = name;
    this->isLecture = isLecture;
    this->isLab = isLab;
    this->TeachingHours = TeachingHours;
}

string Course::getId() const {
    return id;
}

string Course::getName() const {
    return name;
}

string Course::getType() const {
    if (isLecture && isLab)
        return "Lecture and Lab";
    else if (isLecture)
        return "Lecture";
    else if (isLab)
        return "Lab";
    return "None";
}

int Course::getTeachinHours() const {
    return TeachingHours;
}

