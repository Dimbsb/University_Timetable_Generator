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
    type = "";
}


Course::Course(string id, string name, string type) {
    this->id = id;
    this->name = name;
    this->type = type;
}


string Course::getId() const { 
    return id; 
    }


string Course::getName() const { 
    return name; 
    }


string Course::getType() const { 
    return type; 
    }


void Course::readDataCourse(){
    cout << "Enter course id:";
    cin >> id;
    cout << "Enter course name:";
    cin >> name;
    cout << "Enter course type:";
    cin >> type;
}


