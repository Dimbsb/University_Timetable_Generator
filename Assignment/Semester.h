// Semester.h
#ifndef SEMESTER_H
#define SEMESTER_H

#include <vector>
#include "Course.h"
using namespace std;

class Semester {
public:
    Semester(int id,int CapacityofCourses);
    int getId() const;
    int getCapacityofCourses() const;
    void addCourse(const Course& course);
    const vector<Course>& getCourses() const;

private:
    int CapacityofCourses;
    int id;
    vector<Course> courses;
};

#endif