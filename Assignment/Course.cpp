// Course.cpp
#include "Course.h"
#include <iostream>
using namespace std;


Course::Course() {
    this->id = 0; 
    this->name = ""; 
    this->type = ""; 
    this->FieldofStudies = ""; 
}


Course::Course(int id, const string& name, const string& type, const string& FieldofStudies) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->FieldofStudies = FieldofStudies;

}


int Course::getId() const { 
    return id; 
    }


string Course::getName() const { 
    return name; 
    }


string Course::getType() const { 
    return type; 
    }

string Course::getFieldofStudies() const { 
    return FieldofStudies; 
    }


void Course::readDataCourse(){
    cout << "Enter course id:";
    cin >> id;
    cout << "Enter course name:";
    cin >> name;
    cout << "Enter course type:";
    cin >> type;
    cout << "Enter course FieldofStudies:";
    cin >> FieldofStudies;

}