// Course.cpp
#include "Course.h"

#include<iostream>
#include<string>
#include <utility>
#include <iostream>
#include <vector>
using namespace std;

Course::Course() {
    id = ""; 
    name = ""; 
    isLecture = false;
    isLab = false;
}


Course::Course(string id, string name, bool isLecture, bool isLab) {
    this->id = id;
    this->name = name;
    this->isLecture = isLecture;
    this->isLab= isLab;

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



