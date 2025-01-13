#include "Semester.h"
#include <iostream> // Include for std::cout
using namespace std;

Semester::Semester(int id, int CapacityofCourses) {
    this->id = id;
    this->CapacityofCourses = CapacityofCourses;
}

int Semester::getId() const { 
    return id; 
}

int Semester::getCapacityofCourses() const { 
    return CapacityofCourses; 
}

void Semester::addCourse(const Course& course) {
    if (courses.size() >= CapacityofCourses) {
        cout << "Cannot add more than " << CapacityofCourses << " courses." << endl;
        return ; 
    }
    courses.push_back(course);
}

const vector<Course>& Semester::getCourses() const {
    return courses;
}