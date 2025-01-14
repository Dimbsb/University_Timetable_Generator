// Course.cpp
#include "Course.h"
#include <iostream>
#include <vector>
using namespace std;

Course::Course() {
    this->id = ""; 
    this->name = ""; 
    this->type = ""; 
    this->FieldofStudies = ""; 
}


Course::Course(const string& id, const string& name, const string& type, const string& FieldofStudies) {
    this->id = id;
    this->name = name;
    this->type = type;
    this->FieldofStudies = FieldofStudies;

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


